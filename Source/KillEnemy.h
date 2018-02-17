#ifndef KILL_ENEMY_H 
#define KILL_ENEMY_H

#include "Planning.h"

class KillEnemyGoal : public Goal
{
public:
  KillEnemyGoal();
  virtual bool IsValid(const WorldState & state) const;
  virtual float GetPriority();
};

#endif
