#ifndef AGENT_H
#define AGENT_H

#include <ngl/Vec3.h>

class Agent
{
public:
  inline ngl::Vec3 getPosition() const {return m_position;}
  inline ngl::Vec3 getVelocity() const {return m_velocity;}

  inline void setPosition(ngl::Vec3 _newPosition) {m_position = _newPosition;}
  inline void setVelocity(ngl::Vec3 _newVelocity) {m_velocity = _newVelocity;}

private:
  // This might be replaced by a Locomotion class, as movement differs from animal to animal.
  ngl::Vec3 m_position;
  ngl::Vec3 m_velocity;
};


#endif // AGENT_H
