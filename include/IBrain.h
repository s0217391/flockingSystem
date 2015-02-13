#ifndef IBRAIN_H
#define IBRAIN_H

#include <vector>

#include "Agent.h"
#include "IBehaviour.h"
#include "ExplicitEulerIntegrator.h"


//Forward Declaration
class EcoSystem;

/*
 * Interface describing what a brain must implement: one method updating an agent given several behaviours
 *
 * it cannot change itself when doing this (should work the same for every agent), and it cannot change anything but the agent
 *
 *
 * For now, IBrain can include integration. THIS'LL HAVE TO MOVE TO locomotion once you have it!!
 */
class IBrain
{
public:
  // has to update agent but nothing else!!
  //   pointer to ecosystem, so "this" can be passed
  virtual void updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<const IBehaviour *> & _behaviours) const = 0;

protected:
  inline IBrain() : m_integrator(0.02) {;}
  ExplicitEulerIntegrator m_integrator;
};

class AverageBrain : public IBrain
{
public:
  inline AverageBrain() : IBrain() {;}

  // has to update agent but nothing else!!
  virtual void updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<const IBehaviour *> & _behaviours) const;
};

#endif // IBRAIN_H
