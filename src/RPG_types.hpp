#ifndef PLATFORMER_GRAB_TYPES_HPP_INCLUDED
#define PLATFORMER_GRAB_TYPES_HPP_INCLUDED

#include <GExL/GExL_types.hpp>
#include <entityx/entityx.h>
#include <GExL/container/TArray.hpp>
#include <SFML/Graphics.hpp>
enum STATES
{
  STATE_NONE = 0,
  STATE_INTO,
  STATE_TITLE,
  STATE_OPTIONS,
  STATE_MENU,
  STATE_GAME,
  STATE_CONSOLE,
  STATE_COUNT  
};
class IState;
class Application;
class StateManager;

class Tilemap;
typedef GExL::Uint32 typeStateID;
enum DAMAGE_TYPES {
  DAMAGE_NONE = 0x00,
  DAMAGE_MELEE = 0x01,
  DAMAGE_MAGIC = 0x02,
  DAMAGE_MISSLE = 0x04,
  DAMAGE_SLASH = 0x08,
  DAMAGE_BLUNT = 0x10,
  DAMAGE_PIERCE = 0x20,
};
enum MOVEMENT_TYPES
{
  MOVEMENT_NONE = 0x00,
  MOVEMENT_WALK_BI = 0x01,
  MOVEMENT_WALK_QUAD = 0x02,
  MOVEMENT_FLY = 0x04,
  MOVEMENT_SWIM = 0x08

};
enum MOVEMENTS_ACTIONS
{
  MOVEMENT_NORTH = 0x01,
  MOVEMENT_SOUTH = 0x02,
  MOVEMENT_EAST = 0x04,
  MOVEMENT_WEST = 0x08,
  MOVEMENT_RUN = 0x10

};
enum BEHAVIOR_FLAGS
{
  BEHAVIOR_NONE = 0x01,
  BEHAVIOR_WANDER = 0x02,
  BEHAVIOR_CONTROLLED = 0x04,
  BEHAVIOR_AGRESSIVE = 0x08,

};
struct CharacterStats
{

  CharacterStats(float thePhys = 1.0, float theIntel = 1.0, float theWit = 1.0, float theLuck = 1.0) :
    phys(thePhys),
    intel(theIntel),
    wit(theWit),
    luck(theLuck)
  {

  }
  float phys;
  float wit;
  float intel;
  float luck;
};
struct CharacterSkills
{
  CharacterSkills():
    combat(0),
    stealth(0),
    reflex(0),
    strength(0),
    fortitude(0),
    magic(0),
    lore(0),
    craft(0),
    willpower(0),
    charisma(0),
    perception(0)
  {

  }
  float combat;
  float stealth;
  float reflex;
  float strength;
  float fortitude;

  float magic;
  float lore;

  float craft;
  float willpower;
  float charisma;
  float perception;
};

#endif