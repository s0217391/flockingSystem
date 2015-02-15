#ifndef BASICBEHAVIOURS_H
#define BASICBEHAVIOURS_H

#include "IBehaviour.h"

class AlignmentBehaviour : public IBehaviour
{
public:
  inline AlignmentBehaviour() : IBehaviour() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

class SeparationBehaviour : public IBehaviour
{
public:
  inline SeparationBehaviour() : IBehaviour() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

class CohesionBehaviour : public IBehaviour
{
public:
  inline CohesionBehaviour() : IBehaviour() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

#endif // BASICBEHAVIOURS_H
