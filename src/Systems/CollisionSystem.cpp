#include "CollisionSystem.hpp"
#include "../Components.hpp"
#include "../Application.hpp"
namespace Systems
{
  CollisionSystem::CollisionSystem(Application& theApp) :
    mApp(theApp),
    mTilemap(theApp.mWorld.mTileMap)
  {

  }
  void CollisionSystem::configure(entityx::EventManager &event_manager)
  {
    event_manager.subscribe<CollisionEvent>(*this);
    event_manager.subscribe<MouseClickEvent>(*this);
  }
  void CollisionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
  {

    entityx::ComponentHandle<c::MapObject> anPhyiscal;
    entityx::ComponentHandle<c::Transformable> anTransform;
    mTilemap.SetTileLayerFlag(1, Tilemap::TILE_NONE);
    for (entityx::Entity entity : es.entities_with_components(anPhyiscal, anTransform)) {
      mTilemap.SetTileFlag(sf::Vector3i(static_cast<GExL::Int32>(anTransform->getPosition().x / Tilemap::TileSize),
        static_cast<GExL::Int32>(anTransform->getPosition().y / Tilemap::TileSize), 1), Tilemap::TILE_BLOCKED);
    }
    while (!mMouseClickEvents.empty())
    {
      MouseClickEvent anMouseClickEvent = mMouseClickEvents.front();
      if (anMouseClickEvent.mButton == sf::Mouse::Left)
      {
        for (entityx::Entity entity : es.entities_with_components(anPhyiscal, anTransform)) {
          sf::FloatRect anClickArea;
          anClickArea.left = anTransform->getPosition().x;
          anClickArea.top = anTransform->getPosition().y;
          anClickArea.width = Tilemap::TileSize*anPhyiscal->size;
          anClickArea.height = Tilemap::TileSize*anPhyiscal->size;
          if (anClickArea.contains(anMouseClickEvent.mPosition))
          {
            mApp.mMenuManager.SetTargetEntity(entity);

            break;
          }
        }
      }
      mMouseClickEvents.pop();
    }
  }

  void CollisionSystem::receive(const CollisionEvent &collision) {

  }
  void CollisionSystem::receive(const MouseClickEvent &mouseclick)
  {
    mMouseClickEvents.push(mouseclick);
  }
}