#include "MusicHandler.hpp"
#include <iostream>
#include "Application.hpp"
MusicHandler::MusicHandler() :
GExL::TAssetHandler<sf::Music>()
{

}
MusicHandler::~MusicHandler()
{

}
bool MusicHandler::LoadFromFile(const GExL::typeAssetID theAssetID, sf::Music& theAsset)
{
  bool anResult = false;
  std::string anFilename = GetFilename(theAssetID);
  if (anFilename.length() > 0)
  {
    //Load music
    if (theAsset.openFromFile(anFilename))
    {
      ELOG() << "MusicHandler::LoadFromFile(" << theAssetID
        << ")" << std::endl;
    }
    else
      anResult = true;
  }
  else
  {
    ELOG() << "MusicHandler::LoadFromFile(" << theAssetID
      << ") No filename provided!" << std::endl;
  }
  return anResult;
}
bool MusicHandler::LoadFromMemory(const GExL::typeAssetID theAssetID, sf::Music& theAsset)
{
  return false;
}

bool MusicHandler::LoadFromNetwork(const GExL::typeAssetID theAssetID, sf::Music& theAsset)
{
  return false;
}