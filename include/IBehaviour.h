#ifndef IBEHAVIOUR_H
#define IBEHAVIOUR_H

#include <ngl/Vec3.h>

#include "Agent.h"

//Forward Declaration
class EcoSystem;

/*
 * Behaviours give an agent a suggestion of how to update its velocity. While computing this, it is not allowed to change anything.
 */
class IBehaviour
{
public:  
  inline void setPriority(int _prior) {m_priority = _prior;}
  inline int getPriority() const {return m_priority;}
  // this will be implemented by any possible behaviour. For this reason, it is given a pointer to the full EcoSystem.
  // However, it is not allowed to change it
  virtual ngl::Vec3 computeForceUpdate(const Agent & _agent, const EcoSystem * _system) const = 0;

  virtual IBehaviour * clone() const = 0;

protected:
  inline IBehaviour() : m_priority(0) {;}

private:
  int m_priority;
};

// THIS IS AN EXAMPLE OF THE CURIOUSLY RECURRING TEMPLATE PATTERN -- google this if you forgot.

template <typename Derived>
class IBehaviourCRTP : public IBehaviour
{
public:
  inline virtual IBehaviour * clone() const {return new Derived(static_cast<Derived const&>(*this));}
};


#endif // IBEHAVIOUR_H
