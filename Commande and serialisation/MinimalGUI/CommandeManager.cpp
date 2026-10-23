#include "CommandeManager.h"
#include "Commande.h"

CommandeManager* CommandeManager::s_instance = nullptr;

void CommandeManager::s_create()
{
	if (s_instance == nullptr)
	{
		s_instance = new CommandeManager;
	}
}

void CommandeManager::Execute(Commande* _commande)
{
	if (_commande == nullptr)
	{
		return;
	}

	_commande->execute();
	m_commandes.push_back(_commande);
	ClearRedo();
}

void CommandeManager::Undo(Commande* _commande)
{
	if (!m_commandes.empty())
	{
		Commande* last = m_commandes.back();
		last->execute();
		m_commandes.pop_back();
		m_undoCommandes.push_back(last);
	}
}

void CommandeManager::Redo()
{
	if (!m_commandes.empty())
	{
		Commande* last = m_undoCommandes.back();
		last->execute();
		m_commandes.push_back(last);
		m_undoCommandes.pop_back();
	}
}

CommandeManager::CommandeManager()
{
}

CommandeManager::~CommandeManager()
{
}

void CommandeManager::ClearRedo()
{
	for (auto undo : m_undoCommandes)
	{
		delete undo;
	}
	m_undoCommandes.clear();
}
