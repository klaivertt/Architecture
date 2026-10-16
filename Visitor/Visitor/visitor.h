#pragma once

#include "common.h"

class Visitor
{
public:
	Visitor(SystemeBase* _systemeBase);
	~Visitor();
	
	void Visit(Files* _files);
	void Visit(Directory* _directory);
private:
	size_t m_depht = 0;
};