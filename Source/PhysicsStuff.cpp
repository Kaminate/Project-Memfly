#include "PhysicsStuff.h"
#include "Transform.h"

PhysicsSystem * g_PhysicsSystem = 0;

PhysicsSystem::PhysicsSystem()
{
  if (g_PhysicsSystem) __debugbreak();
  g_PhysicsSystem = this;
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Update(float dt)
{
  for (auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    PhysicsComponent * component = *it;
  }
}

PhysicsComponent::PhysicsComponent()
{
  g_PhysicsSystem->m_components.insert(this);
}
PhysicsComponent::~PhysicsComponent()
{
  g_PhysicsSystem->m_components.erase(this);
}
