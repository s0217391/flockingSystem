#include <ngl/Random.h>

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
  ngl::Random * rand = ngl::Random::instance();

  ngl::Vec3 pos = 100 * rand->getRandomVec3();
  ngl::Vec3 vel = rand->getRandomVec3();
  Agent newA(pos, vel);

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
  delete m_brain;
  m_brain = _brain;
}
