#pragma once
#include <iostream>
#include <type_traits>

#define DEBUG 1

#if DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x) 
#endif

namespace vector {

	//declaration
	template<class value_type>
	class Vector {
	private:
		unsigned int m_max_size; //total size of m_array
		value_type* m_buffer;
		unsigned int m_size; //number of elements in Vector
	public:
		Vector() : m_max_size(0), m_buffer(new value_type[m_max_size]), m_size(0) {};
		Vector(const Vector& other) : m_max_size(other.max_size()), m_buffer(new value_type[m_max_size]), m_size(0) {
			for (value_type value: other) {
				push_back(value);
			}
		};
		~Vector() { delete[] m_buffer; };
	public: //capacity
		void reserve(unsigned int t_new_size) { resize(t_new_size); LOG("Vector size set"); };
		unsigned int size() const { return m_size; };
		void resize(unsigned int t_new_size);
		void shrink_to_fit() { resize(m_size); };
		unsigned int max_size() const { return m_max_size; };
		unsigned int capacity() const { return m_max_size; };
		bool empty() const { return m_size == 0; };
	public: //iterators (these need to be rewrittent to return an iterator object (with ++ and -- overloads)
		value_type* begin() const { return m_buffer; };
		value_type* end() const { return (m_buffer + m_size); };
	public: //modifiers
		void push_back(value_type t_value);
		value_type& pop_back();
		void clear();
		void insert(unsigned int t_index, value_type t_value);
		void assign(value_type* t_start_ptr, value_type* t_end_ptr); //3 overloads in c++11 onwards
		void assign(unsigned int t_number, const value_type& t_value);
		void swap(Vector<value_type>& t_other);
		value_type* erase(value_type* t_index);
		value_type* erase(value_type* t_start, value_type* t_end);
	public: //element access
		value_type* data() { return m_buffer; };
		value_type& at(unsigned int t_index) const;
		value_type& front() const;
		value_type& back() const;
	public: //operator overloads
		value_type& operator[](unsigned int t_index) const { return m_buffer[t_index]; };
		//Vector<value_type> operator=(
		Vector& operator=(const Vector& other) {
			m_max_size = other.max_size();
			clear();
			for (value_type value : other) {
				push_back(value);
			}
			return *this;
		};
	private:
		bool max_capacity() const { return m_size == m_max_size; };
	public: //iterator class
		class Iterator {
		private:
		public:
		};
	};



	//IMPLEMENTATION
	//***************************************************

	//places new elemnt at end of Vector
	template<class value_type>
	void Vector<value_type>::push_back(value_type t_value) {
		if (max_capacity()) {
			if (m_max_size == 0)
				resize(1);
			else
				resize(m_max_size * 2);
			LOG("Vector size doubled");
		}
		m_buffer[m_size] = t_value;
		m_size++;
		LOG("Element added");
	}

	template<class value_type>
	void Vector<value_type>::clear() {
		delete[] m_buffer;
		m_buffer = new value_type[m_max_size];
		m_size = 0;
		LOG("Vector cleared");
	}


	template<class value_type>
	value_type& Vector<value_type>::pop_back() {
		--m_size;
		return m_buffer[m_size];
	}

	template<class value_type>
	void Vector<value_type>::insert(unsigned int t_index, value_type t_value) {
		if (max_capacity()) {
			if (m_max_size == 0)
				resize(1);
			else
				resize(m_max_size * 2);
		}
		if (t_index == m_size) { //insert to the end of vector
			m_buffer[t_index] = t_value;
			m_size++;
		} else {//insert at t_index, and shift all elements down by 1
			for (unsigned int i = m_size; i > t_index; --i) {
				m_buffer[i] = m_buffer[i - 1];
			}
			m_buffer[t_index] = t_value;
			m_size++;
		}
	}
	template<class value_type>
	void Vector<value_type>::assign(value_type* t_start_ptr, value_type* t_end_ptr) {
		clear();
		resize(0);
		for (value_type* iter = t_start_ptr; iter < t_end_ptr; ++iter) {
			push_back(*iter);
		}
	}

	template<class value_type>
	void Vector<value_type>::assign(unsigned int t_number, const value_type& t_value) {
		clear();
		reserve(t_number);
		for (unsigned int i = 0; i < t_number; ++i) {
			push_back(t_value);
		}
	}

	template<class value_type>
	void Vector<value_type>::swap(Vector<value_type>& t_other) {
		value_type* temp_buffer = m_buffer;
		unsigned int temp_size = m_size;
		unsigned int temp_max_size = m_max_size;
		m_buffer = t_other.m_buffer;
		m_size = t_other.m_size;
		m_max_size = t_other.m_max_size;
		t_other.m_buffer = temp_buffer;
		t_other.m_size = temp_size;
		t_other.m_max_size = temp_max_size;
	}

	template<class value_type>
	value_type* Vector<value_type>::erase(value_type* t_index) {
		//Transform t_index into usable numbers
		value_type* iter = t_index;
		while (iter != (end()-1)) {
			*iter = *(iter + 1);
			++iter;
		}
		--m_size;
		return t_index;
	}
	
	template<class value_type>
	value_type* Vector<value_type>::erase(value_type* t_start, value_type* t_end) {
		return t_start;
	}

	template<class value_type>
	value_type& Vector<value_type>::at(unsigned int t_index) const{
		return m_buffer[t_index];
	}

	template<class value_type>
	value_type& Vector<value_type>::front() const {
		return m_buffer[0];
	}

	template<class value_type>
	value_type& Vector<value_type>::back() const {
		return m_buffer[m_size - 1];
	}
	


	template<class value_type>
	void Vector<value_type>::resize(unsigned int t_new_size) {
		
		value_type* temp = m_buffer;
		m_buffer = new value_type[t_new_size];
		m_size = t_new_size < m_size ? t_new_size : m_size;

		//copy old array data into new array
		for (unsigned int i = 0; i < m_size; ++i) {
			m_buffer[i] = temp[i];
		}

		//delete old array and update m_array_size
		delete[] temp;
		m_max_size = t_new_size;
	}

};