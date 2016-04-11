#include "Box2dUtil.hpp"
#include <GExL/container/TArray.hpp>
namespace Box2d
{
  Box2d::BodyDef GenerateBodyDef(Box2d::BodyType theType, Box2d::Vector2f thePosition)
  {
    Box2d::BodyDef anBodyDef;
    anBodyDef.type = theType;
    Box2d::Vector2f anFinalPosition(thePosition.x / Box2d::UNIT_SCALE, thePosition.y / Box2d::UNIT_SCALE);
    anBodyDef.position = anFinalPosition;
    return anBodyDef;
  }
  Box2d::FixtureDef GenerateFixtureDef(b2Shape* theShape, float theDensity, float theFriction)
  {
    Box2d::FixtureDef anFixtureDef;
    anFixtureDef.shape = theShape;
    anFixtureDef.density = theDensity;
    anFixtureDef.friction = theFriction;
    return anFixtureDef;
  }

  Box2d::PolyShape GenerateBoxShape(float theWidth, float theHeight)
  {
    Box2d::PolyShape anShape;
    anShape.SetAsBox(theWidth / 2 / Box2d::UNIT_SCALE, theHeight / 2 / Box2d::UNIT_SCALE);
    return anShape;
  }
  Box2d::PolyShape GeneratePolyShape(tmxparser::TmxShapePointCollection_t thePoints)
  {
    Box2d::PolyShape anShape;

    return anShape;
  }
  Box2d::ChainShape GenerateChainShape(tmxparser::TmxShapePointCollection_t thePoints)
  {
    Box2d::ChainShape anShape;

   // anShape.SetPrevVertex(Vector2f(anVectorArray[0].x-1.0f, anVectorArray[0].y-1.0f));
   // anShape.SetNextVertex(Vector2f(anVectorArray[anVectorArray.size()-1].x + 1.0f, anVectorArray[anVectorArray.size() - 1].y - 1.0f));
    return anShape;
  }
  GExL::TArray<Box2d::Vector2f> GeneratePoints(tmxparser::TmxShapePointCollection_t thePoints)
  {
    const int anVectorCount = thePoints.size();
    GExL::TArray<Box2d::Vector2f> anVectorArray(anVectorCount);

    for (int v = 0; v < anVectorCount; v++)
    {
      anVectorArray[v].Set(thePoints[v].first / Box2d::UNIT_SCALE, thePoints[v].second / Box2d::UNIT_SCALE);
    }
    return anVectorArray;
  }
}