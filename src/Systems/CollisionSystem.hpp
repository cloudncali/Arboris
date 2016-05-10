#ifndef COLLISIONSYSTEM_HPP_INCLUDED
#define COLLISIONSYSTEM_HPP_INCLUDED
#include "../RPG_types.hpp"
#include "../Events.hpp"
namespace Systems
{
  class CollisionSystem : public entityx::System <CollisionSystem>, public entityx::Receiver <CollisionSystem>
  {
  public:
    CollisionSystem(Application& theApp);
    void configure(entityx::EventManager &event_manager);
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    void receive(const CollisionEvent &collision);
    void receive(const MouseClickEvent &mouseclick);
  private:
    Application& mApp;
    Tilemap& mTilemap;
    std::queue<MouseClickEvent> mMouseClickEvents;
  };
}
#endif