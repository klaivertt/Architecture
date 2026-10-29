#pragma once

#include "common.h"
#include "Widget.h"

class Command
{
public:
	virtual ~Command() = default;

	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual void redo() = 0;

};

template<typename T>
class SliderCommand : public Command
{
public:
	SliderCommand(Slider<T>& _slider) : slider(_slider)
	{
		m_old = slider.getValue();
	}

	virtual void execute() override
	{
		m_new = slider.getValue();
	}

	virtual void undo() override
	{
		slider.SetValue(m_old);
	}

	virtual void redo() override
	{
		slider.SetValue(m_new);
	}

private:
	Slider<T>& slider;
	T m_old;
	T m_new;
};
