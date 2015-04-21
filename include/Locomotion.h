#ifndef LOCOMOTION_H
#define LOCOMOTION_H

#include "Agent.h"
#include "ExplicitEulerIntegrator.h"

class Locomotion
{
public:
  inline Locomotion() : m_integrator(0.02) {;}

  void moveAgent(Agent & io_agent);

private:
  ExplicitEulerIntegrator m_integrator;
};

#endif // LOCOMOTION_H
