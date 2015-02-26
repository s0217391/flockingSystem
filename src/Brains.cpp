#include "IBrain.h"

void AverageBrain::updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<IBehaviour *> & _behaviours) const
{
  ngl::Vec3 result(0, 0, 0);
  int counter = 0;

  for(size_t i = 0; i < _behaviours.size(); ++i)
  {
    ngl::Vec3 temp = _behaviours[i]->computeForceUpdate(io_agent, _system);
    if(temp.length() > 0)
    {
      result += _behaviours[i]->computeForceUpdate(io_agent, _system);
      ++counter;
    }
  }

  if(counter > 0)
  {
    result = result * (1.0f / counter);
  }

  io_agent.setSteeringForce(result);
  m_integrator.UpdateAgent(io_agent);
}

void PriorityBrain::updateAgent(Agent & io_agent, const EcoSystem * _system, const std::vector<IBehaviour *> & _behaviours) const
{
  // start at lowest priority number (0 is highest priority)
  int currentPriority = 0;

  ngl::Vec3 result(0, 0, 0);
  // no need to clear these in the loop because once the become non-zero we'l exit the loop
  int counter = 0;
  int behaviourCheckedCounter = 0;

  //as long as we have not found a sufficient result and we haven't checked all behaviours (keep in mind there might not be any sufficient result):
  while(counter == 0 && behaviourCheckedCounter < _behaviours.size())
  {
    // check all behaviours:
    for(size_t i = 0; i < _behaviours.size(); ++i)
    {
      // To see if they have the current priority. If they have:
      if(_behaviours[i]->getPriority() == currentPriority)
      {
        // increase the amount of behaviours checked by one (this one)
        ++behaviourCheckedCounter;
        // compute its suggestion
        ngl::Vec3 temp = _behaviours[i]->computeForceUpdate(io_agent, _system);
        // if it is a useful suggestion:
        if(temp.length() > 0)
        {
          // add it to the result
          result += _behaviours[i]->computeForceUpdate(io_agent, _system);
          // keep track of the amount of behaviours with a useful suggestion
          ++counter;
        }
      }
    }

    // increase this for the next iteration, if any
    ++currentPriority;
  }

  // regular check before averaging
  if(counter > 0)
  {
    result = result * (1.0f / counter);
  }

  io_agent.setSteeringForce(result);
  m_integrator.UpdateAgent(io_agent);
}
