#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include "Core.h"
#include <set>
#include <list>

struct Action
{
  Action(bool blocking);
  virtual ~Action();
  virtual void Update(float dt) = 0;
  //virtual bool IsValid() { return true; }
  bool IsFinished() const;
  bool IsBlocking() const;
protected:
  void SetFinished();
private:
  bool m_finished;
  bool m_blocking;
};

class ActionList : public Component
{
public:
  ActionList();
  ~ActionList();
  void Clear();
  ActionList * Push(Action * action);
  bool Empty() const;
private:
  friend class ActionManager;
  void Update(float dt);
  std::list<Action*> m_actions; // owned by us
};

class ActionManager : public System
{
public:
  ActionManager();
  virtual void Update(float dt);
  static ActionManager * Instance();
  
private:
  friend class ActionList;
  std::set<ActionList*> m_components;
  static ActionManager * s_instance;
};

#endif
