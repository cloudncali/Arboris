#ifndef TITLE_STATE_HPP_INCLUDED
#define TITLE_STATE_HPP_INCLUDED
#include <SFML/Window.hpp>
#include "Application.hpp"
#include "TextureAsset.hpp"
#include "FontAsset.hpp"
#include <GExL/utils/TTimer.hpp>
#include "IState.hpp"
class TitleState : public IState
{
public:
  TitleState(Application& theApp);
  ~TitleState();
  void init();
  void handleEvent(sf::Event theEvent);
  void update(float theDeltaTime);
  void render();
  void reinit();
  void start();
  void stop();
private:
  TextureAsset mBackgroundImage;
  FontAsset mMainFont;
};
#endif