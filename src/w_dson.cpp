module wind;

import <string>;
import <cstdint>;
import std;
import :base;
import :dson;
import :string;

namespace wind
{
	const string_t dson_t::default_tab = "\t";

	dson_t::dson_t() = default;

	void dson_t::set_content(const string_t& sString, const size_t nItem)
	{
		if (nItem >= m_vContent.size())
			m_vContent.resize(nItem + 1);

		m_vContent[nItem] = sString;
	}

	// Retrieves the String Value of a Property (for a given index) or ""
	const string_t dson_t::get_content(const size_t nItem) const
	{
		if (nItem >= m_vContent.size())
			return "";
		else
			return m_vContent[nItem];
	}

	size_t dson_t::get_content_count() const
	{
		return m_vContent.size();
	}

	size_t dson_t::get_children_count() const
	{
		return this->m_mapObjects.size();
	}

	bool dson_t::contains(const string_t& sName) const
	{
		return m_mapObjects.count(sName.c_str()) > 0;
	}

	const dson_t& dson_t::get_property(const string_t& name) const
	{
		size_t x = name.find('.');

		if (x != string_t::npos)
		{
			string_t sProperty = name.substr(0, x);

			if (this->contains(sProperty))
			{
				return operator[](sProperty).get_property(name.substr(x + 1));
			}

			return operator[](sProperty);
		}

		return operator[](name);
	}

	dson_t& dson_t::get_property(const string_t& name)
	{
		size_t x = name.find('.');

		if (x != string_t::npos)
		{
			string_t sProperty = name.substr(0, x);

			if (this->contains(sProperty))
			{
				return operator[](sProperty).get_property(name.substr(x + 1, name.length()));
			}

			return operator[](sProperty);
		}

		return operator[](name);
	}

	dson_t& dson_t::get_indexed_property(const string_t& name, const size_t nIndex)
	{
		return get_property(name + "[" + std::to_string(nIndex) + "]");
	}

	bool dson_t::write(const dson_t& n, const string_t& sFileName, const string_t& sIndent, const char sListSep)
	{
		// Cache indentation level
		size_t nIndentCount = 0;
		// Cache sperator string for convenience
		string_t sSeperator = string_t({ sListSep, ' ', 0 });

		// Fully specified lambda, because this lambda is recursive!
		std::function<void(const dson_t&, ALLEGRO::FILE&)> write = [&](const dson_t& n, ALLEGRO::FILE& pfile)
			{
				// Lambda creates string given indentation preferences
				auto indent = [&](const string_t& sString, const size_t nCount)
					{
						string_t sOut;
						for (size_t n = 0; n < nCount; n++)
						{
							sOut.append(sString);
						}
						return sOut;
					};

				// Iterate through each property of this node
				for (auto const& property : n.m_vecObjects)
				{
					// Does property contain any sub objects?
					if (property.second.m_vecObjects.empty())
					{
						// No, so it's an assigned field and should just be written. If the property
						// is flagged get_as comment, it has no assignment potential. First write the 
						// property name

						al::fput_ustr(pfile, indent(sIndent, nIndentCount));
						al::fput_ustr(pfile, property.first);
						al::fputs(pfile, (property.second.m_bIsComment ? "" : " = "));

						// Second, write the property value (or values, seperated by provided
						// separation charater
						size_t nItems = property.second.get_content_count();
						for (size_t i = 0; i < property.second.get_content_count(); i++)
						{
							// If the Value being written, in string form, contains the separation
							// character, then the value must be written inside quotation marks. Note, 
							// that if the Value is the last of a list of Values for a property, it is
							// not suffixed with the separator

							size_t x = property.second.get_content(i).find(sListSep, 0);
							if (x != string_t::npos)
							{
								// Value contains separator, so wrap in quotes
								al::fputs(pfile, "\"");
								al::fput_ustr(pfile, property.second.get_content(i));
								al::fputs(pfile, "\"");
								if (nItems > 1)
								{
									al::fput_ustr(pfile, sSeperator);
								}
							}
							else
							{
								// Value does not contain separator, so just write out
								al::fput_ustr(pfile, property.second.get_content(i));
								if (nItems > 1)
								{
									al::fput_ustr(pfile, sSeperator);
								}
							}
							nItems--;
						}

						// Property written, move to next line
						al::fputs(pfile, "\n");
					}
					else
					{
						// Yes, property has properties of its own, so it's a node
						// Force a new line and write out the node's name
						al::fput_ustr(pfile, indent(sIndent, nIndentCount));
						al::fput_ustr(pfile, property.first);
						al::fputs(pfile, "\n");
						// Open braces, and update indentation
						al::fput_ustr(pfile, indent(sIndent, nIndentCount));
						al::fputs(pfile, "{\n");
						nIndentCount++;
						// Recursively write that node
						write(property.second, pfile);
						// Node written, so close braces
						al::fput_ustr(pfile, indent(sIndent, nIndentCount));
						al::fputs(pfile, "}\n");
					}
				}

				// We've finished writing out a node, regardless of state, our indentation
				// must decrease, unless we're top level
				if (nIndentCount > 0) nIndentCount--;
			};

		// Start Here! Open the file for writing
		ALLEGRO::FILE file = al::fopen(sFileName.c_str(), "w");
		if (file)
		{
			// write the file starting form the supplied node
			write(n, file);
			return true;
		}
		return false;
	}

