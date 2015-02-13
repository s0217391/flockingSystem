#include "EcoSystem.h"

//Create a new flock: init brain and behaviours as well!
int EcoSystem::createNewFlock()
{
  Flock newFlock;

  /// Can only do this once there are actual implementations of brain and behaviour
  //create brain
  //newFlock.setBrain(newBrain);
  //create behaviours
  //newFlock.setBehaviour();

  m_flocks.push_back(newFlock); //shallow copy suffices. Don't copy the brain or behaviours!! THINK: implicit copy constructor makes a copy of the pointers which is good enough.

  // return index in the list
  return m_flocks.size() - 1;
}
