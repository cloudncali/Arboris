#include "TextureHandler.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Application.hpp"
TextureHandler::TextureHandler() :
GExL::TAssetHandler<sf::Texture>()
{

}
TextureHandler::~TextureHandler()
{

}
bool TextureHandler::LoadFromFile(const GExL::typeAssetID theAssetID, sf::Texture& theAsset)
{
  bool anResult = false;
  std::string anFilename = GetFilename(theAssetID);
  if (anFilename.length() > 0)
  {
    if (!theAsset.loadFromFile(anFilename))
    {
      ELOG() << "ImageHandler::LoadFromFile(" << theAssetID
        << ")" << std::endl;
    }
  }
  else
  {
    ELOG() << "TextureHandler::LoadFromFile(" << theAssetID
      << ") No filename provided!" << std::endl;
  }
  return anResult;
}
bool TextureHandler::LoadFromMemory(const GExL::typeAssetID theAssetID, sf::Texture& theAsset)
{
  return false;
}

bool TextureHandler::LoadFromNetwork(const GExL::typeAssetID theAssetID, sf::Texture& theAsset)
{
  return false;
}