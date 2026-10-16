#pragma once

#include "Common.h"
#include "Helper.h"
class Media;

class User
{
public:
	User()
	{
		m_name = Helper::get().popRandomUserName();
	}
	~User()
	{
		Helper::get().pushUserName(m_name);
	}

	void Print();
	

	void SetMedia(Media* _media)
	{
		m_media = _media;
	}

private:
	const char* m_name;
	Media* m_media = nullptr;
};