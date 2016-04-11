#ifndef EVENTS_HPP_INCLUDED
#define EVENTS_HPP_INCLUDED
#include "RPG_types.hpp"
#include <SFML/System.hpp>
struct CollisionEvent {
  CollisionEvent(entityx::Entity left, entityx::Entity right) : left(left), right(right) {}

  entityx::Entity left, right;
};
struct DamageEvent {
  DamageEvent(entityx::Entity theSource,sf::Vector2f theTarget, GExL::Uint32 theType, float thePower) :
  source(theSource),
  target(theTarget),
  type(theType),
  power(thePower)
  {}
  entityx::Entity source;
  sf::Vector2f target;
  GExL::Uint32 type;
  float power;
};
struct MovementEvent {
  MovementEvent(entityx::Entity theEntity, sf::Vector2f theTarget, GExL::Uint32 theType) :
    entity(theEntity),
    target(theTarget),
    type(theType)
  {}
  entityx::Entity entity;
  sf::Vector2f target;
  GExL::Uint32 type;
};

struct KeyboardEvent {
  KeyboardEvent(sf::Event& theEvent) :
    theKeyCode(static_cast<GExL::Uint32 >(theEvent.key.code))
  {
    
  }
  GExL::Uint32 theKeyCode;
};
#endif
