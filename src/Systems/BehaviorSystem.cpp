#include "BehaviorSystem.hpp"
#include "../Components.hpp"
#include "../Application.hpp"
#include <GExL/utils/MathUtil.hpp>
namespace Systems
{
  BehaviorSystem::BehaviorSystem(Application& theApp) :
    mApp(theApp),
    mPlayerAction(false)
  {

  }
  void BehaviorSystem::configure(entityx::EventManager &event_manager)
  {
    event_manager.subscribe<KeyboardEvent>(*this);
    event_manager.subscribe<AttackEvent>(*this);
  }
  void BehaviorSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
  {

    entityx::ComponentHandle<c::Character> anAlive;
    entityx::ComponentHandle<c::MapObject> anMapObject;
    entityx::ComponentHandle<c::Transformable> anTransform;

    if (mTurnOrder.empty())
    {
      for (entityx::Entity anEntity : es.entities_with_components(anAlive, anMapObject, anTransform)) {
        if (!anMapObject->destroyed)
          mTurnOrder.push(anEntity);
      }

    }
    else
    {
      bool anAction = false;
      entityx::Entity anEntity = mTurnOrder.front();
      anAlive = anEntity.component<c::Character>();
      anMapObject = anEntity.component<c::MapObject>();

      anTransform = anEntity.component<c::Transformable>();
      if (!anMapObject->destroyed)
      {
        if (anMapObject->health <= 0)
        {
          anMapObject->destroyed = true;

          anTransform->setRotation(90);

        }
        else
        {
          std::string anEntityName = anEntity.component<c::MapObject>()->name;
          sf::Vector2f anTargetPos;
          if (anAlive->behaviorFlags & BEHAVIOR_CONTROLLED)
          {
            anAction = mPlayerAction;
            if (!anAction)
            {
              while (!mKeyboardEventQueue.empty() && !mTurnOrder.empty())
              {

                if (mKeyboardEventQueue.front().theKeyCode == sf::Keyboard::Left)
                {
                  anTargetPos.x = -1.0f;
                  anTargetPos.y = 0.0f;
                  anAction = true;
                }
                else if (mKeyboardEventQueue.front().theKeyCode == sf::Keyboard::Right)
                {
                  anTargetPos.x = 1.0f;
                  anTargetPos.y = 0.0f;
                  anAction = true;
                }
                else if (mKeyboardEventQueue.front().theKeyCode == sf::Keyboard::Up)
                {
                  anTargetPos.x = 0.0f;
                  anTargetPos.y = -1.0f;
                  anAction = true;
                }
                else if (mKeyboardEventQueue.front().theKeyCode == sf::Keyboard::Down)
                {
                  anTargetPos.x = 0.0f;
                  anTargetPos.y = 1.0f;
                  anAction = true;
                }
                else if (mKeyboardEventQueue.front().theKeyCode == sf::Keyboard::A)
                {
                  if (anAlive->behaviorFlags & BEHAVIOR_AGRESSIVE)
                  {
                    mApp.mConsole.print(anEntityName + "is lowering it's gaurd.");
                    anAlive->behaviorFlags &= ~BEHAVIOR_AGRESSIVE;
                  }
                  else
                  {
                    mApp.mConsole.print(anEntityName + "is acting aggressive.");
                    anAlive->behaviorFlags |= BEHAVIOR_AGRESSIVE;
                  }
                  anAction = true;
                }
                mKeyboardEventQueue.pop();
              }
            }
            else
            {
              mPlayerAction = false;
            }
          }
          else if (anAlive->behaviorFlags & BEHAVIOR_WANDER)
          {
            GExL::Uint32 anDirection = GExL::random(0, 8);
            if (anDirection == 1)
            {
              anTargetPos.x = 0.0f;
              anTargetPos.y = -1.0f;
              anAction = true;
            }
            if (anDirection == 2)
            {
              anTargetPos.x = 1.0f;
              anTargetPos.y = 0.0f;
              anAction = true;
            }
            if (anDirection == 3)
            {
              anTargetPos.x = 0.0f;
              anTargetPos.y = 1.0f;
              anAction = true;
            }
            if (anDirection == 4)
            {
              anTargetPos.x = -1.0f;
              anTargetPos.y = 0.0f;
              anAction = true;
            }
          }
          if (anAction)
          {
            anTargetPos.x += anTransform->getPosition().x / Tilemap::TileSize;
            anTargetPos.y += anTransform->getPosition().y / Tilemap::TileSize;
            if (anAlive->behaviorFlags & BEHAVIOR_AGRESSIVE)
            {
              //mApp.mWorld.events.emit<DamageEvent>(anEntity, anTargetPos, static_cast<GExL::Uint32>(DAMAGE_MELEE), 0.0f);
            }
            mApp.mWorld.events.emit<MovementEvent>(anEntity, anTargetPos, MOVEMENT_WALK_BI);
            mTurnOrder.pop();

          }
        }
      }
      else
      {
        mTurnOrder.pop();
      }
    }
  }

  void BehaviorSystem::receive(const KeyboardEvent &keyboardevent) {
    if (keyboardevent.theKeyCode == sf::Keyboard::Left ||
      keyboardevent.theKeyCode == sf::Keyboard::Right ||
      keyboardevent.theKeyCode == sf::Keyboard::Up ||
      keyboardevent.theKeyCode == sf::Keyboard::Down ||
      keyboardevent.theKeyCode == sf::Keyboard::A)
    {
      mKeyboardEventQueue.push(keyboardevent);
    }

  }
  void BehaviorSystem::receive(const AttackEvent &attackevent) {
    mPlayerAction = true;
  }
}