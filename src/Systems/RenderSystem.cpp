#include "RenderSystem.hpp"
#include "..\Components.hpp"
namespace Systems
{
  RenderSystem::RenderSystem(sf::RenderWindow& theWindow) :
    mWindow(theWindow)
  {

  }
  void RenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) {
    //Render Each entity
    entityx::ComponentHandle<c::Transformable> anTransformable;
    entityx::ComponentHandle<c::Drawable> anRender;
    for (entityx::Entity entity : es.entities_with_components(anTransformable, anRender)) {
      sf::RenderStates anRenderState(&anRender->mTexture);
      sf::Transform anTransform = anTransformable->getTransform();
      anRenderState.transform *= anTransform;
      mWindow.draw(anRender->mVertices, anRenderState);
    }

  };
}