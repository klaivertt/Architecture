#pragma once
#include "common.h"

class Subject;

class Observer
{
public:
	virtual ~Observer();

	virtual void onNotified() = 0;
	void setSubject(Subject& _subject) { m_subject = &_subject; }

private:
	Subject* m_subject{ nullptr };
};

class Subject
{
public:
	void registerObserver(Observer& _observer);
	void unregisterObserver(Observer& _observer);

	void notify();

private:
	std::vector<Observer*> m_observers;
};