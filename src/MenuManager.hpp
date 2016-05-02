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
  void CreateEntityMenu();
  void CreateActionMenu();
  void CloseEntityWindow();
  void ShowActionMenu();
  void HideActionMenu();

private:
  entityx::Entity mTargetEntity;
  Application& mApp;
  sf::View mMenuView;

  tgui::Gui mGUI;
  tgui::Panel::Ptr mActionMenu;
  tgui::ChildWindow::Ptr mEntityWindow;
  tgui::Theme::Ptr mTheme;
};
#endif

