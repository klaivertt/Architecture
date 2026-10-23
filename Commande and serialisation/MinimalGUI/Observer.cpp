#include "Observer.h"

Observer::~Observer()
{
    if (m_subject)
        m_subject->unregisterObserver(*this);
}

void Subject::registerObserver(Observer& _observer)
{
	m_observers.push_back(&_observer);
}

void Subject::unregisterObserver(Observer& _observer)
{
    for (unsigned int i = 0; i < m_observers.size(); ++i)
    {
        if (m_observers[i] == &_observer)
        {
            m_observers.erase(m_observers.begin() + i);
            return;
        }
    }
}

void Subject::notify() 
{
    for (Observer* o : m_observers)
    {
        o->onNotified();
    }
}