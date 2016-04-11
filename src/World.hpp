#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED
#include <entityx/entityx.h>
#include <string>

#include "tmxparser.h"
#include "Components.hpp"
#include "Systems.hpp"
#include <GExL/assets/AssetManager.hpp>
#include "Tilemap.hpp"
class World : public entityx::EntityX
{
public:
  World(Application& theApp);

	void update(entityx::TimeDelta dt);

	void render();

  entityx::Entity SpawnBackdrop(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture);
  entityx::Entity SpawnPrimalObject(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture);
  entityx::Entity SpawnCharacter(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture);
  entityx::Entity SpawnWisp(GExL::Int32 theX, GExL::Int32 theY, sf::Texture& theTexture);
  sf::RenderWindow &mWindow;
  Tilemap mTileMap;
};

#endif