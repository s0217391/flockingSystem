#include "Locomotion.h"

void Locomotion::moveAgent(Agent & io_agent)
{
  ngl::Vec3 netForce = io_agent.getSteeringForce();

  // Add damping force :)
  ngl::Vec3 damp = -1 * 0.5 * io_agent.getVelocity();

  netForce += damp;
  m_integrator.updateAgent(io_agent, netForce);
}
