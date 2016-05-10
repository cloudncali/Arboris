#ifndef MAPOBJECT_HPP_INCLUDED
#define MAPOBJECT_HPP_INCLUDED

#include "../RPG_types.hpp"

namespace Components
{
  struct MapObject
  {
    MapObject(float theHealth = 100.0f, float theDefense = 0.0f, bool theBlocking = false, float theWeight = 0.0f, GExL::Int32 theSize = 1, std::string theName = "") :
      health(theHealth),
      defense(theDefense),
      blocking(theBlocking),
      weight(theWeight),
      size(theSize),
      destroyed(false),
      name(theName)
    {

    }
    float health;
    float defense;
    bool blocking;
    float weight;
    GExL::Int32 size;
    bool destroyed;
    std::string name;
  };
}
#endif