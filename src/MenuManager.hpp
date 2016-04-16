#ifndef MENU_MANAGER_HPP_INCLUDED
#define MENU_MANAGER_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "RPG_types.hpp"
#include "TextureAsset.hpp"
#include "FontAsset.hpp"
#include <GExL/utils/TTimer.hpp>
#include <entityx/entityx.h>
#include <TGUI/TGUI.hpp>
class MenuManager
{
public:
  MenuManager(Application& theApp);
  ~MenuManager();
  void init();
  void handleEvent(sf::Event theEvent);
  void update(float theDeltaTime);
  void render();
  void reinit();
  void start();
  void stop();
  void SetTargetEntity(entityx::Entity theTargetEntity);
private:
  
  entityx::Entity mTargetEntity;
  tgui::Gui mGUI;
  Application& mApp;
};
#endif

