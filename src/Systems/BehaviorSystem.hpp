#ifndef BEHAVIORSYSTEM_HPP_INCLUDED
#define BEHAVIORSYSTEM_HPP_INCLUDED
#include "../RPG_types.hpp"
#include "../Events.hpp"

namespace Systems
{
  class BehaviorSystem : public entityx::System <BehaviorSystem>, public entityx::Receiver<BehaviorSystem>
  {
  public:
    BehaviorSystem(Application& theApp);
    void configure(entityx::EventManager &event_manager);
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    void receive(const KeyboardEvent &keyboardevent);
    void receive(const AttackEvent &attackevent);
  private:
    std::queue<KeyboardEvent> mKeyboardEventQueue;
    std::queue<entityx::Entity> mTurnOrder;
    bool mPlayerAction;
    Application& mApp;
  };
}
#endif