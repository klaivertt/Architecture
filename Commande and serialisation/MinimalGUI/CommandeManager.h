#pragma once

#include "common.h"

class Commande;
class CommandeManager
{
public:
	void s_create();
	const CommandeManager* get() { return s_instance; }

	void Execute(Commande* _commande);
	void Undo(Commande* _commande);
	void Redo();
private:
	CommandeManager();
	~CommandeManager();

	void ClearRedo();

	static CommandeManager* s_instance;
	std::vector<Commande*> m_commandes;
	std::vector<Commande*> m_undoCommandes;
};