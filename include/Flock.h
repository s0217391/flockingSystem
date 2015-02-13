#ifndef FLOCK_H
#define FLOCK_H

#include <vector>

#include "Agent.h"
#include "IBehaviour.h"
#include "IBrain.h"

class Flock
{
public:
  inline Flock() {;}
  ~Flock(); // delete behaviours and brain

  // Flock owns the agents, so it creates them as well. will happen in a factory class later on
  int createAgent();

  // Assume Flock becomes owner of this instance!!!
  inline void addBehaviour(IBehaviour * _behav) {m_behaviours.push_back(_behav);}
  void cleanBehaviours();

  // Flock becomes owner of this brain!!
  void setBrain(IBrain * _brain);


private:
  std::vector<Agent> m_agents;
  //For now, all agents have the same brain and behaviours.
  // Worry about behaviour assignment later. Iterative development.
  std::vector<IBehaviour *> m_behaviours;

  IBrain * m_brain;
};

#endif // FLOCK_H
