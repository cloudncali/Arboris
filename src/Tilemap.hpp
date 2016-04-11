#ifndef TILE_MAP_HPP_INCLUDED
#define TILE_MAP_HPP_INCLUDED
#include <SFML/System.hpp>
#include "RPG_types.hpp"
#include "tmxparser.h"
#include <GExL/container/TArray3D.hpp>
class Tilemap
{
public:
  enum TILE_FLAGS
  {
    TILE_NONE = 0x00,
    TILE_BLOCKED = 0x01,
    TILE_WARP = 0x02,
    TILE_DOOR = 0x04,
  };

  static const GExL::Uint32 MaxMapSize = 100; //Max Map Size in Tiles (both width and height)
  static const GExL::Uint32 TileSize = 32; //TileSize in Pixels
  static const GExL::Uint32 ChunkSize = 25; //ChunkSize in Tiles
  Tilemap(Application &theApp);
  void ParseMap(tmxparser::TmxMap& theMapData);
  bool TestTileFlag(sf::Vector3f theTile, GExL::Uint32 theFlag);
  void SetTileFlag(sf::Vector3i theTile, GExL::Uint32 theFlag);
  void SetTileLayerFlag(GExL::Uint32 theLayer, GExL::Uint32 theFlag);
private:
  GExL::TArray3D<GExL::Uint32> mTileFlags;
  Application &mApp;
};
#endif
