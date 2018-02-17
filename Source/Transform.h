#ifndef TRANSFORMH
#define TRANSFORMH

#include "Core.h"
#include "Point4.h"

class Transform : public Component
{
public:
  Transform(float x = 0, float y = 0);
  // unit: arbitrary units.
  // Physics has a units->meter conversino
  // Graphics works on arbitrary units?
  Point4 m_pos; 
};

#endif
