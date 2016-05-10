#include <GExL/utils/TTimer.hpp>
#include <entityx/deps/Dependencies.h>
#include <iostream>
#include "GExL/utils/Math_types.hpp"
#include "Application.hpp"
#include "FontHandler.hpp"
#include "TextureHandler.hpp"
#include "MusicHandler.hpp"
#include "StateManager.hpp"
#include "MenuManager.hpp"
#include "GameState.hpp"
#include "TitleState.hpp"
#include "ConsoleState.hpp"
Application::Application() :
  mRunning(false),
  mWindow(),
  mScreenWidth(800),
  mScreenHeight(600),
  mAssetManager(),
  bVSync(false),
  mPaused(false),
  mLogger("output.txt", true),
  mWorld(*this),
  mTimestep(1.0f / 60.0f),
  mConsoleFont(),
  mConsole(mConsoleFont),
  mData(*this),
  mMenuManager(*this)
{
}

Application::~Application()
{

}



int Application::run()
{
	init();
	sf::Event anEvent;
  sf::Clock anUpdateTimer;
	while (mRunning)
	{
		//UpdateState();
		//Event pull and handle
		while (mWindow.pollEvent(anEvent))
		{
			handleEvent(anEvent);
		}
    update(anUpdateTimer.getElapsedTime().asSeconds());
    anUpdateTimer.restart();
		render();
		mStateManager.UpdateStates();
		//If frame finished early
	}
	return 0;
}
void Application::init()
{
	mRunning = true;
	//Init Logger
  //Create window
  mWindow.create(sf::VideoMode(800, 600), "RPG");
	if (!mWindow.isOpen())
	{
		FLOG(GExL::StatusAppInitFailed) << "Window could not be created!" << std::endl;
		mRunning = false;
	}
  else
  {
    mConsoleFont.loadFromFile("resources/Aaargh.ttf");
    //Register Asset Handlers.
    mAssetManager.RegisterHandler(new(std::nothrow) FontHandler(128));
    mAssetManager.RegisterHandler(new(std::nothrow) TextureHandler());
    mAssetManager.RegisterHandler(new(std::nothrow) MusicHandler());
    //Register States Handlers.
    mStateManager.RegisterState(STATE_GAME, new GameState(*this));
    mStateManager.RegisterState(STATE_TITLE, new TitleState(*this));
    mStateManager.RegisterState(STATE_CONSOLE, new ConsoleState(*this));
    //Start Up State.
    mStateManager.SetNextState(STATE_GAME);
    //Entity World dependencies
    mWorld.systems.add<entityx::deps::Dependency<c::Drawable, c::Transformable>>();
    mWorld.systems.add<entityx::deps::Dependency<c::Character, c::MapObject>>();

    mMenuManager.init();
  }
  
}
void Application::initMenus()
{
  
}
void Application::handleEvent(sf::Event theEvent)
{
	//User requests quit
	if (theEvent.type == sf::Event::Closed)
	{
		mRunning = false;
	}
  if (!mPaused)
  {
    mStateManager.handleEvent(theEvent);
    mMenuManager.handleEvent(theEvent);
  }
}

void Application::update(float theDeltaTime)
{
	if (!mPaused)
  {
		mStateManager.update(theDeltaTime);
    mWorld.update(theDeltaTime);
    mMenuManager.update(theDeltaTime);
  }
}

void Application::render()
{
  mWindow.clear(sf::Color::White);
  
  mStateManager.render();
  mMenuManager.render();
  mWindow.display();
}

GExL::Uint32 Application::GetScreenWidth()
{
	return mScreenWidth;
}
GExL::Uint32 Application::GetScreenHeight()
{
	return mScreenHeight;
}
