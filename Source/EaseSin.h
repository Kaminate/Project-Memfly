// TODO: replace with TweenAction

#ifndef EASE_SIN_H
#define EASE_SIN_H

#include "ActionList.h"

struct EaseSin : public Action
{
  EaseSin(float & value, float begin, float end, float time, float amplitude, float frequency, bool blocking);
  virtual void Update(float dt);
private:
  float & m_value;
  float m_begin;
  float m_end;
  float m_currTime;
  float m_totalTime;
  float m_a;
  float m_b;
};

#endif
