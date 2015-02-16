#ifndef EXPLICITEULERINTEGRATOR_H
#define EXPLICITEULERINTEGRATOR_H

#include "Agent.h"

class ExplicitEulerIntegrator
{
public:
    inline ExplicitEulerIntegrator(float _timestep) : m_timestep(_timestep) {;}

    void UpdateAgent(Agent & io_agent) const;

private:
    float m_timestep;
};

#endif // EXPLICITEULERINTEGRATOR_H
