#ifndef FLOCK_H
#define FLOCK_H

#include <vector>

#include "Agent.h"
#include "IBehaviour.h"
#include "IBrain.h"

class Flock
{
public:
  inline Flock(int _id) : c_flockID(_id), m_brain(NULL) {;}
  ~Flock(); // delete behaviours and brain

  // Flock owns the agents, so it creates them as well. will happen in a factory class later on
  int createAgent();
  // Return const reference to the agents
  inline const std::vector<Agent> & getAgents() const {return m_agents;}
  inline const Agent & getAgent(int _agentID) const {return m_agents[_agentID];}

  // Assume Flock becomes owner of this instance!!!
  inline void addBehaviour(IBehaviour * _behav) {m_behaviours.push_back(_behav);}
  void cleanBehaviours();

  // Flock becomes owner of this brain!!
  void setBrain(IBrain * _brain);

  inline int getID() const {return c_flockID;}

  void updateFlock(EcoSystem * _eSystem);

private:
  // TODO: THIS SHOULD BE CONST :( doesn't work
  int c_flockID;

  std::vector<Agent> m_agents;
  //For now, all agents have the same brain and behaviours.
  // Worry about behaviour assignment later. Iterative development.
  std::vector<IBehaviour *> m_behaviours;

  IBrain * m_brain;
};

#endif // FLOCK_H
