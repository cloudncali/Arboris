#include "Systems.hpp"
#include "Components.hpp"
#include <GExL/utils/MathUtil.hpp>
#include "Events.hpp"
#include "Tilemap.hpp"
#include "Application.hpp"
RenderSystem::RenderSystem(sf::RenderWindow& theWindow) :
  mWindow(theWindow)
{

}
void RenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
  //Render Each entity
  entityx::ComponentHandle<EntityTransformable> anTransformable;
  entityx::ComponentHandle<EntityRender> anRender;
  for (entityx::Entity entity : es.entities_with_components(anTransformable, anRender)) {
    sf::RenderStates anRenderState(&anRender->mTexture);
    sf::Transform anTransform = anTransformable->getTransform();
    anRenderState.transform *= anTransform;
    mWindow.draw(anRender->mVertices, anRenderState);
  }
};
DebugRenderSystem::DebugRenderSystem(sf::RenderWindow& theWindow) :
  mWindow(theWindow)
{

}
void DebugRenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
  //Render Each entity
  entityx::ComponentHandle<EntityTransformable> anTransformable;
  entityx::ComponentHandle<EntityDebugRender> anRender;

  for (entityx::Entity entity : es.entities_with_components(anTransformable, anRender)) {
    sf::RenderStates anRenderState;
    sf::Transform anTransform = anTransformable->getTransform();
    anRenderState.transform *= anTransform;
    mWindow.draw(anRender->mVertices, anRenderState);
  }
};
CombatSystem::CombatSystem(Console& theConsole):
  mConsole(theConsole)
{

}

void CombatSystem::configure(entityx::EventManager &event_manager) {
  event_manager.subscribe<DamageEvent>(*this);
}
void CombatSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  entityx::ComponentHandle<EntityPhysical> anPhysical;
  entityx::ComponentHandle<EntityTransformable> anTransform;
  while (!mDamageQueue.empty())
  {
    DamageEvent damage = mDamageQueue.front();
    for (entityx::Entity entity : es.entities_with_components(anTransform, anPhysical)) {
      if (damage.target.x == static_cast<GExL::Int32>(anTransform->getPosition().x / Tilemap::TileSize)
        && damage.target.y == static_cast<GExL::Int32>(anTransform->getPosition().y / Tilemap::TileSize))
      {
        if (entity.has_component<EntityAlive>())
        {
          entityx::ComponentHandle<EntityAlive> anAlive = entity.component<EntityAlive>();
          if (damage.type|= DAMAGE_MELEE)
          {
            CharacterSkills &anSkillsA = damage.source.component<EntityAlive>()->skills;
            CharacterSkills &anSkillsB = entity.component<EntityAlive>()->skills;
            CharacterStats &anStatsA=damage.source.component<EntityAlive>()->stats;
            CharacterStats &anStatsB= entity.component<EntityAlive>()->stats;

            GExL::Uint32 anLuckRollA = GExL::random(1, static_cast<GExL::Uint32>(anStatsA.luck));
            GExL::Uint32 anLuckRollB = GExL::random(1, static_cast<GExL::Uint32>(anStatsB.luck));

            GExL::Uint32 anTotalA = static_cast<GExL::Uint32>(anSkillsA.combat + anStatsA.phys + anLuckRollA);
            GExL::Uint32 anTotalB = static_cast<GExL::Uint32>(anSkillsB.combat + anStatsB.phys + anLuckRollB);
            if (anTotalA >= anTotalB)
            {
              GExL::Uint32 anDamageLuckRoll = GExL::random(1, static_cast<GExL::Uint32>(anStatsA.luck));
              Damage(entity, damage.power+anStatsA.phys+ anDamageLuckRoll, damage.type);
            }
          }
        }
        else
        {
          Damage(entity, damage.power, damage.type);
        }
      }
      if (anPhysical->condition <= 0.0f)
      {
        anPhysical->destroyed = true;
        entity.destroy();
      }
    }
    mDamageQueue.pop();
  }
}
void CombatSystem::receive(const DamageEvent &damage) {
  mDamageQueue.push(damage);
}
void CombatSystem::Damage(entityx::Entity theEntity, float thePower, GExL::Uint32 theType)
{
  entityx::ComponentHandle<EntityPhysical> anPhysical;
  anPhysical = theEntity.component<EntityPhysical>();
  GExL::Uint32 anFinalDamage = std::ceil(thePower / anPhysical->toughness);
  anPhysical->condition -= anFinalDamage;
  std::stringstream anOutput("Combat: ");
  anOutput << anFinalDamage;
  anOutput << " delt to";
  anOutput << anPhysical->name;
  anOutput << ".";
  mConsole.print(anOutput.str());
}
MovementSystem::MovementSystem(Tilemap& theMap) :
  mTilemap(theMap)
{

}
void MovementSystem::configure(entityx::EventManager &event_manager)
{
  event_manager.subscribe<MovementEvent>(*this);
}
void MovementSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  entityx::ComponentHandle<EntityPhysical> anPhysical;
  entityx::ComponentHandle<EntityTransformable> anTransform;
  while (!mMovementQueue.empty())
  {
    MovementEvent movement = mMovementQueue.front();
    anPhysical = movement.entity.component<EntityPhysical>();
    anTransform = movement.entity.component<EntityTransformable>();
    GExL::Int32 anTileX = movement.target.x;
    GExL::Int32 anTileY = movement.target.y;
    if (!(mTilemap.TestTileFlag(sf::Vector3f(static_cast<float>(anTileX), static_cast<float>(anTileY), 0), Tilemap::TILE_BLOCKED) ||
      mTilemap.TestTileFlag(sf::Vector3f(static_cast<float>(anTileX), static_cast<float>(anTileY), 1), Tilemap::TILE_BLOCKED)))
    {
      anTransform->setPosition(movement.target.x*Tilemap::TileSize, movement.target.y*Tilemap::TileSize);
    }
    else
    {

    }

    mMovementQueue.pop();
  }
}
void MovementSystem::receive(const MovementEvent &movement) {
  mMovementQueue.push(movement);
}

