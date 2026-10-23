#pragma once
#include "common.h"

class Button;
template<typename T>
class Slider;
class Label;
class Panel;

//---------------------------------------------------------------------------------
class Visitor
{
public:
	virtual ~Visitor() {}

	virtual void visit(Button& _button) {}
	virtual void visit(Slider<unsigned>& _slider) {}
	virtual void visit(Slider<float>& _slider) {}
	virtual void visit(Panel& _panel);
	virtual void visit(Label& _label) {}
};

//---------------------------------------------------------------------------------
class ConstVisitor
{
public:
	virtual ~ConstVisitor() {}

	virtual void visit(const Button& _button) {}
	virtual void visit(const Slider<unsigned>& _slider) {}
	virtual void visit(const Slider<float>& _slider) {}
	virtual void visit(const Panel& _panel);
	virtual void visit(const Label& _label) {}
};

