#include "CommandeManager.h"
#include "Commande.h"

CommandManager* CommandManager::s_instance = nullptr;

void CommandManager::s_create()
{
	if (s_instance == nullptr)
	{
		s_instance = new CommandManager;
	}
}

void CommandManager::Execute(Command* _commande)
{
	if (_commande == nullptr)
	{
		return;
	}

	_commande->execute();
	m_commandes.push_back(std::move(_commande));
	ClearRedo();
}

void CommandManager::Undo()
{
	if (m_commandes.empty())
	{
		return;
	}

	Command* last = m_commandes.back();
	last->undo();
	m_undoCommandes.push_back(last);
	m_commandes.pop_back();
}

void CommandManager::Redo()
{
	if (m_undoCommandes.empty())
	{
		return;
	}

	Command* last = m_undoCommandes.back();
	last->redo();
	m_commandes.push_back(last);
	m_undoCommandes.pop_back();
}

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

void CommandManager::ClearRedo()
{
	for (auto undo : m_undoCommandes)
	{
		delete undo;
	}
	m_undoCommandes.clear();
}
