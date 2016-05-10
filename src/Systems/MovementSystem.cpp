#include "MovementSystem.hpp"
#include "..\Tilemap.hpp"
#include "..\Components.hpp"
namespace Systems
{
  MovementSystem::MovementSystem(Tilemap& theMap) :
    mTilemap(theMap)
  {

  }
  void MovementSystem::configure(entityx::EventManager &event_manager)
  {
    event_manager.subscribe<MovementEvent>(*this);
  }
  void MovementSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
  {
    entityx::ComponentHandle<c::MapObject> anMapObject;
    entityx::ComponentHandle<c::Transformable> anTransform;
    while (!mMovementQueue.empty())
    {
      MovementEvent movement = mMovementQueue.front();
      anMapObject = movement.entity.component<c::MapObject>();
      anTransform = movement.entity.component<c::Transformable>();
      GExL::Int32 anTileX = movement.target.x;
      GExL::Int32 anTileY = movement.target.y;
      if (!(mTilemap.TestTileFlag(sf::Vector3f(static_cast<float>(anTileX), static_cast<float>(anTileY), 0), Tilemap::TILE_BLOCKED) ||
        mTilemap.TestTileFlag(sf::Vector3f(static_cast<float>(anTileX), static_cast<float>(anTileY), 1), Tilemap::TILE_BLOCKED)))
      {
        anTransform->setPosition(movement.target.x*Tilemap::TileSize, movement.target.y*Tilemap::TileSize);
      }
      else
      {

      }

      mMovementQueue.pop();
    }
  }
  void MovementSystem::receive(const MovementEvent &movement) {
    mMovementQueue.push(movement);
  }
}