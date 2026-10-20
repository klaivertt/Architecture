#pragma once

#include "Common.h"

template<typename T>
void swap(T& _a, T& _b)
{
	T temp = _a;
	_a = _b;
	_b = temp;
}

template<typename T, typename T2>
class Pair
{
public:
	struct M_Pair
	{
		M_Pair(T _value1, T2 _value2)
			: m_value1(_value1), m_value2(_value2)
		{
		}
		T m_value1;
		T2 m_value2;
	};

	Pair& operator=(const Pair& other)
	{
		m_pair.m_value1 = other.m_pair.m_value1;
		m_pair.m_value2 = other.m_pair.m_value2;
		return *this;
	}

	Pair(T _value1, T2 _value2) : m_pair(_value1, _value2)
	{
	}

	Pair(M_Pair _pair) : m_pair(_pair)
	{
	}

	~Pair() = default;

	M_Pair& GetValue()
	{
		return m_pair;
	}
	T& GetFirst()
	{
		return m_pair.m_value1;
	}

	T2& GetSecond()
	{
		return m_pair.m_value2;
	}
private:
	M_Pair m_pair;
};

template<typename T>
class Array
{
public:
	Array() = default;

	explicit Array(size_t _size)
	{
		m_array = new T[_size];
		m_size = _size;
		m_capacity = _size;
	}

	~Array()
	{
		delete[] m_array;
		m_array = nullptr;
	}

	Array(const Array& _other)
	{
		m_array = (_other.m_size ? new T[_other.m_size] : nullptr);
		m_size = _other.m_size;
		m_capacity = _other.m_capacity;
		std::copy(_other.m_array, _other.m_array + _other.m_size, m_array);
	}

	Array(Array&& _other)
		: m_array(_other.m_array),
		m_size(_other.m_size),
		m_capacity(_other.m_capacity)
	{
		_other.m_array = nullptr;
		_other.m_size = 0;
		_other.m_capacity = 0;
	}

	T* Get()
	{
		return m_array;
	}

	T& operator[](size_t _index)
	{
		assert(_index < m_size && "Array: index out of range");
		return m_array[_index];
	}

	const T& operator[](size_t _index) const
	{
		assert(_index < m_size && "Array: index out of range");
		return m_array[_index];
	}

	const size_t size()
	{
		return m_size;
	}

	void Resize(size_t _newSize)
	{
		if (_newSize > m_capacity)
		{
			Reserve(_newSize);
		}

		for (size_t i = m_size; i < _newSize; ++i)
		{
			m_array[i] = T{};
		}

		m_size = _newSize;
	}

	void Reserve(size_t _newCapacity)
	{
		if (_newCapacity <= m_capacity)
		{
			return;
		}

		T* newArray = new T[_newCapacity];
		for (size_t i = 0; i < m_size; ++i)
		{
			newArray[i] = std::move(m_array[i]);
		}

		delete[] m_array;
		m_array = newArray;
		m_capacity = _newCapacity;
	}

	void PushBack(T _add)
	{
		if (m_size == m_capacity)
		{
			Reserve(m_capacity == 0 ? 1 : m_capacity * 2);
		}

		m_array[m_size++] = std::move(_add);
	}
private:
	T* m_array = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;

	void CalculCapacity(void)
	{
		m_capacity;
	}
};