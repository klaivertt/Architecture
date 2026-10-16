#include "User.h"
#include "Media.h"
void User::Print()
{
	if (m_name)
	{
		std::cout << "User m_name : " << m_name << std::endl;
	}
	else
	{
		std::cout << "User m_name is nullptr" << std::endl;
	}

	if (m_media)
	{
		std::cout << "User m_media : " << m_media->getName() << std::endl;
	}
	else
	{
		std::cout << "User m_media is nullptr" << std::endl;
	}
}
