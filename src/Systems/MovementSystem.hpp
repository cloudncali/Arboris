#ifndef MOVEMENTSYSTEM_HPP_INCLUDED
#define MOVEMENTSYSTEM_HPP_INCLUDED
#include "../RPG_types.hpp"
#include "../Events.hpp"
namespace Systems
{
  class MovementSystem : public entityx::System <MovementSystem>, public entityx::Receiver<MovementSystem>
  {
  public:
    MovementSystem(Tilemap& theMap);
    void configure(entityx::EventManager &event_manager);
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    void receive(const MovementEvent &movement);
  private:
    std::queue<MovementEvent> mMovementQueue;
    Tilemap& mTilemap;
  };
}
#endif