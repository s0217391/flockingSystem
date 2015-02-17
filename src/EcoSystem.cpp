#include "BasicBehaviours.h"
#include "EcoSystem.h"

//Create a new flock: init brain and behaviours as well!
int EcoSystem::createNewFlock()
{
  // This creates a flock on the stack.
  // once the flock is done, a deep copy is made in the vector.push_back call.
  // The deep copy relies on the CRTP for the pointer objects (behaviours and brains!!)

  // An alternative is to put the flock in the dynamic memory as well put I've been taught to avoid pointers as much as possible
  // (To reduce chances of memory leaks and gain performance from knowing memory size at compile time)
  // I wouldn't have used pointers for brains and behaviours but since they're virtual base class, I didn't have a choice

  /* from stackoverflow:
as a rule of thumb use the stack whenever you can. i.e. when the variable is never needed outside of that scope.
its faster, causes less fragmentation and is going to avoid the other overheads associated with calling malloc or new.
allocating off of the stack is a couple of assembler operations,
malloc or new is several hundred lines of code in an efficient implementation.

its never best to use the heap... just unavoidable. :)
   */

  Flock newFlock(m_flocks.size());
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

  m_flocks.push_back(newFlock); // Deep copy made here!

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

void EcoSystem::updateSystem()
{
  for(size_t i = 0; i < m_flocks.size(); ++i)
  {
    m_flocks[i].updateFlock(this);
  }
}

void EcoSystem::getAgentStates(std::vector<ngl::Vec3> & io_positions, std::vector<ngl::Vec3> & io_velocities)
{
  int counter = 0;
  for(size_t i = 0; i < m_flocks.size(); ++i)
  {
    const std::vector<Agent> & agents = m_flocks[i].getAgents();
    for(size_t j = 0; j < agents.size(); ++j)
    {
      io_positions[counter] = agents[j].getPosition();
      io_velocities[counter] = agents[j].getVelocity();
      ++counter;
    }
  }
}
