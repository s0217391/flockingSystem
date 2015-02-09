#ifndef IBEHAVIOUR_H
#define IBEHAVIOUR_H

#include <ngl/Vec3.h>

#include "Agent.h"

//Forward Declaration
class EcoSystem;

/*
 * Behaviours give an agent a suggestion of how to update its velocity. While computing this, it is not allowed to change anything.
 */
class IBehaviour
{
public:
  // this will be implemented by any possible behaviour. For this reason, it is given a pointer to the full EcoSystem.
  // However, it is not allowed to change it
  virtual ngl::Vec3 computeVelocityUpdate(const Agent & _agent, const EcoSystem * _system) const = 0;
};

#endif // IBEHAVIOUR_H
