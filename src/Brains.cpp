#include "IBrain.h"

void AverageBrain::updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<IBehaviour *> & _behaviours) const
{
  ngl::Vec3 result;
  for(size_t i = 0; i < _behaviours.size(); ++i)
  {
      result += _behaviours[i]->computeForceUpdate(io_agent, _system);
  }
  if(_behaviours.size() > 0)
  {
      result = result * (1.0f / _behaviours.size());
  }

  io_agent.setSteeringForce(result);
}
