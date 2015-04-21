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
 * For now, IBrain can include integration. THIS'LL HAVE TO MOVE TO locomotion once you have it!!
 */
class IBrain
{
public:
  // has to update agent but nothing else!!
  //   pointer to ecosystem, so "this" can be passed
  // TODO: how can I get the IBehaviours to be const?
  virtual void updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<IBehaviour *> & _behaviours) const = 0;

  virtual IBrain * clone() const = 0;

protected:
  inline IBrain() {;}
};


// CURIOUSLY RECURRING TEMPLATE PATTERN
template <typename Derived>
class IBrainCRTP : public IBrain
{
public:
  inline virtual IBrain * clone() const {return new Derived(static_cast<Derived const&>(*this));}
};





/*
 * Brain that averages all behaviours
 */
class AverageBrain : public IBrainCRTP<AverageBrain>
{
public:
  inline AverageBrain() : IBrainCRTP<AverageBrain>() {;}

  // has to update agent but nothing else!!
  // TODO: how can I get the IBehaviours to be const?
  virtual void updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<IBehaviour *> & _behaviours) const;
};




/*
 * Brain that averages all behaviours of the highest available priority
 */
class PriorityBrain : public IBrainCRTP<PriorityBrain>
{
public:
  inline PriorityBrain() : IBrainCRTP<PriorityBrain>() {;}

  // has to update agent but nothing else!!
  // TODO: how can I get the IBehaviours to be const?
  virtual void updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<IBehaviour *> & _behaviours) const;
};

#endif // IBRAIN_H
