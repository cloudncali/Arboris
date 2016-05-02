#include "MenuManager.hpp"
#include "Application.hpp"
#include <GExL/utils/String_types.hpp>
#include <GExL/utils/MathUtil.hpp>
#include <time.h>
#include "Tilemap.hpp"
MenuManager::MenuManager(Application& theApp) :
  mApp(theApp)  
{

}
MenuManager::~MenuManager()
{

}
void MenuManager::init()
{
  FontAsset MenuFont(mApp.mAssetManager, "resources/Aaargh.ttf", GExL::AssetLoadNow);
  mGUI.setWindow(mApp.mWindow);
  mGUI.setFont(MenuFont.GetAsset());
  mTheme= std::make_shared<tgui::Theme>("resources/Images/GUITheme.txt");
  CreateActionMenu();
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
  if (mTargetEntity.valid())
  {
    if (mTargetEntity.has_component<EntityPhysical>())
    {
      tgui::Label::Ptr anName, anCon, anToughness, anPhys, anWit, anIntel;
      if (mEntityWindow != NULL)
      {
        mEntityWindow->show();
        anName = mEntityWindow->get<tgui::Label>("NameLabel");
        anCon = mEntityWindow->get<tgui::Label>("ConLabel", true);
        anToughness = mEntityWindow->get<tgui::Label>("ToughnessLabel", true);
        entityx::ComponentHandle<EntityPhysical> anPhysical = mTargetEntity.component<EntityPhysical>();
        entityx::ComponentHandle<EntityTransformable> anTransform = mTargetEntity.component<EntityTransformable>();
        anName->setText(anPhysical->name);
        anCon->setText(GExL::FloatParser::ToString(anPhysical->condition));
        anToughness->setText(GExL::FloatParser::ToString(anPhysical->toughness));
        
      }
      if (mActionMenu != NULL)
      {
        entityx::ComponentHandle<EntityPhysical> anPhysical = mTargetEntity.component<EntityPhysical>();
        entityx::ComponentHandle<EntityTransformable> anTransform = mTargetEntity.component<EntityTransformable>();
        sf::Vector2f anPosition = anTransform->getPosition();
        anPosition.x -= 30;
        anPosition.y -= 75-((anPhysical->size*32)/2);
        mActionMenu->setPosition(anPosition);
      }
    }
  }
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
  mTargetEntity = theTargetEntity;
 
  ShowActionMenu();

}
void MenuManager::CreateEntityMenu()
{
    mEntityWindow = mTheme->load("ChildWindow");
    mEntityWindow->setPosition(10, 10);
    mEntityWindow->setSize(200, 300);

    tgui::Label::Ptr anNameLabel = mTheme->load("Label");
    anNameLabel->setTextSize(26);
    anNameLabel->setText("Name");
    anNameLabel->setPosition(0, 0);

    tgui::HorizontalLayout::Ptr anVitalLayout = std::make_shared<tgui::HorizontalLayout>();
    anVitalLayout->setPosition(8, 26);
    anVitalLayout->setSize(94, 32);

    tgui::Label::Ptr anConLabel = mTheme->load("Label");
    anConLabel->setTextSize(24);
    anConLabel->setText("Con");
    anConLabel->setPosition(0, 0);
    anVitalLayout->add(anConLabel, "ConLabel");

    tgui::Label::Ptr anToughnessLabel = mTheme->load("Label");
    anToughnessLabel->setTextSize(24);
    anToughnessLabel->setText("T");
    anToughnessLabel->setPosition(32, 0);
    anVitalLayout->add(anToughnessLabel, "ToughnessLabel");

    tgui::VerticalLayout::Ptr anStatsLayout = std::make_shared<tgui::VerticalLayout>();
    anStatsLayout->setPosition(8, 64);
    anStatsLayout->setSize(75, 60);

    tgui::Label::Ptr anPhysLabel = mTheme->load("Label");
    anPhysLabel->setTextSize(20);
    anStatsLayout->add(anPhysLabel);

    tgui::Label::Ptr anIntelLabel = mTheme->load("Label");
    anIntelLabel->setTextSize(20);
    anStatsLayout->add(anIntelLabel);
    //Wit Label
    tgui::Label::Ptr anWitLabel = mTheme->load("Label");
    anWitLabel->setTextSize(20);
    anStatsLayout->add(anWitLabel);
    tgui::Button::Ptr anCloseButton= mTheme->load("ChildWindowCloseButton");
    anCloseButton->connect("pressed", &MenuManager::CloseEntityWindow, this);
    mEntityWindow->setCloseButton(anCloseButton);

    mEntityWindow->add(anNameLabel, "NameLabel");
    mEntityWindow->add(anVitalLayout, "VitalLayout");
    mEntityWindow->add(anStatsLayout, "StatsLayout");

    mGUI.add(mEntityWindow, "EntityWindow");

    mActionMenu->hide();
}
void MenuManager::CreateActionMenu()
{
  if (mActionMenu == NULL)
  {
    mActionMenu = std::make_shared<tgui::Panel>();
    mActionMenu->setPosition(0, 0);
    mActionMenu->setSize(150, 150);

    mActionMenu->setBackgroundColor(tgui::Color(0, 0, 0, 100));
    tgui::Button::Ptr anLookButton = mTheme->load("Button");
    mActionMenu->add(anLookButton, "LookButton");
    anLookButton->setPosition(70, 0);
    anLookButton->setSize(60, 40);
    anLookButton->setText("Look");
    anLookButton->connect("pressed", &MenuManager::CreateEntityMenu,this);
    tgui::Button::Ptr anCancelButton = mTheme->load("Button");
    mActionMenu->add(anCancelButton, "CancelButton");
    anCancelButton->setPosition(80, 45);
    anCancelButton->setSize(60, 40);
    anCancelButton->setText("Cancel");
    anCancelButton->connect("pressed", &MenuManager::HideActionMenu, this);
    mGUI.add(mActionMenu, "ActionMenu");
  }
}
void MenuManager::CloseEntityWindow()
{
  mEntityWindow->hide();
}
void MenuManager::ShowActionMenu()
{
  mActionMenu->show();
}
void MenuManager::HideActionMenu()
{
  mActionMenu->hide();
}