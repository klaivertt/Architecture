#pragma once

#include "common.h"

class SystemeBase
{
public:
	SystemeBase();
	~SystemeBase();

	virtual void Print(size_t _depht) = 0;
	virtual void Accepte(Visitor& _visitor) = 0;

protected:
	std::string m_name = "";
};

class Directory : public SystemeBase
{
public:
	Directory(std::string _name)
	{
		m_name = _name;
	}

	~Directory();

	void Add(SystemeBase* _systemeBase);

	std::vector<SystemeBase*>& GetChildren();

	void Print(size_t _depht) override;

	virtual void Accepte(Visitor& _visitor) override;
private:
	std::vector<SystemeBase*> m_files;
};

class Files : public SystemeBase
{
public:
	Files(std::string _name, size_t _size = 512u)
	{
		m_name = _name;
		m_size = _size;
	}
	~Files();

	void Print(size_t _depht) override;
	
	virtual void Accepte(Visitor& _visitor)override;
	size_t GetSize();
private:
	size_t m_size = 0u;
};
