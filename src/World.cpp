#include <GExL/container/TArray3D.hpp>
#include <GExL/utils/String_types.hpp>
#include "World.hpp"
#include "Components.hpp"
#include "TextureAsset.hpp"
#include "Application.hpp"
World::World(Application& theApp) :
  mWindow(theApp.mWindow),
  mTileMap(theApp)
{
  systems.add<s::BehaviorSystem>(theApp);
  systems.add<s::MovementSystem>(theApp.mWorld.mTileMap);
  systems.add<s::CollisionSystem>(theApp);
  systems.add<s::CombatSystem>(theApp);
  systems.add<s::RenderSystem>(theApp.mWindow);
  systems.configure();
}
void World::update(entityx::TimeDelta dt) {
  systems.update<s::BehaviorSystem>(0);
  systems.update<s::CollisionSystem>(0);
  systems.update<s::MovementSystem>(0);
  systems.update<s::CombatSystem>(0);
}
void World::render() {
	systems.update<s::RenderSystem>(0);
  
}
entityx::Entity World::CreatLabel(GExL::Int32 theX, GExL::Int32 theY, std::string theText)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<c::Transformable>();
  anEntity.component<c::Transformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  
  return anEntity;
}
entityx::Entity World::SpawnBackdrop(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<c::Transformable>();
  anEntity.component<c::Transformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  anEntity.assign<c::Drawable>(theTexture);
  return anEntity;
}

//Blank Genaric Object
entityx::Entity World::SpawnPrimalObject(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<c::Transformable>();
  anEntity.component<c::Transformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  anEntity.assign<c::Drawable>(theTexture);
  anEntity.assign<c::MapObject>(100.0f, 3.0f, true, 1.0f);
  return anEntity;
}
//Blank Genaric Creature
entityx::Entity World::SpawnWisp(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<c::Transformable>();
  anEntity.component<c::Transformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  anEntity.assign<c::Drawable>(theTexture);
  anEntity.assign<c::MapObject>(100.0f, 3.0f, true, 1.0f);
  return anEntity;
}

entityx::Entity World::SpawnCharacter(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture)
{
  entityx::Entity anEntity = entities.create();
  anEntity.assign<c::Transformable>();
  anEntity.component<c::Transformable>()->setPosition(sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY)));
  anEntity.assign<c::Drawable>(theTexture);
  anEntity.assign<c::MapObject>();
  return anEntity;
}
