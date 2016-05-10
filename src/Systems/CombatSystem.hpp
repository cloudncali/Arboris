#ifndef COMBATSYSTEM_HPP_INCLUDED
#define COMBATSYSTEM_HPP_INCLUDED
#include "../RPG_types.hpp"
#include "../Events.hpp"
namespace Systems
{
  class CombatSystem : public entityx::System <CombatSystem>, public entityx::Receiver<CombatSystem>
  {
  public:
    CombatSystem(Application& theApp);
    void configure(entityx::EventManager &event_manager);
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    //Event Functions
    void receive(const DamageEvent &damage);
    void receive(const AttackEvent &attackevent);
    
    //Logic Funtions
    void Damage(entityx::Entity theEntity, float thePower, GExL::Uint32 theType);
    void Attack(AttackEvent& theAttack);
  private:
    std::queue<DamageEvent> mDamageQueue;
    std::queue<AttackEvent> mAttackQueue;

    Application& mApp;
  };
}
#endif