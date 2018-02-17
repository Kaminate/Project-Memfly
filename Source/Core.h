#ifndef COREH
#define COREH

#include <vector>

class Core;
class System;
class Component;
class GameObject;

class Core
{
public:
  void Update(float dt);
  void AddSystem(System * system);

private:
  std::vector<System*> m_systems;
};

class System
{
public:
  virtual ~System();
  virtual void Update(float dt) = 0;
};

class Component
{
public:
  Component();
  virtual ~Component();

  const GameObject * GetOwner() const;
  GameObject * GetOwner();
  GameObject * & GetOwnerRef();

private:
  GameObject * m_owner; // set by GameObject::AddComponent   // maybe this should just be public
};

class GameObject
{
public:
  ~GameObject(); // deletes all components
  void AddComponent(Component * component);
  
  template<typename ComponentType>
  ComponentType * GetComponent(); // return 0 if not found
  
  template<typename ComponentType>
  const ComponentType * GetComponent() const; // return 0 if not found
  

private:
  std::vector<Component *> m_components; // owned by GameObject
};

template<typename ComponentType> 
ComponentType * GameObject::GetComponent()
{
  for (auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    ComponentType * component = dynamic_cast<ComponentType*>(*it);
    if (component)
    {
      return component;
    }
  }
  return 0;
}

template<typename ComponentType>
const ComponentType * GameObject::GetComponent() const
{
  for (auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    const ComponentType * component = dynamic_cast<ComponentType*>(*it);
    if (component)
    {
      return component;
    }
  }
  return 0;
}
  

#endif
