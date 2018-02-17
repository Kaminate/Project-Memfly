#include "Planning.h"
#include <iostream> // debugging

// Value
Value::Value()                 : m_x(0), m_y(0){}
Value::Value(float val)        : m_float(val){}
Value::Value(bool val)         : m_bool(val){}
Value::Value(int val)          : m_int(val){}
Value::Value(unsigned val)     : m_unsigned(val){}
Value::Value(char val)         : m_char(val){}
Value::Value(float x, float y) : m_x(x), m_y(y){}

// WorldState
WorldState AmendWorldState(const WorldState & state, WorldState amendments) // copy amendments by value
{
  amendments.insert(state.begin(), state.end()); // doesn't replace any keys
  return amendments;
}

// PlanningSystem
PlanningSystem * PlanningSystem::s_instance = 0;
PlanningSystem::PlanningSystem()
{
  if (s_instance) __debugbreak();
  s_instance = this;
}
void PlanningSystem::Update(float dt)
{
  for (auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    PlanningComponent * component = *it;
    component->Update(dt);
  }
}
PlanningSystem* PlanningSystem::Instance() {return s_instance;}

// Planning Action
//PlanningAction::PlanningAction(bool blocking, PlanningComponent * agent)
//  : Action(blocking)
//  , m_agent(agent)
//{
//}
//bool PlanningAction::IsValid()
//{
//  for (auto it = m_preconditions.begin(); it != m_preconditions.end(); ++it)
//  {
//    const Goal * goal = *it;
//    if (goal->IsValid(m_agent->GetWorldState()))
//    {
//      return false;
//    }
//  }
//  return true;
//};


// PlanningComponent 
std::priority_queue<PathfindingNode*> PlanningComponent::nodequeue;
std::vector<PathfindingNode*> PlanningComponent::allNodes;

PlanningComponent::PlanningComponent()
{
  PlanningSystem::Instance()->m_components.insert(this);
}
PlanningComponent::~PlanningComponent()
{
  PlanningSystem::Instance()->m_components.erase(this); 
}
const Goal * PlanningComponent::SelectBestGoal() const
{
  Goal * bestGoal = 0; 
  float bestGoalPriority;

  for (auto it = m_GoalSet.begin(); it != m_GoalSet.end(); ++it)
  {
    Goal * goal = *it;
    if (!goal->IsValid(m_worldState))
    {
      continue;
    }

    float goalPriority = goal->GetPriority();

    if (!bestGoal || goalPriority < bestGoalPriority)
    {
      bestGoal = goal;
      bestGoalPriority = goalPriority;
    }
  }
  return bestGoal;
}
void PlanningComponent::ClearPathNodeContainers()
{
  for (auto it = allNodes.begin(); it != allNodes.end(); ++it) // delete all nodes
  {
    PathfindingNode * node = *it;
    delete node;
  }
  allNodes.clear();
  while (!nodequeue.empty())
  {
    nodequeue.pop();
  }
}
void PlanningComponent::Plan() // aka planner::formulatePlan()
{
  const Goal * bestGoal = SelectBestGoal();
  if (!bestGoal || m_ActionSet.empty())
  {
    return; // either no goals or no actions. obviously can't plan
  }
    
  PathfindingNode * goalNode = new PathfindingNode();
  goalNode->m_goals.push_back(bestGoal);
    
  allNodes.push_back(goalNode);
  nodequeue.push(goalNode);

  unsigned loopCount = 0;
  while (!nodequeue.empty())
  {
    if (loopCount++ == 50)
    {
      __debugbreak();
      ClearPathNodeContainers();
    }

    PathfindingNode * parent = nodequeue.top();
    
    if (parent->m_goals.empty()) // Found a path!
    {
      for (PathfindingNode * node = parent; node; node = node->m_parent)
      {
        if (node->m_action)
        {
          node->m_action->Activate(this);
        }
      }
      return ClearPathNodeContainers();
    }

    nodequeue.pop(); // pop it so we never consider it again (we don't want to recreate children)

    // for each of our available actions
    for (auto availableActionit = m_ActionSet.begin(); availableActionit != m_ActionSet.end(); ++availableActionit)
    {
      PlanningAction * action = *availableActionit;

      // create a pathfinding node for the action applied to reach the parent
      PathfindingNode * child = new PathfindingNode();
      child->m_parent = parent;
      child->m_action = action;

      // apply the action's effects (amend the amendments?)
      child->m_worldStateAmendments = AmendWorldState(parent->m_worldStateAmendments, action->m_effects);
          
      // about to use this
      WorldState amendedWorldState = AmendWorldState(m_worldState, child->m_worldStateAmendments);
        
      // see if it removed any goals
      child->RemoveInvalidGoals(amendedWorldState);
        
      // add any of the actions prequisite goals (if they're valid)
      const GoalContainer & actionPrereqs = action->m_preconditions;
      for (auto prereq = actionPrereqs.begin(); prereq != actionPrereqs.end(); ++prereq)
      {
        const Goal * precondition = *prereq;
        if (precondition->IsValid(amendedWorldState))
        {
          child->m_goals.push_back(precondition);
        }
      }

      // keep track of the child
      allNodes.push_back(child);
      nodequeue.push(child);

    } // for each available action
  } // while (!nodes.empty())

  // should be impossible to reach here
  __debugbreak();
}

PlanningComponent * PlanningComponent::AddGoal (Goal * goal)
{
  m_GoalSet.insert(goal);
  goal->SetAgent(this);
  return this;
}
PlanningComponent * PlanningComponent::AddAction(PlanningAction * action)
{
  m_ActionSet.insert(action);
  return this;
}
void PlanningComponent::Update(float dt)
{
  if (m_actionList.Empty())
  {
    Plan();
  }
}
const WorldState & PlanningComponent::GetWorldState() const
{
  return m_worldState;
}

// Goal
Goal::Goal(const char * name) : m_name(name) {}
const PlanningComponent * Goal::GetAgent() const { return m_agent; }
PlanningComponent * Goal::GetAgent() { return m_agent; }
void Goal::SetAgent(PlanningComponent * owner) { m_agent = owner; }
const WorldState & Goal::GetWorldState() const {return m_desiredState;}

// pathfindingnode
PathfindingNode::PathfindingNode()
  : m_parent(0)
  , m_action(0)
{
}
bool PathfindingNode::operator<(const PathfindingNode & rhs)
{
  return m_goals.size() < rhs.m_goals.size();
}
void PathfindingNode::RemoveInvalidGoals(const WorldState & state)
{
  auto it = m_goals.begin();
  while (it != m_goals.end())
  {
    const Goal * goal = *it;
    if (!goal->IsValid(state))
    {
      it = m_goals.erase(it);
    }
    else
    {
      ++it;
    }
  }
}
