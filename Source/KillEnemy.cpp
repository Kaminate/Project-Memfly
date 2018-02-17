#include "KillEnemy.h"

KillEnemyGoal::KillEnemyGoal() : Goal("Dispatch enemy")
{
  m_desiredState[TARGET_DEAD] = true;
}

bool KillEnemyGoal::IsValid(const WorldState & state) const
{
  // return !!agent->currTarget;
  return true;
}

float KillEnemyGoal::GetPriority()
{
  return 1;
}
