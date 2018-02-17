#include "ActionList.h"

ActionManager * ActionManager::s_instance = 0;

// Action Manager
ActionManager::ActionManager()
{
  if (s_instance)
  {
    __debugbreak();
  }
  s_instance = this;
}
void ActionManager::Update(float dt)
{
  for (auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    ActionList * actList = *it;
    actList->Update(dt);
  }
}
ActionManager* ActionManager::Instance() {return s_instance;}

// Action
Action::Action(bool blocking) : m_blocking(blocking), m_finished(false) {}
Action::~Action() {}
bool Action::IsFinished() const {return m_finished;}
bool Action::IsBlocking() const {return m_blocking;}
void Action::SetFinished() {m_finished = true;}

// Actionlist
ActionList::ActionList()
{
  ActionManager::Instance()->m_components.insert(this);
}
ActionList::~ActionList()
{
  Clear();
  ActionManager::Instance()->m_components.erase(this); 
}
void ActionList::Clear()
{
  for (auto it = m_actions.begin(); it != m_actions.end(); ++it)
  {
    Action * action = *it;
    delete action;
  }
}
ActionList * ActionList::Push(Action * action)
{
  m_actions.push_back(action);
  return this;
}
void ActionList::Update(float dt)
{
  auto it = m_actions.begin();
  while(it != m_actions.end())
  {
    Action * action = *it;
    //if (!action->IsValid())
    //{
    //  return Clear();
    //}
    action->Update(dt);
    if (action->IsFinished())
    {
      delete action;
      it = m_actions.erase(it);
    }
    else if (action->IsBlocking()) return;
    else ++it;
  }
}
bool ActionList::Empty() const
{
  return m_actions.empty();
}