#include "GameState.hpp"
#include "Application.hpp"

#include <GExL/utils/MathUtil.hpp>
#include <time.h>
GameState::GameState(Application& theApp) :
IState(theApp),
mBackgroundImage(theApp.mAssetManager, "resources/Images/bg.png", GExL::AssetLoadNow),
mTilesetImage(theApp.mAssetManager, "resources/Images/DungeonTiles.gif", GExL::AssetLoadNow),
mMainFont(theApp.mAssetManager, "resources/Aaargh.ttf", GExL::AssetLoadNow),
mPlayerImage(theApp.mAssetManager, "resources/Images/CharacterTiles.png", GExL::AssetLoadNow),
mDebugImage(theApp.mAssetManager, "resources/Images/DebugTiles.png", GExL::AssetLoadNow)
{

}
GameState::~GameState()
{

}
void GameState::init()
{
	srand(GExL::Uint32(time(NULL)));
  mBackgroundImage.GetAsset().setRepeated(true);
  mTilesetImage.GetAsset().setSmooth(false);
  tmxparser::parseFromFile("resources/Maps/Hayold.tmx", &mMapAsset, "resources/Images");
  mApp.mWorld.mTileMap.ParseMap(mMapAsset);
  mApp.mConsole.setBackgroundColor(sf::Color(0u, 0u, 0u, 0u));
  mApp.mConsole.show();
}
void GameState::reinit()
{
}
void GameState::handleEvent(sf::Event theEvent)
{
  if (theEvent.type == sf::Event::KeyReleased)
  {
    if (theEvent.key.code == sf::Keyboard::Tilde)
    {
      if (mApp.mStateManager.GetCurrentSubState() == STATE_NONE)
      {
        mApp.mStateManager.SetNextSubState(STATE_CONSOLE);
      }
    }
    KeyboardEvent anKeyboardEvent(theEvent);
    mApp.mWorld.events.emit<KeyboardEvent>(anKeyboardEvent);
  }
  if (theEvent.type == sf::Event::MouseButtonPressed)
  {
    mApp.mWorld.events.emit<MouseClickEvent>(MouseClickEvent(theEvent));
  }
}
void GameState::update(float theDeltaTime)
{
  
}
void GameState::render()
{
  mApp.mWorld.render();
  mApp.mWindow.draw(mApp.mConsole);
}
void GameState::start()
{
}
void GameState::stop()
{
}