#ifndef EXPLICITEULERINTEGRATOR_H
#define EXPLICITEULERINTEGRATOR_H

#include "Agent.h"

class ExplicitEulerIntegrator
{
public:
    inline ExplicitEulerIntegrator(float _timestep) : m_timestep(_timestep) {;}

    void updateAgent(Agent & io_agent, ngl::Vec3 _netForce) const;

    // Update agent without passing a net force. Will use the Agents steering force directly.
    inline void updateAgent(Agent & io_agent) const {updateAgent(io_agent, io_agent.getSteeringForce());}

private:
    float m_timestep;
};

#endif // EXPLICITEULERINTEGRATOR_H
