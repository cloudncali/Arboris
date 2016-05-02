#include "Tilemap.hpp"
#include <entityx\entityx.h>
#include <GExL/utils/String_types.hpp>
#include "TextureAsset.hpp"
#include "Components.hpp"
#include "Application.hpp"

Tilemap::Tilemap(Application &theApp) :
  mApp(theApp),
  mTileFlags(2, 100, 100)
{
  for (GExL::Uint32 x = 0; x < mTileFlags.columns(); ++x)
  {
    for (GExL::Uint32 y = 0; y < mTileFlags.rows(); ++y)
    {
      mTileFlags[0][y][x] = TILE_NONE;
      mTileFlags[1][y][x] = TILE_NONE;
    }
  }
}
void Tilemap::ParseMap(tmxparser::TmxMap& theMapData)
{
  GExL::Uint32 anTileIndex = 0;
  GExL::Uint32 anLayerIndex = 0;
  TextureAsset anTextureAsset(mApp.mAssetManager, theMapData.propertyMap["tiletexture"], GExL::AssetLoadNow);
  sf::Texture &anTexture = anTextureAsset.GetAsset();

  const GExL::Uint32 anMapWidth = theMapData.width;
  const GExL::Uint32 anMapHeight = theMapData.height;

  GExL::TArray3D<entityx::Entity> anChunkArray(theMapData.layerCollection.size() + 1,anMapHeight / ChunkSize + 1, anMapWidth / ChunkSize + 1);
  for (GExL::Uint32 anLayer = 0; anLayer < anChunkArray.levels(); ++anLayer)
  {
    for (GExL::Uint32 anChunkY = 0; anChunkY < anChunkArray.rows(); ++anChunkY)
    {
      for (GExL::Uint32 anChunkX = 0; anChunkX < anChunkArray.columns(); ++anChunkX)
      {
        anChunkArray[anLayer][anChunkY][anChunkX] = mApp.mWorld.entities.create();
        anChunkArray[anLayer][anChunkY][anChunkX].assign<EntityTransformable>();

        anChunkArray[anLayer][anChunkY][anChunkX].assign<EntityRender>(anTexture);
        entityx::ComponentHandle<EntityTransformable> anTransform = anChunkArray[anLayer][anChunkY][anChunkX].component<EntityTransformable>();
        entityx::ComponentHandle<EntityRender> anRender = anChunkArray[anLayer][anChunkY][anChunkX].component<EntityRender>();
        anTransform->setPosition(sf::Vector2f(static_cast<float>( anChunkX * TileSize * ChunkSize), static_cast<float>(anChunkY * TileSize * ChunkSize)));

        anRender->mVertices.clear();
        anRender->mVertices.setPrimitiveType(sf::Quads);


      }
    }
  }
  for (auto it = theMapData.layerCollection.begin(); it != theMapData.layerCollection.end(); ++it)
  {
    for (auto it2 = it->tiles.begin(); it2 != it->tiles.end(); ++it2)
    {
      if (it2->gid>0)
      {
        GExL::Uint32 anTileGID = it2->gid - theMapData.tilesetCollection.at(it2->tilesetIndex).firstgid;
        GExL::Uint32 anTilesetWidth = theMapData.tilesetCollection.at(it2->tilesetIndex).colCount;
        GExL::Int32 anTileSourceX = anTileGID % anTilesetWidth;
        GExL::Int32 anTileSourceY = anTileGID / anTilesetWidth;
        GExL::Int32 anTileDestX = anTileIndex % anMapWidth;
        GExL::Int32 anTileDestY = anTileIndex / anMapWidth;
        GExL::Uint32 anChunkX = anTileDestX / ChunkSize;
        GExL::Uint32 anChunkY = anTileDestY / ChunkSize;
        sf::Vector2f anFinalPos = sf::Vector2f((static_cast<float>(anTileDestX - (anChunkX * ChunkSize)) * TileSize),
          static_cast<float>((anTileDestY - (anChunkY * ChunkSize)) * TileSize));
        entityx::ComponentHandle<EntityRender> anRender = anChunkArray[anLayerIndex][anChunkY][anChunkX].component<EntityRender>();
        anRender->mVertices.append(sf::Vertex(anFinalPos,
          sf::Vector2f(static_cast<float>(anTileSourceX * TileSize), static_cast<float>(anTileSourceY * TileSize))));
        anRender->mVertices.append(sf::Vertex(anFinalPos + sf::Vector2f(static_cast<float>(TileSize), 0.0f),
          sf::Vector2f(static_cast<float>(anTileSourceX * TileSize), static_cast<float>(anTileSourceY * TileSize)) + sf::Vector2f(static_cast<float>(TileSize), 0.0f)));
        anRender->mVertices.append(sf::Vertex(anFinalPos + sf::Vector2f(static_cast<float>(TileSize), static_cast<float>(TileSize)),
          sf::Vector2f(static_cast<float>(anTileSourceX * TileSize), static_cast<float>(anTileSourceY * TileSize)) + sf::Vector2f(static_cast<float>(TileSize), static_cast<float>(TileSize))));
        anRender->mVertices.append(sf::Vertex(anFinalPos + sf::Vector2f(0.0f, static_cast<float>(TileSize)),
          sf::Vector2f(static_cast<float>(anTileSourceX * TileSize), static_cast<float>(anTileSourceY * TileSize)) + sf::Vector2f(0.0f, TileSize)));
        mTileFlags[0][anTileDestY / TileSize][anTileDestX / TileSize] = TILE_NONE;
        if(theMapData.tilesetCollection.at(it2->tilesetIndex).tileDefinitions[anTileGID].propertyMap["blocking"]==GExL::BoolParser::ToString(true))
        {
          mTileFlags[0][anTileDestY][anTileDestX] |= TILE_BLOCKED;
        }
      }
      anTileIndex++;
    }
    anTileIndex = 0;
    anLayerIndex++;
  }
  entityx::Entity anEntity;
  for (auto it = theMapData.objectGroupCollection.begin(); it != theMapData.objectGroupCollection.end(); ++it)
  {
    for (auto it2 = it->objects.begin(); it2 != it->objects.end(); ++it2)
    {
      if (GExL::StringToLowercase(it2->type) == "character")
      {
        if (it2->propertyMap.find("characterdata") != it2->propertyMap.end())
        {
          anEntity = mApp.mWorld.entities.create();
          mApp.mData.ParseCharacter(it2->propertyMap["characterdata"], anEntity);
          anEntity.component<EntityTransformable>()->setPosition(sf::Vector2f(it2->x, it2->y));
          ParseCharacterData(anEntity, it2->propertyMap);
        }
      }
    }
    anTileIndex = 0;
    anLayerIndex++;
  }

}
bool Tilemap::TestTileFlag(sf::Vector3f theTile, GExL::Uint32 theFlag)
{
  bool anResult = false;
  if (theTile.x > 0 && theTile.x < mTileFlags.columns() && theTile.y > 0 && theTile.y < mTileFlags.rows())
  {
    if (mTileFlags[theTile.z][theTile.y][theTile.x] & theFlag)
    {
      anResult = true;
    }
  }
  return anResult;
}
void Tilemap::SetTileFlag(sf::Vector3i theTile, GExL::Uint32 theFlag)
{
  if (theTile.x < mTileFlags.columns() && theTile.y < mTileFlags.rows() &&
    theTile.z<mTileFlags.levels() && theTile.x >= 0 && theTile.y >= 0 &&
    theTile.z >= 0)
  {
    mTileFlags[theTile.z][theTile.y][theTile.x] = theFlag;
  }
}
void Tilemap::SetTileLayerFlag(GExL::Uint32 theLayer, GExL::Uint32 theFlag)
{
  if (theLayer<mTileFlags.levels() && theLayer>= 0)
  {
    for (GExL::Uint32 anTileY = 0; anTileY < mTileFlags.rows(); ++anTileY)
    {
      for (GExL::Uint32 anTileX = 0; anTileX < mTileFlags.columns(); ++anTileX)
      {
        mTileFlags[theLayer][anTileY][anTileX] = theFlag;
      }
    }
  }
}
void Tilemap::ParseCharacterData(entityx::Entity theCharacter, tmxparser::TmxPropertyMap_t theData)
{
  

  //Parse for characterFlags
  if (theData.find("controlled") != theData.end())
  {
    if (GExL::BoolParser::ToValue(theData["controlled"], false))
    {
      theCharacter.component<EntityAlive>()->behaviorFlags |= BEHAVIOR_CONTROLLED;
    }
    else
    {
      theCharacter.component<EntityAlive>()->behaviorFlags &= BEHAVIOR_CONTROLLED;
    }
  }

  if (theData.find("wander") != theData.end())
  {
    if (GExL::BoolParser::ToValue(theData["wander"], false))
    {
      theCharacter.component<EntityAlive>()->behaviorFlags |= BEHAVIOR_WANDER;
    }
    else
    {
      theCharacter.component<EntityAlive>()->behaviorFlags &= BEHAVIOR_WANDER;
    }
  }
}