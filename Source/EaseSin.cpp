#include "EaseSin.h"

EaseSin::EaseSin(
  float & value, 
  float begin, 
  float end, 
  float time, 
  float amplitude, 
  float frequency, 
  bool blocking)
  : Action(blocking)
  , m_value(value)
  , m_begin(begin)
  , m_end(end)
  , m_currTime(0)
  , m_totalTime(time)
  , m_a(amplitude)
  , m_b(6.2831853071f * frequency) // b = 2 * pi * frequency
{

}

void EaseSin::Update(float dt)
{
  // todo:

  // m_currTime += dt;
  // if (m_currTime >= m_totalTime)
  // {
  //   m_value = m_end;
  //   SetFinished();
  //   return;
  // }

  // float t = m_currTime / m_totalTime;
  //m_value = (1 - t) * m_begin + t * m_end;
}
