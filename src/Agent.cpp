#include "Agent.h"

AgentIdentifier Agent::getIdentifier() const
{
    AgentIdentifier result;
    result.m_agentID = getID();
    result.m_flockID = getFlockID();

    return result;
}
