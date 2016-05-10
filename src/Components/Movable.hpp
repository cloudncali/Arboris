#ifndef MOVABLE_HPP_INCLUDED
#define MOVABLE_HPP_INCLUDED
#include "../RPG_types.hpp"

namespace Components
{

  struct Movable
  {

    Movable(GExL::Uint32 theType = MOVEMENT_WALK_BI, float theSpeed = 1.0f) :
      type(theType),
      speed(theSpeed)
    {

    }
    GExL::Uint32 type;
    float speed;
  };

}
#endif