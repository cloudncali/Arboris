#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED
#include "../RPG_types.hpp"

namespace Components
{
  struct Character
  {
    Character(CharacterStats theStats = CharacterStats(), CharacterSkills theSkills = CharacterSkills(), float theHealth = 100.0f, float theEnergy = 100.0f, GExL::Uint32 theBehaviorFlags = BEHAVIOR_NONE) :
      energy(theEnergy),
      behaviorFlags(theBehaviorFlags),
      stats(theStats),
      skills(theSkills)
    {

    }
    float energy;
    CharacterStats stats;
    CharacterSkills skills;
    GExL::Uint32 behaviorFlags;
  };
}
#endif