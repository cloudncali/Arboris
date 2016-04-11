#ifndef MUSIC_HANDLER_HPP_INCLUDED
#define MUSIC_HANDLER_HPP_INCLUDED
#include <GExL/assets/TAssetHandler.hpp>
#include <SFML/Audio.hpp>
class MusicHandler : public GExL::TAssetHandler<sf::Music>
{
public:
  MusicHandler();
  /// Provides the ImageHandler class for managing sf::Image assets

  /**
  * ImageHandler deconstructor
  */
  virtual ~MusicHandler();

protected:
  /**
  * LoadFromFile is responsible for loading theAsset from a file and must
  * be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromFile(const GExL::typeAssetID theAssetID, sf::Music& theAsset);
  /**
  * LoadFromMemory is responsible for loading theAsset from memory and
  * must be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromMemory(const GExL::typeAssetID theAssetID, sf::Music& theAsset);
  /**
  * LoadFromNetwork is responsible for loading theAsset from network and
  * must be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromNetwork(const GExL::typeAssetID theAssetID, sf::Music& theAsset);
private:
}; // class TextureHandler

#endif