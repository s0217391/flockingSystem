#ifndef BASICBEHAVIOURS_H
#define BASICBEHAVIOURS_H

#include "IBrain.h"

class AlignmentBehaviour
{
public:
  inline AlignmentBehaviour() : IBrain() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

class SeparationBehaviour
{
public:
  inline SeparationBehaviour() : IBrain() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

class CohesionBehaviour
{
public:
  inline CohesionBehaviour() : IBrain() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

#endif // BASICBEHAVIOURS_H
