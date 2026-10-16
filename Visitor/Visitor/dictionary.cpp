#include "dictionary.h"
#include "visitor.h"

Directory::~Directory()
{
	for (auto file : m_files)
	{
		delete file;
	}
}

void Directory::Add(SystemeBase* _systemeBase)
{
	if (_systemeBase == nullptr)
	{
		return;
	}

	m_files.push_back(_systemeBase);
}

std::vector<SystemeBase*>& Directory::GetChildren()
{
	return m_files;
}

void Directory::Print(size_t _depht)
{
	for (size_t i = 0; i < _depht; ++i)
	{
		std::cout << "--";
	}
	if (0 < _depht)
	{
		std::cout << ">";
	}

	std::cout << "Directory: " << m_name << std::endl;
}

void Directory::Accepte(Visitor& _visitor)
{
	_visitor.Visit(this);
}

Files::~Files()
{
}

void Files::Print(size_t _depht)
{
	for (size_t i = 0; i < _depht; ++i)
	{
		std::cout << "--";
	}
	if (0 < _depht)
	{
		std::cout << ">";
	}
	std::cout << "Files: " << m_name << " (size: " << m_size << " Bytes)" << std::endl;
}

void Files::Accepte(Visitor& _visitor)
{
	_visitor.Visit(this);
}

size_t Files::GetSize()
{
	return m_size;
}

SystemeBase::SystemeBase()
{
}

SystemeBase::~SystemeBase()
{
}
