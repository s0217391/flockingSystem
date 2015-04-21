#ifndef BASICBEHAVIOURS_H
#define BASICBEHAVIOURS_H

#include "IBehaviour.h"

class AlignmentBehaviour : public IBehaviourCRTP<AlignmentBehaviour>
{
public:
  inline AlignmentBehaviour(float _distance, float _weight) : IBehaviourCRTP<AlignmentBehaviour>(),
                                                              m_alignmentDistance(_distance),
                                                              m_alignmentWeight(_weight) {;}

  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;

private:
  // This behaviour only works with other agents within the specified distance
  float m_alignmentDistance;
  // The weight given to the force after it is computed.
  float m_alignmentWeight;
};

class SeparationBehaviour : public IBehaviourCRTP<SeparationBehaviour>
{
public:
  inline SeparationBehaviour(float _distance, float _weight) : IBehaviourCRTP<SeparationBehaviour>(),
                                                               m_separationDistance(_distance),
                                                               m_separationWeight(_weight) {;}


  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;

private:
  // This behaviour only works with other agents within the specified distance
  float m_separationDistance;
  // The weight given to the force after it is computed.
  float m_separationWeight;
};

class CohesionBehaviour : public IBehaviourCRTP<CohesionBehaviour>
{
public:
  inline CohesionBehaviour(float _distance, float _weight) : IBehaviourCRTP<CohesionBehaviour>(),
                                                             m_cohesionDistance(_distance),
                                                             m_cohesionWeight(_weight) {;}


  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const;

private:
  // This behaviour only works with other agents within the specified distance
  float m_cohesionDistance;
  // The weight given to the force after it is computed.
  float m_cohesionWeight;
};

#endif // BASICBEHAVIOURS_H
