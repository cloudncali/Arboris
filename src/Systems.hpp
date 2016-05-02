#ifndef SYSTEMS_HPP_INCLUDED
#define SYSTEMS_HPP_INCLUDED
#include <entityx/entityx.h>
#include <GExL/container/TArray.hpp>
#include "RPG_types.hpp"
#include <SFML/Graphics.hpp>
#include "Events.hpp"
#include "Tilemap.hpp"
#include "Console.hpp"
class RenderSystem : public entityx::System < RenderSystem > {
public:
  RenderSystem(sf::RenderWindow& theWindow);
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
private:
  GExL::Int32 mCameraX;
  GExL::Int32 mCameraY;
  entityx::Entity mCameraFocus;
  sf::RenderWindow& mWindow;
};
class DebugRenderSystem : public entityx::System < DebugRenderSystem > {
public:
  DebugRenderSystem(sf::RenderWindow& theWindow);
  void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
private:
  GExL::Int32 mCameraX;
  GExL::Int32 mCameraY;
  entityx::Entity mCameraFocus;
  sf::RenderWindow& mWindow;
};
class CombatSystem : public entityx::System <CombatSystem>, public entityx::Receiver<CombatSystem>
{
public:
  CombatSystem(Console& theConsole);
  void configure(entityx::EventManager &event_manager);
  void receive(const DamageEvent &damage);
  void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
  void Damage(entityx::Entity theEntity, float thePower, GExL::Uint32 theType);
private:
  std::queue<DamageEvent> mDamageQueue;
  Console& mConsole;
};
class MovementSystem : public entityx::System <MovementSystem>, public entityx::Receiver<MovementSystem>
{
public:
  MovementSystem(Tilemap& theMap);
  void configure(entityx::EventManager &event_manager);
  void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
  void receive(const MovementEvent &movement);
private:
  std::queue<MovementEvent> mMovementQueue;
  Tilemap& mTilemap;
};
class CollisionSystem : public entityx::System <CollisionSystem>, public entityx::Receiver <CollisionSystem>
{
public:
  CollisionSystem(Application& theApp);
  void configure(entityx::EventManager &event_manager);
  void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
  void receive(const CollisionEvent &collision);
  void receive(const MouseClickEvent &mouseclick);
private:
  Application& mApp;
  Tilemap& mTilemap;
  std::queue<MouseClickEvent> mMouseClickEvents;
};
class BehaviorSystem : public entityx::System <BehaviorSystem> , public entityx::Receiver<BehaviorSystem>
{
public:
  BehaviorSystem(Application& theApp);
  void configure(entityx::EventManager &event_manager);
  void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
  void receive(const KeyboardEvent &keyboardevent);
private:
  std::queue<KeyboardEvent> mKeyboardEventQueue;
  std::queue<entityx::Entity> mTurnOrder;
  Application& mApp;
};

#endif
