export module wind:vector;

import <memory>;
import <cstdint>;
import :base;

namespace wind
{
	export template <typename T>
	class vector_t : public class_t<vector_t<T>>
	{
	public:
		using element_type = T;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using const_pointer_element_type = wind::add_pointer<const element_type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_reference_element_type = wind::add_reference<const element_type>::type;

		vector_t() : m_data(nullptr), m_count(0) {}

		vector_t(std::initializer_list<element_type> l) : m_data(l.size() ? std::make_shared<element_type[]>(l.size()) : nullptr), m_count(this->m_data ? l.size() : 0)
		{
			size_t i = 0;
			for (auto it = l.begin(); it != l.end(); ++it)
			{
				this->operator[](i) = *it;
				++i;
			}
		}

		vector_t(size_t count) : m_data(std::make_shared<element_type[]>(count)), m_count(this->m_data ? count : 0) {}

		vector_t(const vector_t<element_type>& vector) : m_data(vector.m_data), m_count(vector.m_count) {}

		template <typename Q>
		vector_t(const vector_t<Q>& vector) : m_data(vector.get_count() ? std::make_shared<element_type[]>(vector.get_count()) : nullptr), m_count(this->m_data ? vector.get_count() : 0)
		{
			for (size_t i = 0; i < this->m_count; ++i)
			{
				this->operator[](i) = vector[i];
			}
		}

		~vector_t() {}

		void clear()
		{
			this->m_data.reset();
		}

		vector_t& operator = (std::initializer_list<element_type> l)
		{
			if (l.size())
			{
				this->m_data = std::make_shared<element_type[]>(l.size());

				if (this->m_data)
				{
					this->m_count = 0;

					for (auto it = l.begin(); it != l.end(); ++it)
					{
						this->operator[](this->m_count) = *it;
						++this->m_count;
					}
				}
				else
				{
					this->m_count = 0;
				}
			}
			else
			{
				this->m_data.reset();
				this->m_count = 0;
			}

			return *this;
		}

		vector_t& operator = (const vector_t<T>& vector)
		{
			this->m_data = vector.m_data;
			this->m_count = vector.m_count;
			return *this;
		}

		template <typename Q>
		vector_t& operator = (const vector_t<Q>& vector)
		{
			if (vector.m_data)
			{
				this->m_data = std::make_shared<element_type[]>(vector.m_count);

				if (this->m_data)
				{
					for (size_t i = 0; i < this->m_count; ++i)
					{
						this->m_data.get()[i] = (element_type)vector.m_data.get()[i];
					}

					this->m_count = vector.m_count;
				}
				else
				{
					this->m_count = 0;
				}
			}
			else
			{
				this->m_data.reset();
				this->m_count = 0;
			}

			return *this;
		}

		size_t get_count() const
		{
			if (this->m_data)
			{
				return this->m_count;
			}

			return 0;
		}

		size_t get_element_size() const
		{
			return sizeof(element_type);
		}

		reference_element_type at(size_t index)
		{
			ALLEGRO::ASSERT(this->m_data && index < this->m_count);
			return this->m_data.get()[index];
		}

		const_reference_element_type at(size_t index) const
		{
			ALLEGRO::ASSERT(this->m_data && index < this->m_count);
			return this->m_data.get()[index];
		}

		reference_element_type operator [](size_t index)
		{
			ALLEGRO::ASSERT(this->m_data && index < this->m_count);
			return this->m_data.get()[index];
		}

		const_reference_element_type operator [](size_t index) const
		{
			ALLEGRO::ASSERT(this->m_data && index < this->m_count);
			return this->m_data.get()[index];
		}

		pointer_element_type get_data()
		{
			if (this->m_data)
			{
				return (pointer_element_type)this->m_data.get()->m_data;
			}

			return nullptr;
		}

		const_pointer_element_type get_data() const
		{
			if (this->m_data)
			{
				return (const_pointer_element_type)this->m_data.get()->m_data;
			}

			return nullptr;
		}

		class iterator
		{
		private:
			iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			iterator(const std::shared_ptr<element_type[]>& data, size_t count, size_t offset) : m_data(data), m_count(count), m_offset(offset), m_offset(offset) {}
			
			iterator(const iterator& it) : m_data(it.m_data), m_count(it.m_count), m_offset(it.m_offset) {}
			
			iterator& operator = (const iterator& it)
			{
				this->m_data = it.m_data;
				this->m_count = it.m_count;
				this->m_offset = it.m_offset;
				return *this;
			}

			bool empty() const
			{
				return !this->m_data;
			}
			
			bool operator == (const iterator& it) const { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }
			
			bool operator != (const iterator& it) const { return !operator == (it); }
			
			iterator& operator ++() { ++this->m_offset; return *this; }
			
			iterator operator ++(int32_t) { iterator tmp = *this; ++(*this); return tmp; }

			reference_element_type get_data()
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			const_reference_element_type get_data() const
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			reference_element_type operator *() { return this->get_data(); }
			const_reference_element_type operator *() const { return this->get_data(); }
			
