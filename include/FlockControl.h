#ifndef FLOCKCONTROL_H
#define FLOCKCONTROL_H

#include <vector>

#include <ngl/Vec3.h>

#include "Flock.h"

class FlockControl
{
public:

  // Add an agent to the flock
  void addAgent();

  // Output: get positions and velocities
  void getPositions(std::vector<ngl::Vec3>& o_positions) const;
  void getVelocities(std::vector<ngl::Vec3>& o_velocities) const;

private:
  //for now, we have one flock
  Flock m_flock;

};

#endif // FLOCKCONTROL_H
