#include "InstakillEnemyAction.h"
#include <iostream>
#include "LerpAction.h"
#include "Transform.h"

InstakillEnemyAction::InstakillEnemyAction()
{
  m_effects[TARGET_DEAD] = true;
}

void InstakillEnemyAction::Activate(PlanningComponent * agent)
{
  std::cout << "Buzzert! The enemy has been instakilled" << std::endl;

  ActionList * aList = agent->GetOwner()->GetComponent<ActionList>();
  Transform * trans = agent->GetOwner()->GetComponent<Transform>();
  if (!aList || !trans) __debugbreak();

  aList->Push(new LerpAction(trans->m_pos.x, 10, -10, 0.2f, true));

}