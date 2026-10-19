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
	Array(size_t _size)
	{
		m_array = new T[_size];
		m_size = _size;
	}
	~Array()
	{
		delete[] m_array;
		m_array = nullptr;
	}

	T* Get()
	{
		return m_array;
	}

	const T& operator[](size_t _index)
	{
		if (_index >= m_size)
		{
			std::cout << "Index : " << _index << "is out ouf bond max size of this array : " << m_size << std::endl;
			return const T;
		}
		return m_array[_index];
	}

	const size_t size()
	{
		return m_size;
	}

	void Resize(size_t _newSize)
	{
		if (!m_array)
		{
			std::cout << "array is null" << std::endl;
			return;
		}

		T* temp = new T[_newSize];

		size_t copySize = std::min(m_size, _newSize);

		std::memcpy(temp, m_array, sizeof(T) * copySize);

		delete[] m_array;

		m_array = temp;
		m_size = _newSize;
	}

private:
	T* m_array = nullptr;
	size_t m_size = 0;
};