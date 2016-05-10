#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <GExL/assets/AssetManager.hpp>
#include <GExL/logger/FileLogger.hpp>
#include <GExL/container/TArray.hpp>
#include <SFML/Graphics.hpp>
#include "RPG_types.hpp"
#include "StateManager.hpp"
#include "World.hpp"
#include "Console.hpp"
#include "FontAsset.hpp"
#include "DataParser.hpp"
#include <TGUI/TGUI.hpp>
#include "MenuManager.hpp"
class Application
{
public:
	//Contructors  etc
	Application();
	~Application();
	int run();

	//Access methods
	GExL::Uint32 GetScreenWidth();
	GExL::Uint32 GetScreenHeight();
  
	//public variables
  sf::RenderWindow mWindow;
  //Managers
	GExL::AssetManager mAssetManager;
	//Temp Game class until state machine is done.
  //Primary classes
	StateManager mStateManager;
	World mWorld;
  Console mConsole;
  DataParser mData;
  MenuManager mMenuManager;
protected:
	virtual void init();
  virtual void initMenus();
	virtual void handleEvent(sf::Event theEvent);
	virtual void update(float theDeltaTime);
	virtual void render();

private:
	//The window renderer
	
	bool mPaused;
	bool mRunning;
	unsigned int mScreenWidth;
	unsigned int mScreenHeight;
	GExL::Uint32 mFPS;
	GExL::Uint32 mTPF;
  float mTimestep;
	bool bVSync;
	GExL::FileLogger mLogger;
  sf::Font mConsoleFont;
  
};


#endif