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
		T m_value2;
	};

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
		if (m_array)
		{
			delete[] m_array;
			m_array = nullptr;
		}
		
		m_size = 0;

	}

	T& Get()
	{
		return m_array;
	}

	int& operator[](size_t _index)
	{
		return m_array[_index];
	}

	size_t size()
	{
		return m_size;
	}

private:
	T* m_array = nullptr;
	size_t m_size = 0;
};