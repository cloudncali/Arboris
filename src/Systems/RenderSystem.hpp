#ifndef RENDERSYSTEM_HPP_INCLUDED
#define RENDERSYSTEM_HPP_INCLUDED
#include "../RPG_types.hpp"
#include "../Events.hpp"
namespace Systems
{
class RenderSystem : public entityx::System < RenderSystem > {
public:
  RenderSystem(sf::RenderWindow& theWindow);
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
private:
  GExL::Int32 mCameraX;
  GExL::Int32 mCameraY;
  entityx::Entity mCameraFocus;
  sf::RenderWindow& mWindow;
};
}
#endif