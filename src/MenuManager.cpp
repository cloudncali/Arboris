#include "MenuManager.hpp"
#include "Application.hpp"
#include <GExL/utils/String_types.hpp>
#include <GExL/utils/MathUtil.hpp>
#include <time.h>
#include "Tilemap.hpp"
MenuManager::MenuManager(Application& theApp) :
  mApp(theApp)
{
  mGUI.setWindow(mApp.mWindow);
}
MenuManager::~MenuManager()
{

}
void MenuManager::init()
{
  FontAsset anMenuFont(mApp.mAssetManager, "resources/Aaargh.ttf", GExL::AssetLoadNow);
  
  auto anTheme = std::make_shared<tgui::Theme>("resources/Images/Black.txt");
  tgui::ChildWindow::Ptr anMenu = anTheme->load("ChildWindow");
  anMenu->setPosition(10, 10);
  tgui::Label::Ptr anNameLabel = anTheme->load("Label");
  
  tgui::VerticalLayout::Ptr anStatsLayout = std::make_shared<tgui::VerticalLayout>();
  anStatsLayout->setPosition(8, 24);
  anStatsLayout->setSize(75, 60);
  tgui::Label::Ptr anPhysLabel = anTheme->load("Label");
  anPhysLabel->setTextSize(16);
  anPhysLabel->setFont(anMenuFont.GetAsset());
  anStatsLayout->add(anPhysLabel);
  tgui::Label::Ptr anIntelLabel = anTheme->load("Label");
  anIntelLabel->setTextSize(16);
  anIntelLabel->setFont(anMenuFont.GetAsset());
  anStatsLayout->add(anIntelLabel);
  tgui::Label::Ptr anWitLabel = anTheme->load("Label");
  anWitLabel->setTextSize(16);
  anWitLabel->setFont(anMenuFont.GetAsset());
  anStatsLayout->add(anWitLabel);
  
  anNameLabel->setText("Name");
  anNameLabel->setFont(anMenuFont.GetAsset());
  anNameLabel->setTextSize(16);
  anNameLabel->setPosition(0, 0);
  
  anMenu->add(anNameLabel, "NameLabel");
  anMenu->add(anStatsLayout, "StatsLayout");
  
  mGUI.add(anMenu);
}
void MenuManager::reinit()
{
}
void MenuManager::handleEvent(sf::Event theEvent)
{
  mGUI.handleEvent(theEvent);
}
void MenuManager::update(float theDeltaTime)
{
  //mConsole.
}
void MenuManager::render()
{
  mGUI.draw();
}
void MenuManager::start()
{

}
void MenuManager::stop()
{

}
void MenuManager::SetTargetEntity(entityx::Entity theTargetEntity)
{
  //mTargetEntity = theTargetEntity;
  //tgui::ChildWindow::Ptr anWindow = mGUI.get<tgui::ChildWindow>("CharacterWindow");
  //tgui::Label::Ptr anWindow = anWindow.get<tgui::("CharacterWindow");
}