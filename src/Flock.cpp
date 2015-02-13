#include "Flock.h"

//Flock owns behaviours and brain!
Flock::~Flock() // delete behaviours and brain
{
  cleanBehaviours();
  delete m_brain;
}

// Flock owns the agents, so it creates them as well. will happen in a factory class later on
int Flock::createAgent()
{
  //create new agent, returns its index in the list.
  return 0;
}


//Flock owns behaviours
void Flock::cleanBehaviours()
{
  for(size_t i = 0; i < m_behaviours.size(); ++i)
  {
    delete m_behaviours[i];
  }
  m_behaviours.clear();
}

// Flock is owner of his brain!! delete the old one
void Flock::setBrain(IBrain * _brain)
{
  delete m_brain;
  m_brain = _brain;
}
