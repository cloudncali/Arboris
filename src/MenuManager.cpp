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
  CreateHUD();
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
    if (mTargetEntity.has_component<c::MapObject>())
    {
      tgui::Label::Ptr anName, anCon, anToughness, anPhys, anWit, anIntel;
      tgui::ChildWindow::Ptr anEntityWindow = mGUI.get<tgui::ChildWindow>("EntityWindow");
      if (anEntityWindow!=nullptr)
      {
        anEntityWindow->show();
        anName = anEntityWindow->get<tgui::Label>("NameLabel");
        anCon = anEntityWindow->get<tgui::Label>("ConLabel", true);
        anToughness = anEntityWindow->get<tgui::Label>("ToughnessLabel", true);
        entityx::ComponentHandle<c::MapObject> anMapObject = mTargetEntity.component<c::MapObject>();
        entityx::ComponentHandle<c::Transformable> anTransform = mTargetEntity.component<c::Transformable>();
        anName->setText(anMapObject->name);
        std::stringstream anConText;
        anConText << "HP: " << GExL::FloatParser::ToString(static_cast<GExL::Int32>(anMapObject->health));
        anCon->setText(anConText.str());
        std::stringstream anToughText;
        anToughText << "DEF: " << GExL::FloatParser::ToString(static_cast<GExL::Int32>(anMapObject->defense));
        anToughness->setText(anToughText.str());

      }
    }
  }
}
void MenuManager::render()
{
  if (mTargetEntity != NULL)
  {
    sf::RectangleShape anTarget;
    anTarget.setPosition(mTargetEntity.component<c::Transformable>()->getPosition());
    anTarget.setSize(sf::Vector2f(32, 32));
    anTarget.setOutlineColor(sf::Color::Red);
    anTarget.setFillColor(sf::Color::Transparent);
    anTarget.setOutlineThickness(3);
    mApp.mWindow.draw(anTarget);
  }
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

}
void MenuManager::SetPlayerEntity(entityx::Entity thePlayerEntity)
{
  mPlayerEntity = thePlayerEntity;
}
void MenuManager::CreateEntityMenu()
{
  tgui::ChildWindow::Ptr anEntityWindow = mGUI.get<tgui::ChildWindow>("EntityWindow");
  if (anEntityWindow == NULL)
  {
    anEntityWindow = mTheme->load("ChildWindow");
    anEntityWindow->setPosition(10, 10);
    anEntityWindow->setSize(200, 100);

      tgui::Label::Ptr anNameLabel = mTheme->load("Label");
      anNameLabel->setTextSize(26);
      anNameLabel->setText("Name");
      anNameLabel->setPosition(0, 0);

      tgui::Label::Ptr anConLabel = mTheme->load("Label");
      anConLabel->setTextSize(24);
      anConLabel->setText("HP: 0");
      anConLabel->setPosition(5, 30);
      anEntityWindow->add(anConLabel, "ConLabel");

      tgui::Label::Ptr anToughnessLabel = mTheme->load("Label");
      anToughnessLabel->setTextSize(24);
      anToughnessLabel->setText("Def: 0");
      anToughnessLabel->setPosition(5, 60);
      anEntityWindow->add(anToughnessLabel, "ToughnessLabel");

      anEntityWindow->add(anNameLabel, "NameLabel");

      mGUI.add(anEntityWindow, "EntityWindow");
    }
}
void MenuManager::CreateCharacterMenu()
{
  tgui::ChildWindow::Ptr anEntityWindow = mGUI.get<tgui::ChildWindow>("EntityWindow");
  if (anEntityWindow == NULL)
  {
    anEntityWindow = mTheme->load("ChildWindow");
    anEntityWindow->setPosition(10, 10);
    anEntityWindow->setSize(200, 100);

    tgui::Label::Ptr anNameLabel = mTheme->load("Label");
    anNameLabel->setTextSize(26);
    anNameLabel->setText("Name");
    anNameLabel->setPosition(0, 0);

    tgui::HorizontalLayout::Ptr anVitalLayout = std::make_shared<tgui::HorizontalLayout>();
    anVitalLayout->setPosition(8, 26);
    anVitalLayout->setSize(94, 32);

    tgui::Label::Ptr anConLabel = mTheme->load("Label");
    anConLabel->setTextSize(24);
    anConLabel->setText("HP: 000");
    anConLabel->setPosition(0, 0);
    anVitalLayout->add(anConLabel, "ConLabel");

    tgui::Label::Ptr anToughnessLabel = mTheme->load("Label");
    anToughnessLabel->setTextSize(24);
    anToughnessLabel->setText("Def: 00");
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
    anEntityWindow->add(anNameLabel, "NameLabel");
    anEntityWindow->add(anVitalLayout, "VitalLayout");
    anEntityWindow->add(anStatsLayout, "StatsLayout");

    mGUI.add(anEntityWindow, "EntityWindow");

    mActionMenu->hide();
  }
}
void MenuManager::CreateActionMenu()
{
  if (mActionMenu == NULL)
  {
    mActionMenu = mTheme->load("Panel");
    mActionMenu->setPosition(0, 460);
    mActionMenu->setSize(600,40);

    tgui::Button::Ptr anLookButton = mTheme->load("Button");
    mActionMenu->add(anLookButton, "LookButton");
    anLookButton->setPosition(0, 0);
    anLookButton->setSize(60, 40);
    anLookButton->setText("Look");
    anLookButton->connect("pressed", &MenuManager::CreateEntityMenu,this);
    tgui::Button::Ptr anTalkButton = mTheme->load("Button");
    mActionMenu->add(anTalkButton, "TalkButton");
    anTalkButton->setPosition(60, 0);
    anTalkButton->setSize(60, 40);
    anTalkButton->setText("Talk");
    tgui::Button::Ptr anAttackButton = mTheme->load("Button");
    mActionMenu->add(anAttackButton, "AttackButton");
    anAttackButton->setPosition(120, 0);
    anAttackButton->setSize(60, 40);
    anAttackButton->setText("Attack");
    anAttackButton->connect("pressed", &MenuManager::Attack, this);
    mGUI.add(mActionMenu, "ActionMenu");

  }
}
void MenuManager::CreateHUD()
{
  tgui::ListBox::Ptr anCombatLogList = mTheme->load("ListBox");
  anCombatLogList->setPosition(0, 500);
  anCombatLogList->setSize(600, 100);
  mGUI.add(anCombatLogList, "CombatLog");

  tgui::Panel::Ptr anCharacterScreen=mTheme->load("Panel");
  anCharacterScreen->setPosition(600, 0);
  anCharacterScreen->setSize(200, 600);
  mGUI.add(anCharacterScreen, "CharacterScreen");
}
void MenuManager::ShowActionMenu()
{
  mActionMenu->show();
}
void MenuManager::HideActionMenu()
{
  mActionMenu->hide();
}
void MenuManager::Attack()
{
  if(mTargetEntity!=NULL)
  {
    mApp.mWorld.events.emit<AttackEvent>(AttackEvent(mPlayerEntity, mTargetEntity, DAMAGE_MELEE, 10));
  }
  
}
void MenuManager::Log(std::string theMessage)
{
  tgui::ListBox::Ptr anCombatLogList = mGUI.get<tgui::ListBox>("CombatLog");
  anCombatLogList->addItem(theMessage);
}