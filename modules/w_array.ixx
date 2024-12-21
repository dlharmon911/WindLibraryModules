export module wind:array;

import <memory>;
import <cstdint>;
import :base;

namespace wind
{
	export template <typename T>
		class array_t
	{
	public:
		using element_type = T;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_pointer_element_type = wind::add_const_pointer<element_type>::type;
		using const_reference_element_type = wind::add_const_reference<element_type>::type;

		array_t() : m_data(nullptr), m_count(0) {}

		array_t(std::initializer_list<element_type> l) : m_data(l.size() ? std::make_shared<element_type[]>(l.size()) : nullptr), m_count(this->m_data ? l.size() : 0)
		{
			size_t i = 0;
			for (auto it = l.begin(); it != l.end(); ++it)
			{
				this->operator[](i) = *it;
				++i;
			}
		}

		array_t(size_t count) : m_data(std::make_shared<element_type[]>(count)), m_count(this->m_data ? count : 0) {}

		array_t(const array_t<element_type>& array) : m_data(array.m_data), m_count(array.m_count) {}

		template <typename Q>
		array_t(const array_t<Q>& array) : m_data(array.get_count() ? std::make_shared<element_type[]>(array.get_count()) : nullptr), m_count(this->m_data ? array.get_count() : 0)
		{
			for (size_t i = 0; i < this->m_count; ++i)
			{
				this->operator[](i) = array[i];
			}
		}

		~array_t() {}

		auto clear() -> void
		{
			this->m_data.reset();
		}

		auto operator = (std::initializer_list<element_type> l) -> array_t&
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

		auto operator = (const array_t<T>& array) -> array_t&
		{
			this->m_data = array.m_data;
			this->m_count = array.m_count;
			return *this;
		}