	bool dson_t::read(dson_t& n, const string_t& sFileName, const char sListSep)
	{
		const size_t max_buffer = 2048;
		int32_t line_number = 0;
		char buffer[max_buffer] = "";

		// Open the file!
		const char* s = sFileName.c_str();
		ALLEGRO::FILE file = al::fopen(sFileName.c_str(), "rb");
		if (file)
		{
			// These variables are outside of the read loop, get_as we will
			// need to refer to previous iteration values in certain conditions
			string_t sPropName = "";
			string_t sPropValue = "";

			// The file is fundamentally structured get_as a stack, so we will read it
			// in a such, but note the data structure in memory is not explicitly
			// stored in a stack, but one is constructed implicitly via the nodes
			// owning other nodes (aka a tree)

			// I dont want to accidentally create copies all over the place, nor do 
			// I want to use pointer syntax, so being a bit different and stupidly
			// using std::reference_wrapper, so I can store references to dson_t
			// nodes in a std::container.
			std::stack<std::reference_wrapper<dson_t>> stkPath;
			stkPath.push(n);

			// read file line by line and process
			while (!al::feof(file))
			{
				string_t line(al::fget_ustr(file));

				// This little lambda removes whitespace from
				// beginning and end of supplied string
				auto trim = [](string_t& s)
					{
						al::ustr_ltrim_ws(s);
						al::ustr_rtrim_ws(s);
						return s;
					};

				trim(line);

				// If line has content
				if (!line.empty())
				{
					// Test if its a comment...
					if (line[0] == '#')
					{
						// ...it is a comment, so ignore
						dson_t comment;
						comment.m_bIsComment = true;
						stkPath.top().get().m_vecObjects.push_back({ line, comment });
					}
					else
					{
						// ...it is content, so parse. Firstly, find if the line
						// contains an assignment. If it does then it's a property...
						size_t x = line.find('=', 0);
						if (x != string_t::npos)
						{
							// ...so split up the property into a name, and its values!

							// Extract the property name, which is all characters up to
							// first assignment, trim any whitespace from ends
							sPropName = line.substr(0, x);
							trim(sPropName);

							// Extract the property value, which is all characters after
							// the first assignment operator, trim any whitespace from ends
							sPropValue = line.substr(x + 1, line.size());
							trim(sPropValue);

							// The value may be in list form: a, b, c, d, e, f etc and some of those
							// elements may exist in quotes a, b, c, "d, e", f. So we need to iterate
							// character by character and break up the value
							bool bInQuotes = false;
							string_t sToken;
							size_t nTokenCount = 0;
							for (const auto c : sPropValue)
							{
								// Is character a quote...
								if (c == '\"')
								{
									// ...yes, so toggle quote state
									bInQuotes = !bInQuotes;
								}
								else
								{
									// ...no, so proceed creating token. If we are in quote state
									// then just append characters until we exit quote state.
									if (bInQuotes)
									{
										sToken.push_back(c.get_codepoint());
									}
									else
									{
										// Is the character our seperator? If it is
										if (c == sListSep)
										{
											// Clean up the token
											trim(sToken);
											// Add it to the vector of values for this property
											stkPath.top().get()[sPropName].set_content(sToken, nTokenCount);
											// Reset our token state
											sToken.clear();
											nTokenCount++;
										}
										else
										{
											// It isnt, so just append to token
											sToken.push_back(c.get_codepoint());
										}
									}
								}
							}

							// Any residual characters at this point just make up the final token,
							// so clean it up and add it to the vector of values
							if (!sToken.empty())
							{
								trim(sToken);
								stkPath.top().get()[sPropName].set_content(sToken, nTokenCount);
							}
						}
						else
						{
							// ...but if it doesnt, then it's something structural
							if (line[0] == '{')
							{
								// Open brace, so push this node to stack, subsequent properties
								// will belong to the new node
								stkPath.push(stkPath.top().get()[sPropName]);
							}
							else
							{
								if (line[0] == '}')
								{
									// Close brace, so this node has been defined, pop it from the
									// stack
									stkPath.pop();
								}
								else
								{
									// Line is a property with no assignment. Who knows whether this is useful,
									// but we can simply add it get_as a valueless property...
									sPropName = line;
									// ...actually it is useful, get_as valuless properties are typically
									// going to be the names of new dson_t nodes on the next iteration
								}
							}
						}
					}
				}
				++line_number;
			}

			// Close and exit!
			file.reset();
			return true;
		}

		// File not found, so fail
		return false;
	}

