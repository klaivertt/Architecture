#pragma once

#include "Common.h"

class User;
class Media;

class Librairies
{
public:
	Librairies();
	~Librairies();
	Media* PopRandomMedia()
	{
		if (m_medias.empty())
		{
			return nullptr;
		}

		int id = std::rand() % m_medias.size();

		Media* media = m_medias[id];
		m_medias.erase(m_medias.begin() + id);
		return media;
	}
	void PushMedia(Media* _medias)
	{
		if (_medias)
		{
			return;
		}

		m_medias.push_back(_medias);
	}

private:
	std::vector<Media*> m_medias;
};