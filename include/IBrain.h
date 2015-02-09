#ifndef IBRAIN_H
#define IBRAIN_H

#include "Agent.h"
#include "IBehaviour.h"


//Forward Declaration
class EcoSystem;

/*
 * Interface describing what a brain must implement: one method updating an agent given several behaviours
 *
 * it cannot change itself when doing this (should work the same for every agent), and it cannot change anything but the agent
 */
class IBrain
{
public:
  virtual void updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<const IBehaviour *> & _behaviours) const = 0;
};

#endif // IBRAIN_H
