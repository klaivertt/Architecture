#pragma once

#include "common.h"

class Command;
class CommandManager
{
public:
	static void s_create();
	static CommandManager* const get() { return s_instance; }

	void Execute(Command* _commande);
	void Undo();
	void Redo();
private:
	CommandManager();
	~CommandManager();

	void ClearRedo();

	static CommandManager* s_instance;
	std::vector<Command*> m_commandes;
	std::vector<Command*> m_undoCommandes;
};