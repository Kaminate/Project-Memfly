#include "LerpAction.h"

LerpAction::LerpAction(
  float & value, float begin, float end, float time, bool blocking)
  : Action(blocking)
  , m_value(value)
  , m_begin(begin)
  , m_end(end)
  , m_currTime(0)
  , m_totalTime(time)
{

}

void LerpAction::Update(float dt)
{
  // perhaps clamp to [0,1]
  m_currTime += dt;
  if (m_currTime >= m_totalTime)
  {
    m_value = m_end;
    SetFinished();
    return;
  }

  float t = m_currTime / m_totalTime;
  m_value = (1 - t) * m_begin + t * m_end;
}
