#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "Application.hpp"
#include "TextureAsset.hpp"
#include "FontAsset.hpp"
#include <GExL/utils/TTimer.hpp>
#include "IState.hpp"
#include "tmxparser.h"
#include "Tilemap.hpp"

class GameState : public IState
{
public:
	GameState(Application& theApp);
	~GameState();
	void init();
	void handleEvent(sf::Event theEvent);
	void update(float theDeltaTime);
	void render();
	void reinit();
	void start();
	void stop();

private:
	entityx::Entity mPlayerEntity;
  entityx::Entity mBackdropEntity;
	TextureAsset mBackgroundImage;
  TextureAsset mTilesetImage;
  TextureAsset mPlayerImage;
  TextureAsset mDebugImage;
  FontAsset mMainFont;
  entityx::Entity mEntity;
  tmxparser::TmxMap mMapAsset;
};
#endif