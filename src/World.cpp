#include <GExL/container/TArray3D.hpp>
#include <GExL/utils/String_types.hpp>
#include "World.hpp"
#include "Components.hpp"
#include "TextureAsset.hpp"
#include "Box2dUtil.hpp"
#include "Application.hpp"
World::World(Application& theApp) :
  mWindow(theApp.mWindow),
  mTileMap(theApp)
{
  systems.add<BehaviorSystem>(theApp);
  systems.add<MovementSystem>(theApp.mWorld.mTileMap);
  systems.add<CollisionSystem>(theApp.mWorld.mTileMap);
  systems.add<CombatSystem>(theApp.mConsole);
  systems.add<RenderSystem>(theApp.mWindow);
  systems.add<DebugRenderSystem>(theApp.mWindow);
  systems.configure();
}
void World::update(entityx::TimeDelta dt) {
  systems.update<BehaviorSystem>(0);
  systems.update<CollisionSystem>(0);
  systems.update<MovementSystem>(0);
  systems.update<CombatSystem>(0);
}
void World::render() {
	systems.update<RenderSystem>(0);
  systems.update<DebugRenderSystem>(0);
  
}
entityx::Entity World::SpawnBackdrop(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<EntityTransformable>();
  anEntity.component<EntityTransformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  anEntity.assign<EntityRender>(theTexture);
  return anEntity;
}

//Blank Genaric Object
entityx::Entity World::SpawnPrimalObject(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<EntityTransformable>();
  anEntity.component<EntityTransformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  anEntity.assign<EntityRender>(theTexture);
  anEntity.assign<EntityPhysical>(100.0f, 3.0f, true, 1.0f);
  return anEntity;
}
//Blank Genaric Creature
entityx::Entity World::SpawnWisp(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<EntityTransformable>();
  anEntity.component<EntityTransformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  anEntity.assign<EntityRender>(theTexture);
  anEntity.assign<EntityPhysical>(100.0f, 3.0f, true, 1.0f);
  return anEntity;
}

entityx::Entity World::SpawnCharacter(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<EntityTransformable>();
  anEntity.component<EntityTransformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  anEntity.assign<EntityRender>(theTexture);
  anEntity.assign<EntityPhysical>();
  return anEntity;
}