		template <typename Q>
		auto operator = (const array_t<Q>& array) -> array_t&
		{
			if (array.m_data)
			{
				this->m_data = std::make_shared<element_type[]>(array.m_count);

				if (this->m_data)
				{
					for (size_t i = 0; i < this->m_count; ++i)
					{
						this->m_data.get()[i] = (element_type)array.m_data.get()[i];
					}

					this->m_count = array.m_count;
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

		auto get_count() const -> size_t
		{
			if (this->m_data)
			{
				return this->m_count;
			}

			return 0;
		}

		auto get_element_size() const -> size_t
		{
			return sizeof(element_type);
		}

		auto at(size_t index) -> reference_element_type
		{
			ALLEGRO::ASSERT(this->m_data && index < this->m_count);
			return this->m_data.get()[index];
		}

		auto at(size_t index) const -> const_reference_element_type
		{
			ALLEGRO::ASSERT(this->m_data && index < this->m_count);
			return this->m_data.get()[index];
		}

		auto operator [](size_t index) -> reference_element_type
		{
			ALLEGRO::ASSERT(this->m_data && index < this->m_count);
			return this->m_data.get()[index];
		}

		auto operator [](size_t index) const -> const_reference_element_type
		{
			ALLEGRO::ASSERT(this->m_data && index < this->m_count);
			return this->m_data.get()[index];
		}

		auto get_data() -> pointer_element_type
		{
			if (this->m_data)
			{
				return (pointer_element_type)this->m_data.get();
			}

			return nullptr;
		}

		auto get_data() const -> const_pointer_element_type
		{
			if (this->m_data)
			{
				return (const_pointer_element_type)this->m_data.get();
			}

			return nullptr;
		}

		class iterator
		{
		private:
			iterator() = default;
		public:
			iterator(const std::shared_ptr<element_type[]>& data, size_t count, size_t offset) : m_data(data), m_count(count), m_offset(offset) {}

			iterator(const iterator& it) : m_data(it.m_data), m_count(it.m_count), m_offset(it.m_offset) {}

			auto operator = (const iterator& it) -> iterator&
			{
				this->m_data = it.m_data;
				this->m_count = it.m_count;
				this->m_offset = it.m_offset;
				return *this;
			}

			auto empty() const -> bool
			{
				return !this->m_data;
			}

			auto operator == (const iterator& it) const -> bool { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }

			auto operator != (const iterator& it) const -> bool { return !operator == (it); }

			auto operator ++() -> iterator& { ++this->m_offset; return *this; }

			auto operator ++(int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }

			auto get_data() -> reference_element_type
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			auto get_data() const -> const_reference_element_type
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			auto operator *() -> reference_element_type { return this->get_data(); }
			auto operator ->() -> reference_element_type { return this->get_data(); }
			auto operator *() const -> const_reference_element_type { return this->get_data(); }
			auto operator ->() const -> const_reference_element_type { return this->get_data(); }

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
			const_iterator(const std::shared_ptr<element_type[]>& data, size_t count, size_t offset) : m_data(data), m_count(count), m_offset(offset) {}

			const_iterator(const const_iterator& it) : m_data(it.m_data), m_count(it.m_count), m_offset(it.m_offset) {}

			auto operator = (const const_iterator& it) -> const_iterator&
			{
				this->m_data = it.m_data;
				this->m_count = it.m_count;
				this->m_offset = it.m_offset;
				return *this;
			}

			auto empty() const -> bool
			{
				return !this->m_data;
			}

			auto operator == (const const_iterator& it) const -> bool { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }

			auto operator != (const const_iterator& it) const -> bool { return !operator == (it); }

			auto operator ++() -> const_iterator& { ++this->m_offset; return *this; }

			auto operator ++(int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }

			auto get_data() const -> const_reference_element_type
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			auto operator *() const -> const_reference_element_type { return this->get_data(); }
			auto operator ->() const -> const_reference_element_type { return this->get_data(); }

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
			reverse_iterator(const std::shared_ptr<element_type[]>& data, size_t count, size_t offset) : m_data(data), m_count(count), m_offset(offset), m_offset(offset) {}

			reverse_iterator(const iterator& it) : m_data(it.m_data), m_count(it.m_count), m_offset(it.m_offset) {}

			auto operator = (const iterator& it) -> reverse_iterator&
			{
				this->m_data = it.m_data;
				this->m_count = it.m_count;
				this->m_offset = it.m_offset;
				return *this;
			}

			auto empty() const -> bool
			{
				return !this->m_data;
			}

			auto operator == (const reverse_iterator& it) const -> bool { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }

			auto operator != (const reverse_iterator& it) const -> bool { return !operator == (it); }

			auto operator --() -> reverse_iterator& { --this->m_offset; return *this; }

			auto operator --(int32_t) -> reverse_iterator { reverse_iterator tmp = *this; --(*this); return tmp; }

			auto get_data() -> reference_element_type
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			auto get_data() const -> const_reference_element_type
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			auto operator *() -> reference_element_type { return this->get_data(); }
			auto operator ->() -> reference_element_type { return this->get_data(); }
			auto operator *() const -> const_reference_element_type { return this->get_data(); }
			auto operator ->() const -> const_reference_element_type { return this->get_data(); }

		private:
			std::shared_ptr<element_type[]> m_data{};
			size_t m_offset;
		};

		class const_reverse_iterator
		{
		private:
			const_reverse_iterator() = default;
		public:
			const_reverse_iterator(const std::shared_ptr<element_type[]>& data, size_t count, size_t offset) : m_data(data), m_count(count), m_offset(offset), m_offset(offset) {}

			const_reverse_iterator(const iterator& it) : m_data(it.m_data), m_count(it.m_count), m_offset(it.m_offset) {}

			auto operator = (const iterator& it) -> const_reverse_iterator&
			{
				this->m_data = it.m_data;
				this->m_count = it.m_count;
				this->m_offset = it.m_offset;
				return *this;
			}

			auto empty() const -> bool
			{
				return !this->m_data;
			}

			auto operator == (const const_reverse_iterator& it) const -> bool { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }

			auto operator != (const const_reverse_iterator& it) const -> bool { return !operator == (it); }

			auto operator --() -> const_reverse_iterator& { --this->m_offset; return *this; }

			auto operator -- (int32_t) -> const_reverse_iterator { const_reverse_iterator tmp = *this; --(*this); return tmp; }

			auto get_data() const -> const_reference_element_type
			{
				ALLEGRO::ASSERT(this->m_data && this->m_offset < this->m_count);
				return this->m_data[this->m_offset];
			}

			auto operator *() const -> const_reference_element_type { return this->get_data(); }
			auto operator ->() const -> const_reference_element_type { return this->get_data(); }

		private:
			std::shared_ptr<element_type[]> m_data{};
			size_t m_offset;
		};

		auto begin() -> iterator
		{
			return iterator(this->m_data, this->m_count, 0);
		}

		auto end() -> iterator
		{
			return iterator(this->m_data, this->m_count, this->m_count);
		}

		auto cbegin() const->const_iterator
		{
			return const_iterator(this->m_data, this->m_count, 0);
		}

		auto cend() const->const_iterator
		{
			return const_iterator(this->m_data, this->m_count, this->m_count);
		}

		auto rbegin() -> reverse_iterator
		{
			return reverse_iterator(this->m_data, this->m_count, this->m_count - 1);
		}

		auto rend() -> reverse_iterator
		{
			return reverse_iterator(this->m_data, this->m_count, -1);
		}

		auto crbegin() const->const_reverse_iterator
		{
			return const_reverse_iterator(this->m_data, this->m_count, this->m_count - 1);
		}

		auto crend() const->const_reverse_iterator
		{
			return const_reverse_iterator(this->m_data, this->m_count, -1);
		}

	private:
		std::shared_ptr<element_type[]> m_data{};
		size_t m_count{ 0 };
	};

	namespace array
	{
		export template <typename T> auto swap(array_t<T>& array, size_t index_a, size_t index_b) -> void
		{
			T c = array[index_a];
			array[index_a] = array[index_b];
			array[index_b] = c;
		}
	}
}