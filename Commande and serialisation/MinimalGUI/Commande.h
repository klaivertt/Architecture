#pragma once

#include "common.h"
#include "Widget.h"

class Commande
{
public:
	~Commande() {}

	virtual void execute() = 0;
	virtual void undo() {};

};
template<typename T>
class SliderCommande : public Commande
{
public:
	SliderCommande(Slider<T>& _slider) : slider(_slider)
	{

	}
private:
	Slider<T>& slider;
};
