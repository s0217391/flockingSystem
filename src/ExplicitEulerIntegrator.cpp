#include "ExplicitEulerIntegrator.h"

void ExplicitEulerIntegrator::UpdateAgent(Agent & io_agent) const
{
    ngl::Vec3 velocity = io_agent.getVelocity() + m_timestep * io_agent.getSteeringForce();

    ngl::Vec3 position = io_agent.getPosition() + m_timestep * io_agent.getVelocity(); // Explicit

    io_agent.setPosition(position);
    io_agent.setVelocity(velocity);
}
