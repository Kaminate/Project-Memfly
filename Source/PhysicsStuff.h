#ifndef PHYSICSSTUFF_H
#define PHYSICSSTUFF_H

#include <set>
#include <map>
#include <string>

#include "Core.h"
#include "Point4.h"
#include "Vector4.h"

class PhysicsSystem;
class PhysicsComponent;

extern PhysicsSystem * g_PhysicsSystem;

class PhysicsSystem : public System
{
public:
  PhysicsSystem();
  ~PhysicsSystem();
  virtual void Update(float dt);
  
private:
  friend class PhysicsComponent;
  
  std::set<PhysicsComponent*> m_components;
  
};

class PhysicsComponent : public Component
{
public:
  PhysicsComponent();
  ~PhysicsComponent();
private:
  Point4 m_position;  // m/s.
  Vector4 m_velocity; // m/s.
  float m_radius;     // m.   assumption: everything's a circle
};
#endif