	dson_t& dson_t::get_child(const string_t& name)
	{
		if (m_mapObjects.count(name) == 0)
		{
			m_mapObjects[name] = m_vecObjects.size();
			m_vecObjects.push_back({ name, dson_t() });
		}

		return m_vecObjects[m_mapObjects[name]].second;
	}

	const dson_t& dson_t::get_child(const string_t& name) const
	{
		auto a = m_mapObjects.find(name.c_str());

		ALLEGRO::ASSERT(a != m_mapObjects.cend());

		return m_vecObjects[a->second].second;
	}

	dson_t& dson_t::operator[](const string_t& name)
	{
		return this->get_child(name);
	}

	const dson_t& dson_t::operator[](const string_t& name) const
	{
		return this->get_child(name);
	}

	void dson_t::add_child(const string_t& name, const dson_t& dson)
	{
		this->m_mapObjects[name] = m_vecObjects.size();
		this->m_vecObjects.push_back({ name, dson });
	}

	dson_t::iterator dson_t::begin() { return iterator(this->m_vecObjects.begin()); }
	dson_t::iterator dson_t::end() { return iterator(this->m_vecObjects.end()); }
	dson_t::const_iterator dson_t::cbegin() const { return const_iterator(this->m_vecObjects.cbegin()); }
	dson_t::const_iterator dson_t::cend() const { return const_iterator(this->m_vecObjects.cend()); }

	bool dson_t::has_content() const { return this->m_vContent.size() > 0; }
	bool dson_t::has_children() const { return this->m_vecObjects.size() > 0; }

	void dson_t::clear()
	{
		this->m_vContent.clear();
		this->m_vecObjects.clear();
		this->m_mapObjects.clear();
		this->m_bIsComment = false;
	}

	bool dson_t::empty()
	{
		return this->m_vContent.empty() && this->m_vecObjects.empty();
	}
}
