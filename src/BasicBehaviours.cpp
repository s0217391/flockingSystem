#include <vector>

#include "BasicBehaviours.h"
#include "EcoSystem.h"

// OK lazy bum make these member variables
float alignmentDistance = 0.2f;
float alignmentWeight = 0.0f;

float separationDistance = 1.0f;
float separationWeight = 0.1f;

float cohesionDistance = 10.0f;
float cohesionWeight = 0.1f;

ngl::Vec3 AlignmentBehaviour::computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const
{
  std::vector<AgentIdentifier> surroundings = _system->getAgentsWithinDistanceOfPosition(_agent.getPosition(), alignmentDistance);

  ngl::Vec3 avg_velocity(0, 0, 0);
  int count = 0;
  for(size_t i = 0; i < surroundings.size(); ++i)
  {
    if(surroundings[i].m_flockID != _agent.getFlockID()) break;
    if(surroundings[i].m_agentID == _agent.getID())      break;

    const Agent & otherAgent = _system->getAgent(surroundings[i]);
    avg_velocity += otherAgent.getVelocity();
    ++count;
  }

  if(count == 0) return ngl::Vec3(0, 0, 0);

  avg_velocity = (1.0f / (float) count) * avg_velocity;

  return alignmentWeight * (avg_velocity - _agent.getVelocity());
}

// This needs a bound!
ngl::Vec3 SeparationBehaviour::computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const
{
  std::vector<AgentIdentifier> surroundings = _system->getAgentsWithinDistanceOfPosition(_agent.getPosition(), separationDistance);

  ngl::Vec3 result(0, 0, 0);
  for(size_t i = 0; i < surroundings.size(); ++i)
  {
    if(surroundings[i].m_flockID != _agent.getFlockID()) break;
    if(surroundings[i].m_agentID == _agent.getID())      break;

    const Agent & otherAgent = _system->getAgent(surroundings[i]);
    ngl::Vec3 direction = _agent.getPosition() - otherAgent.getPosition();
    float distance = direction.length();
    direction.normalize();

    direction = (1.0f / distance) * direction; // BOUND THIS!
    result += direction;
  }

  return separationWeight * result;
}

ngl::Vec3 CohesionBehaviour::computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const
{
    std::vector<AgentIdentifier> surroundings = _system->getAgentsWithinDistanceOfPosition(_agent.getPosition(), cohesionDistance);

    ngl::Vec3 avg_position(0, 0, 0);
    int count = 0;
    for(size_t i = 0; i < surroundings.size(); ++i)
    {
      if(surroundings[i].m_flockID != _agent.getFlockID()) break;
      if(surroundings[i].m_agentID == _agent.getID())      break;

      const Agent & otherAgent = _system->getAgent(surroundings[i]);
      avg_position += otherAgent.getPosition();
      ++count;
    }

    if(count == 0) return ngl::Vec3(0, 0, 0);

    avg_position = (1.0f / (float) count) * avg_position;

    return cohesionWeight * (avg_position - _agent.getPosition());
}
