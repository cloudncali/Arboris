#include "FontHandler.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Application.hpp"
FontHandler::FontHandler(GExL::Uint32 theFontSize) :
GExL::TAssetHandler<sf::Font>(),
mFontSize(theFontSize)
{

}
FontHandler::~FontHandler()
{

}
bool FontHandler::LoadFromFile(const GExL::typeAssetID theAssetID, sf::Font& theAsset)
{
  bool anResult = false;
  std::string anFilname = GetFilename(theAssetID);
  if (anFilname.length() > 0)
  {
    if (theAsset.loadFromFile(anFilname))
    {
      anResult = true;
    }
  }
  else
  {
    ELOG() << "ImageHandler::LoadFromFile(" << theAssetID
      << ") No filename provided!" << std::endl;
  }
  return anResult;
}
bool FontHandler::LoadFromMemory(const GExL::typeAssetID theAssetID, sf::Font& theAsset)
{
  return false;
}

bool FontHandler::LoadFromNetwork(const GExL::typeAssetID theAssetID, sf::Font& theAsset)
{
  return false;
}