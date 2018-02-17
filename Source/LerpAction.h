// TODO: replace with TweenAction

#ifndef LERPACTION_H
#define LERPACTION_H

#include "ActionList.h"

struct LerpAction : public Action
{
  LerpAction(float & value, float begin, float end, float time, bool blocking);
  virtual void Update(float dt);
private:
  float & m_value;
  float m_begin;
  float m_end;
  float m_currTime;
  float m_totalTime;
};

#endif
