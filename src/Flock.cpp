#include <ngl/Random.h>

#include "Flock.h"

// Deep copy constructor. Relies on Curiously recurring template pattern for the pointer objects.
Flock::Flock(const Flock & other) : c_flockID(other.c_flockID) //gets the same id... this isn't ideal but for now it will do..
{
  for(size_t i = 0; i < other.m_behaviours.size(); ++i)
  {
    addBehaviour(other.m_behaviours[i]->clone());
  }

  setBrain(other.m_brain->clone());
}

//Flock owns behaviours and brain!
Flock::~Flock() // delete behaviours and brain
{
  cleanBehaviours();
  delete m_brain;
}

// Flock owns the agents, so it creates them as well. will happen in a factory class later on
int Flock::createAgent()
{
  ngl::Random * rand = ngl::Random::instance();

  ngl::Vec3 pos = 1 * rand->getRandomVec3();
  ngl::Vec3 vel = 1 * rand->getRandomVec3();
  Agent newA(m_agents.size(), c_flockID, pos, vel);

  m_agents.push_back(newA);
  return m_agents.size() - 1;
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
  if(m_brain == 0) delete m_brain;
  m_brain = _brain;
}


void Flock::updateFlock(EcoSystem * _eSystem)
{
  for(size_t i = 0; i < m_agents.size(); ++i)
  {
    m_brain->updateAgent(m_agents[i], _eSystem, m_behaviours);
  }
}
