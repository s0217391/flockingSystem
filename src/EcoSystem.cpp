#include "BasicBehaviours.h"
#include "EcoSystem.h"

//Create a new flock: init brain and behaviours as well!
int EcoSystem::createNewFlock()
{
  Flock newFlock(m_flocks.size());

  /// Can only do this once there are actual implementations of brain and behaviour
  //create brain
  IBrain * brain = new AverageBrain(); // Becomes owner
  newFlock.setBrain(brain);
  //create behaviours
  IBehaviour * alignBehaviour = new AlignmentBehaviour();
  IBehaviour * separateBehaviour = new SeparationBehaviour();
  IBehaviour * cohesionBehaviour = new CohesionBehaviour();

  newFlock.addBehaviour(alignBehaviour);    // becomes owner
  newFlock.addBehaviour(separateBehaviour); // becomes owner
  newFlock.addBehaviour(cohesionBehaviour); // becomes owner

  m_flocks.push_back(newFlock); //shallow copy suffices. Don't copy the brain or behaviours!! THINK: implicit copy constructor makes a copy of the pointers which is good enough.

  // return index in the list
  return m_flocks.size() - 1;
}

std::vector<AgentIdentifier> EcoSystem::getAgentsWithinDistanceOfPosition(ngl::Vec3 _pos, float _distance)
{
  std::vector<AgentIdentifier> result;

  for(size_t i = 0; i < m_flocks.size(); ++i)
  {
    const std::vector<Agent> & agents = m_flocks[i].getAgents();
    for(size_t j = 0; j < agents.size(); ++j)
    {
        ngl::Vec3 diff = agents[j].getPosition() - _pos;
        if(diff.length() < _distance)
        {
            result.push_back(agents[j].getIdentifier());
        }
    }
  }

  return result;
}