			reference_element_type operator ->() { return this->get_data(); }
			const_reference_element_type operator ->() const { return this->get_data(); }

		private:
			std::shared_ptr<element_type[]> m_data{};
			size_t m_count;
			size_t m_offset;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			const_iterator(const std::shared_ptr<element_type[]>& data, size_t count, size_t offset) : m_data(data), m_count(count), m_offset(offset), m_offset(offset) {}

			const_iterator(const const_iterator& it) : m_data(it.m_data), m_count(it.m_count), m_offset(it.m_offset) {}

			const_iterator& operator = (const const_iterator& it)
			{
				this->m_data = it.m_data;
				this->m_count = it.m_count;
				this->m_offset = it.m_offset;
				return *this;
			}

			bool empty() const
			{
				return !this->m_data;
			}

			bool operator == (const const_iterator& it) const { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }

			bool operator != (const const_iterator& it) const { return !operator == (it); }

			const_iterator& operator ++() { ++this->m_offset; return *this; }

			const_iterator operator ++(int32_t) { const_iterator tmp = *this; ++(*this); return tmp; }

			reference_element_type get_data()
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			const_reference_element_type get_data() const
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			reference_element_type operator *() { return this->get_data(); }
			const_reference_element_type operator *() const { return this->get_data(); }

			reference_element_type operator ->() { return this->get_data(); }
			const_reference_element_type operator ->() const { return this->get_data(); }

		private:
			std::shared_ptr<element_type[]> m_data{};
			size_t m_count;
			size_t m_offset;
		};

		class reverse_iterator
		{
		private:
			reverse_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			reverse_iterator(const std::shared_ptr<element_type[]>& data, size_t count, size_t offset) : m_data(data), m_count(count), m_offset(offset), m_offset(offset) {}

			reverse_iterator(const iterator& it) : m_data(it.m_data), m_count(it.m_count), m_offset(it.m_offset) {}

			reverse_iterator& operator = (const iterator& it)
			{
				this->m_data = it.m_data;
				this->m_count = it.m_count;
				this->m_offset = it.m_offset;
				return *this;
			}

			bool empty() const
			{
				return !this->m_data;
			}

			bool operator == (const iterator& it) const { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }

			bool operator != (const iterator& it) const { return !operator == (it); }

			reverse_iterator& operator --() { --this->m_offset; return *this; }

			reverse_iterator operator --(int32_t) { reverse_iterator tmp = *this; --(*this); return tmp; }

			reference_element_type get_data()
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data.get()[this->m_offset];
			}

			const_reference_element_type get_data() const
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data.get()[this->m_offset];
			}

			reference_element_type operator *() { return this->get_data(); }
			const_reference_element_type operator *() const { return this->get_data(); }

			reference_element_type operator ->() { return this->get_data(); }
			const_reference_element_type operator ->() const { return this->get_data(); }

		private:
			std::shared_ptr<element_type[]> m_data{};
			size_t m_offset;
		};

		class const_reverse_iterator
		{
		private:
			const_reverse_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			const_reverse_iterator(const std::shared_ptr<element_type[]>& data, size_t count, size_t offset) : m_data(data), m_count(count), m_offset(offset), m_offset(offset) {}

			const_reverse_iterator(const iterator& it) : m_data(it.m_data), m_count(it.m_count), m_offset(it.m_offset) {}

			const_reverse_iterator& operator = (const iterator& it)
			{
				this->m_data = it.m_data;
				this->m_count = it.m_count;
				this->m_offset = it.m_offset;
				return *this;
			}

			bool empty() const
			{
				return !this->m_data;
			}

			bool operator == (const iterator& it) const { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }

			bool operator != (const iterator& it) const { return !operator == (it); }

			const_reverse_iterator& operator --() { --this->m_offset; return *this; }

			const_reverse_iterator operator --(int32_t) { const_reverse_iterator tmp = *this; --(*this); return tmp; }

			reference_element_type get_data()
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data.get()[this->m_offset];
			}

			const_reference_element_type get_data() const
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data.get()[this->m_offset];
			}

			reference_element_type operator *() { return this->get_data(); }
			const_reference_element_type operator *() const { return this->get_data(); }

			reference_element_type operator ->() { return this->get_data(); }
			const_reference_element_type operator ->() const { return this->get_data(); }

		private:
			std::shared_ptr<element_type[]> m_data{};
			size_t m_offset;
		};

		iterator begin()
		{
			return iterator(this->m_data, 0);
		}

		iterator end()
		{
			return iterator(this->m_data, this->m_count);
		}

		const_iterator cbegin()
		{
			return const_iterator(this->m_data, 0);
		}

		const_iterator cend()
		{
			return const_iterator(this->m_data, this->m_count);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->m_data, this->m_count - 1);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(this->m_data, -1);
		}

		const_reverse_iterator crbegin()
		{
			return const_reverse_iterator(this->m_data, this->m_count - 1);
		}

		const_reverse_iterator crend()
		{
			return const_reverse_iterator(this->m_data, -1);
		}

	private:
		std::shared_ptr<element_type[]> m_data{};
		size_t m_count{ 0 };
	};
}
