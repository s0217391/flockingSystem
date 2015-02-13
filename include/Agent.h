#ifndef AGENT_H
#define AGENT_H

#include <ngl/Vec3.h>

class Agent
{
public:
  inline Agent(ngl::Vec3 _initPos, ngl::Vec3 _initVel) : m_position(_initPos), m_velocity(_initVel) {;}


  inline ngl::Vec3 getPosition() const {return m_position;}
  inline ngl::Vec3 getVelocity() const {return m_velocity;}
  inline ngl::Vec3 getSteeringForce() const {return m_steeringForce;}

  inline void setPosition(ngl::Vec3 _newPosition) {m_position = _newPosition;}
  inline void setVelocity(ngl::Vec3 _newVelocity) {m_velocity = _newVelocity;}
  inline void setSteeringForce(ngl::Vec3 _newForce) {m_steeringForce = _newForce;}

private:
  // This might be replaced by a Locomotion class, as movement differs from animal to animal.
  ngl::Vec3 m_position;
  ngl::Vec3 m_velocity;
  ngl::Vec3 m_steeringForce; // use forces, as in craig reynold's steering paper - force might be used to update orientation in a different way

  // You'll have to add mass at some point
};


#endif // AGENT_H
