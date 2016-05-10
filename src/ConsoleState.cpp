#include "ConsoleState.hpp"
#include "Application.hpp"
#include <GExL/utils/String_types.hpp>
#include <GExL/utils/MathUtil.hpp>
#include <time.h>
#include "Tilemap.hpp"
ConsoleState::ConsoleState(Application& theApp) :
  IState(theApp),
  mBackgroundImage(theApp.mAssetManager, "resources/images/bg.png", GExL::AssetLoadNow)
{
  RegisterConsoleCommands();
}
ConsoleState::~ConsoleState()
{

}
void ConsoleState::init()
{
  srand(GExL::Uint32(time(NULL)));
  mBackgroundImage.GetAsset().setRepeated(true);
  mApp.mConsole.setBackgroundColor(sf::Color(0u, 0u, 0u, 100u));
  mApp.mConsole.showCommandBuffer(true);
}
void ConsoleState::reinit()
{
}
void ConsoleState::handleEvent(sf::Event theEvent)
{
  if (theEvent.key.code == sf::Keyboard::Tilde && theEvent.type == sf::Event::KeyReleased)
  {
    if (mApp.mStateManager.GetCurrentSubState() == STATE_CONSOLE)
    {
      mApp.mStateManager.SetNextSubState(STATE_NONE);
    }
  }  
  else
  {
    mApp.mConsole.handleEvent(theEvent);
    mApp.mConsole.handleUIEvent(theEvent);
  }
}
void ConsoleState::update(float theDeltaTime)
{
  //mConsole.
}
void ConsoleState::render()
{
  mApp.mWindow.draw(mApp.mConsole);

}
void ConsoleState::start()
{
  mApp.mConsole.setBackgroundColor(sf::Color(0u, 0u, 0u, 100u));
  mApp.mConsole.showCommandBuffer(true);
}
void ConsoleState::stop()
{
  mApp.mConsole.setBackgroundColor(sf::Color(0u, 0u, 0u, 10u));
  mApp.mConsole.showCommandBuffer(false);
}
void ConsoleState::RegisterConsoleCommands()
{
  ///Basic spawn command;
  Console::CommandData cd;

  cd.action = [this](std::vector<std::string> l, sf::Uint32& flags) -> std::string
  {
    std::stringstream anOutput;
    bool anError = false;
    if (l.size() >= 4)
    {
      
      entityx::Entity anEntity;
      GExL::Int32 anX, anY;
      std::string anEntityType, anEntityLabel, anTexutreID;
      anEntityType = l[0];
      anEntityLabel = l[1];
      anX = GExL::Int32Parser::ToValue(l[2], 0);
      anY = GExL::Int32Parser::ToValue(l[3], 0);
      if (GExL::StringToLowercase(anEntityType) == "pc")
      {
        if (mApp.mData.ParseCharacter(anEntityLabel, anEntity))
        {
          anEntity.component<c::Transformable>()->setPosition(static_cast<float>(anX*Tilemap::TileSize), static_cast<float>(anY*Tilemap::TileSize));
          anEntity.component<c::Character>()->behaviorFlags |= BEHAVIOR_CONTROLLED;
        }
        else
        {
          anOutput << "Could not find data for " << anEntityLabel;
          anError = true;
        }
      }
      else if (GExL::StringToLowercase(anEntityType) == "npc")
      {
        if (mApp.mData.ParseCharacter(anEntityLabel, anEntity))
        {
          anEntity.component<c::Transformable>()->setPosition(static_cast<float>(anX*Tilemap::TileSize), static_cast<float>(anY*Tilemap::TileSize));
        }
        else
        {
          anOutput << "Could not find data for: " << anEntityLabel;

          anError = true;
        }
      }
      else
      {
        anOutput << "Unknow chracter type, " << anEntityType <<" for: " << anEntityLabel;
        anError = true;
      }
  
      if (!anError)
      {
        anOutput << anEntityLabel << " Entity" << " created as a " << anEntityType <<  
          " at X: " << GExL::Uint32Parser::ToString(anX) << ", Y: " <<
          GExL::Uint32Parser::ToString(anY);
      }
      //anReturn = anEntity.id;
    }
    else
    {
      anOutput << "Not enough arguemnts for command: 'spawn'";
    }
    mApp.mConsole.print(anOutput.str());
    return "";

  };
  cd.help = "Basic Spawn Command.";

  mApp.mConsole.addItem("spawn", cd);

  cd.action = [this](std::vector<std::string> l, sf::Uint32& flags) -> std::string
  {
    std::string anOutput;
    if (l.size() >= 4)
    {
      std::string anDamageType;
      GExL::Int32 anX, anY;
      float anPower;
      anDamageType = l[0];
      anX = GExL::Int32Parser::ToValue(l[1], 0);
      anY = GExL::Int32Parser::ToValue(l[2], 0);
      anPower = GExL::FloatParser::ToValue(l[3], 0.0f);
      if (GExL::StringToLowercase(anDamageType) == "spot")
      {
        //mApp.mWorld.events.emit<DamageEvent>(sf::Vector2f(static_cast<float>(anX), static_cast<float>(anY)), 0, anPower);
      }


      anOutput = l[3];
      anOutput += " damage done at: ";
      anOutput += l[1];
      anOutput += " ,";
      anOutput += l[2];
      anOutput += ".";
      //anReturn = anEntity.id;
    }
    else
    {
      anOutput = "Not enough arguemnts for command: 'spawn'";
    }
    mApp.mConsole.print(anOutput);
    return "";

  };
  cd.help = "cause damage.";

  mApp.mConsole.addItem("damage", cd);
}