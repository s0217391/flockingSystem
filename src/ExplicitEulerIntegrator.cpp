#include "ExplicitEulerIntegrator.h"

void ExplicitEulerIntegrator::updateAgent(Agent & io_agent, ngl::Vec3 _netForce) const
{
    ngl::Vec3 velocity = io_agent.getVelocity() + m_timestep * _netForce;

    ngl::Vec3 position = io_agent.getPosition() + m_timestep * io_agent.getVelocity(); // Explicit

    io_agent.setPosition(position);
    io_agent.setVelocity(velocity);
}
