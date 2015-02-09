#ifndef FLOCK_H
#define FLOCK_H

#include <vector>

#include "Agent.h"
#include "IBehaviour.h"
#include "IBrain.h"

class Flock
{
private:
  std::vector<Agent> m_agents;
  //For now, all agents have the same brain and behaviours.
  // Worry about behaviour assignment later. Iterative development.
  std::vector<IBehaviour *> m_behaviours;

  IBrain * m_brain;
};

#endif // FLOCK_H
