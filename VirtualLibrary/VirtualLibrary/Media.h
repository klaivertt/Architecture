#pragma once
#include "Helper.h"

//-------------------------------------------------------------------------
class Media
{
protected:
	const char* m_name{ nullptr };
};

//-------------------------------------------------------------------------
class Movie : public Media
{
public:
	Movie() { m_name = Helper::get().popRandomMovieName(); }
	~Movie() { Helper::get().pushMovieName(m_name); }
};
