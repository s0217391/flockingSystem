#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <vector>

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
  int createNewFlock();
  // Add one agent to the flock. At the moment, all flock members are similar and can be best initialized by the flock.
  // This will need start position and velocity tho.
  int addAgentToFlock(int _flock);

  void updateSystem();

private:
  std::vector<Flock> m_flocks;
};


#endif // ECOSYSTEM_H
