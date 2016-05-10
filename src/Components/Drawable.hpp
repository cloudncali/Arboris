#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED
#include "../RPG_types.hpp"
#include "SFML/Graphics.hpp"
namespace Components
{

  class Drawable
  {
  public:
    sf::Texture mTexture;
    sf::VertexArray mVertices;

    Drawable(sf::Texture& theTexture) :
      mTexture(theTexture),
      mVertices(sf::TrianglesStrip)
    {
      mVertices.append(sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
      mVertices.append(sf::Vertex(sf::Vector2f(0, static_cast<float>(theTexture.getSize().y)), sf::Vector2f(0, static_cast<float>(theTexture.getSize().y))));
      mVertices.append(sf::Vertex(sf::Vector2f(static_cast<float>(theTexture.getSize().x), 0), sf::Vector2f(static_cast<float>(theTexture.getSize().x), 0)));
      mVertices.append(sf::Vertex(sf::Vector2f(static_cast<float>(theTexture.getSize().x), static_cast<float>(theTexture.getSize().y)), sf::Vector2f(static_cast<float>(theTexture.getSize().x), static_cast<float>(theTexture.getSize().y))));
    }
    //This clears all vertex information on a drawable and resets it using a cliprect(for tilemaps, spritesheets, etc)
    void SetClipRect(sf::IntRect theClipRect)
    {
      mVertices.clear();
      mVertices.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(static_cast<float>(theClipRect.left), static_cast<float>(theClipRect.top))));
      mVertices.append(sf::Vertex(sf::Vector2f(0.0f, static_cast<float>(theClipRect.height)), sf::Vector2f(static_cast<float>(theClipRect.left), static_cast<float>(theClipRect.top + theClipRect.height))));
      mVertices.append(sf::Vertex(sf::Vector2f(static_cast<float>(theClipRect.width), 0.0f), sf::Vector2f(static_cast<float>(theClipRect.left + theClipRect.width), static_cast<float>(theClipRect.top))));
      mVertices.append(sf::Vertex(sf::Vector2f(static_cast<float>(theClipRect.width), static_cast<float>(theClipRect.height)), sf::Vector2f(static_cast<float>(theClipRect.left + theClipRect.width), static_cast<float>(theClipRect.top + theClipRect.height))));
    }

  };

  
}
#endif