CollisionSystem::CollisionSystem(Tilemap& theMap) :
  mTilemap(theMap)
{

}
void CollisionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
  //Render Each entity
  entityx::ComponentHandle<EntityPhysical> anPhyiscal;
  entityx::ComponentHandle<EntityTransformable> anTransform;
  mTilemap.SetTileLayerFlag(1, Tilemap::TILE_NONE);
  for (entityx::Entity entity : es.entities_with_components(anPhyiscal, anTransform)) {
    mTilemap.SetTileFlag(sf::Vector3i(static_cast<GExL::Int32>(anTransform->getPosition().x / Tilemap::TileSize), 
      static_cast<GExL::Int32>(anTransform->getPosition().y / Tilemap::TileSize), 1), Tilemap::TILE_BLOCKED);
  }
}
void CollisionSystem::receive(const CollisionEvent &collision) {

}

BehaviorSystem::BehaviorSystem(Application& theApp) :
  mApp(theApp)
{

}
void BehaviorSystem::configure(entityx::EventManager &event_manager)
{
  event_manager.subscribe<KeyboardEvent>(*this);
}
void BehaviorSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{

  entityx::ComponentHandle<EntityAlive> anAlive;
  entityx::ComponentHandle<EntityTransformable> anTransform;

  if (mTurnOrder.empty())
  {
    for (entityx::Entity anEntity : es.entities_with_components(anAlive, anTransform)) {
      mTurnOrder.push(anEntity);
    }

  }
  else
  {
    bool anAction = false;
    entityx::Entity anEntity = mTurnOrder.front();
    anAlive = anEntity.component<EntityAlive>();
    anTransform = anEntity.component<EntityTransformable>();
    std::string anEntityName = anEntity.component<EntityPhysical>()->name;
    if (anAlive->behaviorFlags & BEHAVIOR_CONTROLLED)
    {
      while (!mKeyboardEventQueue.empty() && !mTurnOrder.empty())
      {
        sf::Vector2f anTargetPos;
        if (mKeyboardEventQueue.front().theKeyCode == sf::Keyboard::Left)
        {
          anTargetPos.x = 1.0f;
          anTargetPos.y = 0.0f;
          anAction = true;
        }
        else if (mKeyboardEventQueue.front().theKeyCode == sf::Keyboard::Right)
        {
          anTargetPos.x = -1.0f;
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
        if (anAction)
        {
          anTargetPos.x += anTransform->getPosition().x / Tilemap::TileSize;
          anTargetPos.y += anTransform->getPosition().y / Tilemap::TileSize;
          if (anAlive->behaviorFlags & BEHAVIOR_AGRESSIVE)
          {
            mApp.mWorld.events.emit<DamageEvent>(anEntity, anTargetPos, static_cast<GExL::Uint32>(DAMAGE_MELEE), 0.0f);
          }
          mApp.mWorld.events.emit<MovementEvent>(anEntity, anTargetPos, MOVEMENT_WALK_BI);
          mTurnOrder.pop();
          mKeyboardEventQueue.pop();
        }
      }
    }
    else if (anAlive->behaviorFlags & BEHAVIOR_WANDER)
    {
      GExL::Uint32 anDirection = GExL::random(0, 8);
      if (anDirection == 1)
      {
        mApp.mWorld.events.emit<MovementEvent>(anEntity, sf::Vector2f(0.0f, -1.0f), MOVEMENT_WALK_BI);
      }
      if (anDirection == 2)
      {
        mApp.mWorld.events.emit<MovementEvent>(anEntity, sf::Vector2f(1.0f, 0.0f), MOVEMENT_WALK_BI);
      }
      if (anDirection == 3)
      {
        mApp.mWorld.events.emit<MovementEvent>(anEntity, sf::Vector2f(0.0f, 1.0f), MOVEMENT_WALK_BI);
      }
      if (anDirection == 4)
      {
        mApp.mWorld.events.emit<MovementEvent>(anEntity, sf::Vector2f(-1.0f, 0.0f), MOVEMENT_WALK_BI);
      }
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