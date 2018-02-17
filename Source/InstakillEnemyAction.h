#pragma once
#include "Planning.h"

class InstakillEnemyAction : public PlanningAction
{
public:
  InstakillEnemyAction();
  virtual void Activate(PlanningComponent * agent);
};
