#include "visitor.h"
#include "dictionary.h"

Visitor::Visitor(SystemeBase* _systemeBase)
{
	if (_systemeBase == nullptr)
	{
		std::cout << "_sytemeBase is a null pointer";
	}

	_systemeBase->Accepte(*this);
}

Visitor::~Visitor()
{
}

void Visitor::Visit(Files* _files)
{
	if(_files)
	{
		_files->Print(m_depht);
	}
}

void Visitor::Visit(Directory* _directory)
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
