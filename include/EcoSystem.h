#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <vector>

#include "IBehaviour.h"
#include "Flock.h"

/*
 * This class represents the flocks and objects present in the environment
 *
 * It is important to keep this information together so it can be easily passed to the Behaviours.
 *
 * The behaviours are meant to be extensible, implying they might need every single bit of info in the EcoSystem.
 *
 */
class EcoSystem
{
public:
  // EcoSystem is the owner of these elements and thus the best place to initialize the flocks
  // In the future this will be done by a factory class
  // returns index of the flock
  int createNewFlock();
  // Add one agent to the flock. At the moment, all flock members are similar and can be best initialized by the flock.
  // This will need start position and velocity tho.
  // returns index of the agent
  inline int addAgentToFlock(int _flock) { return m_flocks[_flock].createAgent(); }

  inline const Agent & getAgent(AgentIdentifier _agent) const {return getFlock(_agent.m_flockId).getAgent(_agent.m_AgentId);}
  inline const Flock & getFlock(int _flockID) const {return m_flocks[_flockID];}

  // Avoid copying Agents.
  std::vector<AgentIdentifier> getAgentsWithinDistanceOfPosition(ngl::Vec3 _pos, float _distance);

  void updateSystem();

private:
  std::vector<Flock> m_flocks;
};


#endif // ECOSYSTEM_H
