#ifndef COMPONENTS_HPP_INCLUDED
#define COMPONENTS_HPP_INCLUDED
#include "RPG_types.hpp"
#include <SFML/Graphics.hpp>
#include <GExL/container/TArray2D.hpp>
class EntityRender
{
public:
  sf::Texture mTexture;
  sf::VertexArray mVertices;
  sf::VertexArray mDebugVertices;

  EntityRender(sf::Texture& theTexture) :
    mTexture(theTexture),
    mVertices(sf::TrianglesStrip)
  {
    mVertices.append(sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
    mVertices.append(sf::Vertex(sf::Vector2f(0, static_cast<float>(theTexture.getSize().y)), sf::Vector2f(0, static_cast<float>(theTexture.getSize().y))));
    mVertices.append(sf::Vertex(sf::Vector2f(static_cast<float>(theTexture.getSize().x), 0), sf::Vector2f(static_cast<float>(theTexture.getSize().x), 0)));
    mVertices.append(sf::Vertex(sf::Vector2f(static_cast<float>(theTexture.getSize().x), static_cast<float>(theTexture.getSize().y)), sf::Vector2f(static_cast<float>(theTexture.getSize().x), static_cast<float>(theTexture.getSize().y))));
  }
  void SetClipRect(GExL::Int32 theX, GExL::Int32 theY, GExL::Int32 theW, GExL::Int32 theH)
  {
    mVertices.clear();
    mVertices.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY))));
    mVertices.append(sf::Vertex(sf::Vector2f(0.0f, static_cast<float>(theH)), sf::Vector2f(static_cast<float>(theX), static_cast<float>(theY + theH))));
    mVertices.append(sf::Vertex(sf::Vector2f(static_cast<float>(theW), 0.0f), sf::Vector2f(static_cast<float>(theX + theW), static_cast<float>(theY))));
    mVertices.append(sf::Vertex(sf::Vector2f(static_cast<float>(theW), static_cast<float>(theH)), sf::Vector2f(static_cast<float>(theX + theW), static_cast<float>(theY + theH))));
  }
};
class EntityDebugRender
{
public:
  sf::VertexArray mVertices;

  EntityDebugRender() :
    mVertices(sf::Quads)
  {
    
  }
};

typedef sf::Transformable EntityTransformable;


struct EntityPhysical
{
  EntityPhysical(float theCondition = 100.0f, float theToughness = 0.0f, bool theBlocking = false, float theWeight = 0.0f, GExL::Int32 theSize = 1, std::string theName = "") :
    condition(theCondition),
    toughness(theToughness),
    blocking(theBlocking),
    weight(theWeight),
    size(theSize),
    destroyed(false),
    name(theName)
  {

  }
  float condition;
  float toughness;
  bool blocking;
  float weight;
  GExL::Int32 size;
  bool destroyed;

  std::string name;
};
struct EntityAlive
{
  EntityAlive(CharacterStats theStats = CharacterStats(),CharacterSkills theSkills=CharacterSkills(), float theHealth = 100.0f, float theEnergy = 100.0f, GExL::Uint32 theBehaviorFlags = BEHAVIOR_NONE) :
    health(theHealth),
    energy(theEnergy),
    behaviorFlags(theBehaviorFlags),
    stats(theStats),
    skills(theSkills)
  {

  }
  float health;
  float energy;
  CharacterStats stats;
  CharacterSkills skills;
  GExL::Uint32 behaviorFlags;
};
struct EntityMobile
{

  EntityMobile(GExL::Uint32 theType=MOVEMENT_WALK_BI, float theSpeed = 1.0f) :
    type(theType),
    speed(theSpeed)
  {

  }
  GExL::Uint32 type;
  float speed;
};



#endif