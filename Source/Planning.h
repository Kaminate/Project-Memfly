/*
  goal: KillEnemy
  valid {return agent->worldstate[target] != null}  <-- target is chosen my the target manager
  worldstate:
    - ENEMY_DEAD = true

  action: Attack
  prerequisite:
    - Armed = true
    - InWeaponsRange = true
  effect WorldState:
    - ENEMY_DEAD = true

  Action: Chase
  effect WorldState:
    - InWeaponsRange = true
  activation: requests nav manager to goto target location

  goal: GetHealth
  float valid
  {
    switch (agent->worldstate[m_healthy])
      case about_to_die: return 1;   
      case acceptable :  return 0.2f;
      case healthy :     return 0;   
  }
  WorldState:
    - m_healthy = acceptable;
*/

#ifndef PLANNING_H
#define PLANNING_H

#include "Core.h"
#include "WorldProperties.h"
#include "ActionList.h"
#include <set>
#include <map>
#include <list>
#include <queue>
#include <vector>


struct Value;
class Goal;
class PlanningAction;
class PlanningComponent;
class PlanningSystem;
struct PathfindingConnection;
struct PathfindingNode;

struct Value 
{
  Value();
  Value(float);
  Value(bool);
  Value(int);
  Value(unsigned);
  Value(char);
  Value(float x, float y);
  union 
  {
    float m_float;
    bool m_bool;
    int m_int;
    unsigned m_unsigned;
    char m_char;
    struct { float m_x; float m_y; };
  };
};

//struct ValueCompare
//{
//  enum Type{Equals, GreaterThan, LessThan, LessThanOrEquals,GreaterThanOrEquals};
//  Type m_type;
//  bool Evaluate(const Value & lhs, const Value & rhs) const
//  {
//    switch (m_type)
//    {
//    case Equals: return lhs == rhs;
//    case GreaterThan: return lhs > rhs;
//
//    }
//  }
//};

typedef std::map<WorldProperty, Value> WorldState;
WorldState AmendWorldState(const WorldState & state, WorldState amendments);

class Goal
{
public:
  Goal(const char * name);
  virtual bool IsValid(const WorldState & worldState) const = 0;
  virtual float GetPriority() = 0;
  
  const PlanningComponent * GetAgent() const;

  PlanningComponent * GetAgent();
  void SetAgent(PlanningComponent * owner);

  const WorldState & GetWorldState() const;

protected:
  WorldState m_desiredState;
  PlanningComponent * m_agent;
  const char * m_name;
};

typedef std::list<const Goal*> GoalContainer; // good container for removal

struct PathfindingNode
{
  PathfindingNode();
  bool operator < (const PathfindingNode & rhs);
  void RemoveInvalidGoals(const WorldState & state);
  
  WorldState m_worldStateAmendments;
  GoalContainer m_goals;
  
  PathfindingNode * m_parent;
  PlanningAction * m_action;
};


// class ActionManager
//
// holds actions so they aren't duplicated across agents
//

class PlanningAction
{
public:
  WorldState m_effects;
  GoalContainer m_preconditions;
  virtual void Activate(PlanningComponent * agent) = 0; // ie: gotonode(#54)
};

// Todo: encapsulate into a planner class

class PlanningComponent : public Component
{
public:
  PlanningComponent();
  ~PlanningComponent();

  PlanningComponent * AddGoal (Goal * goal);
  PlanningComponent * AddAction(PlanningAction * action);
  const WorldState & GetWorldState() const;

private:
  friend class PlanningSystem;
  void Plan();
  
  const Goal * SelectBestGoal() const;

  ActionList m_actionList; // reserved for just the resulting actions of the planner
  void Update(float dt);

  WorldState m_worldState;
  std::set<Goal*> m_GoalSet;
  std::set<PlanningAction*> m_ActionSet;

  static void ClearPathNodeContainers();
  static std::priority_queue<PathfindingNode*> nodequeue;
  static std::vector<PathfindingNode*> allNodes;
};

class PlanningSystem : public System
{
public:
  PlanningSystem();
  virtual void Update(float dt);
  static PlanningSystem * Instance();
  
private:
  friend class PlanningComponent;
  std::set<PlanningComponent*> m_components;
  static PlanningSystem * s_instance;
};

#endif
