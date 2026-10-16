#pragma once

#include "common.h"

class Visitor
{
public:	
	virtual void Visit(Files* _files) = 0;
	virtual void Visit(Directory* _directory) = 0;
private:
};

class PrintVisitor : public Visitor
{
public:
	PrintVisitor(SystemeBase* _systemeBase);
	~PrintVisitor();
	
	virtual void Visit(Files* _files) override;
	virtual void Visit(Directory* _directory) override;
private:
	size_t m_depht = 0;
};

class ComputeSizeVisitor : public Visitor
{
public:
	ComputeSizeVisitor(SystemeBase* _systemeBase);
	~ComputeSizeVisitor();
	
	virtual void Visit(Files* _files) override;
	virtual void Visit(Directory* _directory) override;
private:
	size_t m_sizeOfFiles = 0;
};