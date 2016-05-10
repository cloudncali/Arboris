#include "CombatSystem.hpp"
#include "../Components.hpp"
#include "../Tilemap.hpp"
#include "../Application.hpp"

#include <GExL/utils/MathUtil.hpp>
namespace Systems
{
  CombatSystem::CombatSystem(Application& theApp) :
    mApp(theApp)
  {

  }

  void CombatSystem::configure(entityx::EventManager &event_manager) {
    event_manager.subscribe<DamageEvent>(*this);
    event_manager.subscribe<AttackEvent>(*this);
  }
  void CombatSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
  {
    entityx::ComponentHandle<c::MapObject> anMapObject;
    entityx::ComponentHandle<c::Transformable> anTransform;
    while (!mDamageQueue.empty())
    {
      DamageEvent damage = mDamageQueue.front();
      for (entityx::Entity entity : es.entities_with_components(anTransform, anMapObject)) {
        if (damage.target.x == static_cast<GExL::Int32>(anTransform->getPosition().x / Tilemap::TileSize)
          && damage.target.y == static_cast<GExL::Int32>(anTransform->getPosition().y / Tilemap::TileSize))
        {
          if (entity.has_component<c::Character>())
          {
            entityx::ComponentHandle<c::Character> anAlive = entity.component<c::Character>();
            if (damage.type |= DAMAGE_MELEE)
            {
              CharacterSkills &anSkillsA = damage.source.component<c::Character>()->skills;
              CharacterSkills &anSkillsB = entity.component<c::Character>()->skills;
              CharacterStats &anStatsA = damage.source.component<c::Character>()->stats;
              CharacterStats &anStatsB = entity.component<c::Character>()->stats;

              GExL::Uint32 anLuckRollA = GExL::random(1, static_cast<GExL::Uint32>(anStatsA.luck));
              GExL::Uint32 anLuckRollB = GExL::random(1, static_cast<GExL::Uint32>(anStatsB.luck));

              GExL::Uint32 anTotalA = static_cast<GExL::Uint32>(anSkillsA.combat + anStatsA.phys + anLuckRollA);
              GExL::Uint32 anTotalB = static_cast<GExL::Uint32>(anSkillsB.combat + anStatsB.phys + anLuckRollB);
              if (anTotalA >= anTotalB)
              {
                GExL::Uint32 anDamageLuckRoll = GExL::random(1, static_cast<GExL::Uint32>(anStatsA.luck));
                Damage(entity, damage.power + anStatsA.phys + anDamageLuckRoll, damage.type);
              }
            }
          }
          else
          {
            Damage(entity, damage.power, damage.type);
          }
        }
        if (anMapObject->health <= 0.0f)
        {
          anMapObject->destroyed = true;
          entity.destroy();
        }
      }
      mDamageQueue.pop();
    }
    while (!mAttackQueue.empty())
    {
      Attack(mAttackQueue.front());
      mAttackQueue.pop();
    }
  }
  void CombatSystem::receive(const DamageEvent &damage) {
    mDamageQueue.push(damage);
  }
  void CombatSystem::receive(const AttackEvent &attack) {
    mAttackQueue.push(attack);
  }
  void CombatSystem::Damage(entityx::Entity theEntity, float thePower, GExL::Uint32 theType)
  {
    entityx::ComponentHandle<c::MapObject> anMapObject;
    anMapObject = theEntity.component<c::MapObject>();
    GExL::Int32 anFinalDamage = thePower - anMapObject->defense;
    if (anFinalDamage > 0)
    {
      anMapObject->health -= anFinalDamage;
      std::stringstream anOutput("Combat: ");
      anOutput << anFinalDamage;
      anOutput << " damage delt to ";
      anOutput << anMapObject->name;
      anOutput << ".";
      mApp.mMenuManager.Log(anOutput.str());
      if (anMapObject->health < 0)
      {
        anMapObject->health = 0;
      }
    }
    else
    {
      std::stringstream anOutput("Combat: ");
      anOutput << anMapObject->name;
      anOutput << " resisted all damage.";
      mApp.mMenuManager.Log(anOutput.str());
    }
  }
  void CombatSystem::Attack(AttackEvent& theAttack)
  {
    if (theAttack.type |= DAMAGE_MELEE)
    {
      //check distence
      entityx::ComponentHandle<c::Transformable> anTransformA, anTransformB;
      anTransformA = theAttack.source.component<c::Transformable>();
      anTransformB = theAttack.target.component<c::Transformable>();

      sf::Vector2i anDistance = static_cast<sf::Vector2i>(anTransformA->getPosition() - anTransformB->getPosition());
      sf::Vector2i anAbsDistance(abs(anDistance.x), abs(anDistance.y));
      if (anAbsDistance.x > 33 || anAbsDistance.y > 33)
      {
        std::stringstream anOutput("Combat: ");
        anOutput << theAttack.target.component<c::MapObject>()->name;
        anOutput << " is out of range.";
        mApp.mMenuManager.Log(anOutput.str());
      }
      else
      {
        entityx::ComponentHandle<c::Character> anCharacterSource, anCharacterTarget;
        entityx::ComponentHandle<c::MapObject> anMapObjectSource, anMapObjectTarget;
        anCharacterSource = theAttack.source.component<c::Character>();
        anCharacterTarget = theAttack.target.component<c::Character>();
        //check for hit.
        //TODO Add LuckRoll;
        GExL::Int32 anHitTarget = anCharacterTarget->skills.combat + anCharacterTarget->skills.reflex + anCharacterTarget->stats.phys + anCharacterTarget->stats.luck;
        GExL::Int32 anHitCheck = anCharacterSource->skills.combat + anCharacterSource->skills.strength + anCharacterSource->stats.phys + anCharacterSource->stats.luck;
        if (anHitCheck >= anHitTarget)
        {
          //TODO: ARMOR CHECK

          //Deal Damage#
          Damage(theAttack.target, anCharacterSource->stats.phys, theAttack.type);
        }
        else
        {
          std::stringstream anOutput("Combat: ");
          anOutput << "Missed ";
          anOutput << theAttack.target.component<c::MapObject>()->name;
          anOutput << ".";
          mApp.mMenuManager.Log(anOutput.str());
        }
      }
    }
    else if (theAttack.type |= DAMAGE_MISSLE)
    {

    }
    else if (theAttack.type |= DAMAGE_MAGIC)
    {

    }
  }
}