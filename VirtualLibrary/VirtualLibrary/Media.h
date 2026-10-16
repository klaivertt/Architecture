#pragma once
#include "Helper.h"

//-------------------------------------------------------------------------
class Media
{
public:
	const char* getName()
	{
		return m_name;
	}

protected:
	const char* m_name{ nullptr };
};

//-------------------------------------------------------------------------
class Movie : public Media
{
public:
	Movie() 
	{ 
		m_name = Helper::get().popRandomMovieName();
	}

	~Movie() 
	{ 
		Helper::get().pushMovieName(m_name);
	}
private:
	float duration = 0;
};

// E-book
class Ebook : public Media
{
public:
	Ebook()
	{ 
		m_name = Helper::get().popRandomEbookName();
	}

	~Ebook()
	{ 
		Helper::get().pushEbookName(m_name);
	}
private:
	int pages = 0;
};
