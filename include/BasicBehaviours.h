#ifndef BASICBEHAVIOURS_H
#define BASICBEHAVIOURS_H

#include "IBehaviour.h"

class AlignmentBehaviour : public IBehaviourCRTP<AlignmentBehaviour>
{
public:
  inline AlignmentBehaviour() : IBehaviourCRTP<AlignmentBehaviour>() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

class SeparationBehaviour : public IBehaviourCRTP<SeparationBehaviour>
{
public:
  inline SeparationBehaviour() : IBehaviourCRTP<SeparationBehaviour>() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

class CohesionBehaviour : public IBehaviourCRTP<CohesionBehaviour>
{
public:
  inline CohesionBehaviour() : IBehaviourCRTP<CohesionBehaviour>() {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;
};

#endif // BASICBEHAVIOURS_H
