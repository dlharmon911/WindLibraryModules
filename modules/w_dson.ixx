/*
	OneLoneCoder - DataFile v1.00
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	An "easy to use" serialisation/deserialisation class that yields
	human readable hierachical files.

	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2022 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com

	Author
	~~~~~~
	David Barr, aka javidx9, OneLoneCoder 2019, 2020, 2021, 2022

*/

export module wind:dson;

import <string>;
import <vector>;
import <unordered_map>;
import <cstdint>;
import allegro;
import :base;
import :string;

namespace wind
{
	export class dson_t
	{
	public:
		using value_type = dson_t;
		using pointer_type = value_type*;
		using reference_type = value_type&;
		using const_pointer_type = const value_type*;
		using const_reference_type = const value_type&;

	private:
		using object_vector_t = std::vector<std::pair<string_t, dson_t>>;
		using index_map_t = std::unordered_map<string_t, size_t>;

		std::vector<string_t> m_vContent;
		object_vector_t m_vecObjects;
		index_map_t m_mapObjects;
		static const string_t default_tab;

	public:
		dson_t();

		const string_t get_content(const size_t nItem = 0) const;
		void set_content(const string_t& sString, const size_t nItem = 0);

		size_t get_content_count() const;
		size_t get_children_count() const;
		bool contains(const string_t& sName) const;
		reference_type get_property(const string_t& name);
		const_reference_type get_property(const string_t& name) const;
		reference_type get_indexed_property(const string_t& name, const size_t nIndex);
		static bool write(const dson_t& n, const string_t& sFileName, const string_t& sIndent = default_tab, const char sListSep = ',');
		static bool read(dson_t& n, const string_t& sFileName, const char sListSep = ',');
		reference_type get_child(const string_t& name);
		const_reference_type get_child(const string_t& name) const;
		reference_type operator[](const string_t& name);
		const_reference_type operator[](const string_t& name) const;
		void add_child(const string_t& name, const dson_t& dson);
		bool has_content() const;
		bool has_children() const;
		void clear();
		bool empty();

		class iterator
		{
		public:
			typedef std::ptrdiff_t difference_type;

			iterator() = default;
			iterator(object_vector_t::iterator it) : m_it(it) {}

			string_t key() const { return this->m_it->first; }
			bool operator == (const iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const iterator& it) const { return !operator == (it); }
			iterator& operator ++() { ++this->m_it; return *this; }
			iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
			pointer_type operator->() { return &this->m_it->second; }
			reference_type operator *() { return this->m_it->second; }

		private:
			object_vector_t::iterator m_it;
		};

		class const_iterator
		{
		public:
			typedef std::ptrdiff_t difference_type;

			const_iterator() = default;
			const_iterator(object_vector_t::const_iterator it) : m_it(it) {}

			string_t key() const { return this->m_it->first; }
			bool operator == (const const_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const const_iterator& it) const { return !operator == (it); }
			const_iterator& operator ++() { ++this->m_it; return *this; }
			const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
			const_pointer_type operator->() const { return &this->m_it->second; }
			const_reference_type operator *() const { return this->m_it->second;}

		private:
			object_vector_t::const_iterator m_it;
		};

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;

	protected:
		bool m_bIsComment = false;
	};
}
