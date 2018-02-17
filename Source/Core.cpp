#include "Core.h"

void Core::Update(float dt)
{
  for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
  {
    (*it)->Update(dt);
  }
}
void Core::AddSystem(System * system) { m_systems.push_back(system); }
System::~System(){}
Component::Component() : m_owner(0) {}
Component::~Component(){}
      GameObject *   Component::GetOwner()       { return m_owner; }
const GameObject *   Component::GetOwner() const { return m_owner; }
      GameObject * & Component::GetOwnerRef()    { return m_owner; }
GameObject::~GameObject()
{
  for (auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    delete *it;
  }
}
void GameObject::AddComponent(Component * component)
{
  component->GetOwnerRef() = this;
  m_components.push_back(component);
}

