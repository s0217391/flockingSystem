#include "BasicBehaviours.h"


ngl::Vec3 AlignmentBehaviour::computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const
{
  return ngl::Vec3();
}

ngl::Vec3 SeparationBehaviour::computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const
{
  return ngl::Vec3();
}

ngl::Vec3 CohesionBehaviour::computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const
{
  return ngl::Vec3();
}
