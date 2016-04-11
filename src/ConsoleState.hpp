#ifndef CONSOLE_STATE_HPP_INCLUDED
#define CONSOLE_STATE_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "Application.hpp"
#include "TextureAsset.hpp"
#include "FontAsset.hpp"
#include <GExL/utils/TTimer.hpp>
#include "IState.hpp"
#include "tmxparser.h"
#include "Console.hpp"
class ConsoleState : public IState
{
public:
  ConsoleState(Application& theApp);
  ~ConsoleState();
  void init();
  void handleEvent(sf::Event theEvent);
  void update(float theDeltaTime);
  void render();
  void reinit();
  void start();
  void stop();
  void RegisterConsoleCommands();
  
private:
  TextureAsset mBackgroundImage;

  
};
#endif

