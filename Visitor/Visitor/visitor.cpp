#include "visitor.h"
#include "dictionary.h"

PrintVisitor::PrintVisitor(SystemeBase* _systemeBase)
{
	if (_systemeBase == nullptr)
	{
		std::cout << "_sytemeBase is a null pointer";
	}

	_systemeBase->Accepte(*this);
}

PrintVisitor::~PrintVisitor()
{
}

void PrintVisitor::Visit(Files* _files)
{
	if (_files)
	{
		_files->Print(m_depht);
	}
}

void PrintVisitor::Visit(Directory* _directory)
{
	if (_directory)
	{
		_directory->Print(m_depht);
	}
	m_depht++;
	std::vector<SystemeBase*>& childrens = _directory->GetChildren();

	for (auto children : childrens)
	{
		children->Accepte(*this);
	}

}

ComputeSizeVisitor::ComputeSizeVisitor(SystemeBase* _systemeBase)
{
	if (_systemeBase == nullptr)
	{
		std::cout << "_sytemeBase is a null pointer";
	}

	_systemeBase->Accepte(*this);
	std::cout << "All Files size : " << m_sizeOfFiles << std::endl;
}

ComputeSizeVisitor::~ComputeSizeVisitor()
{
}

void ComputeSizeVisitor::Visit(Files* _files)
{
	if (_files)
	{
		m_sizeOfFiles += _files->GetSize();
	}
}

void ComputeSizeVisitor::Visit(Directory* _directory)
{
	if (_directory)
	{
		std::vector<SystemeBase*>& childrens = _directory->GetChildren();

		for (auto children : childrens)
		{
			children->Accepte(*this);
		}
	}
}
