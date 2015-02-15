#include "Agent.h"

AgentIdentifier Agent::getIdentifier() const
{
    AgentIdentifier result;
    result.m_AgentId = getID();
    result.m_flockId = getFlockID();

    return result;
}
