#ifndef FONT_MANGER_HPP_INCLUDED
#define FONT_MANGER_HPP_INCLUDED
#include <GExL/assets/TAssetHandler.hpp>
#include <SFML/Graphics.hpp>
class FontHandler : public GExL::TAssetHandler<sf::Font>
{
public:
  FontHandler(GExL::Uint32 theFontSize);
  /// Provides the ImageHandler class for managing sf::Image assets

  /**
  * ImageHandler deconstructor
  */
  virtual ~FontHandler();

protected:
  /**
  * LoadFromFile is responsible for loading theAsset from a file and must
  * be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromFile(const GExL::typeAssetID theAssetID, sf::Font& theAsset);
  /**
  * LoadFromMemory is responsible for loading theAsset from memory and
  * must be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromMemory(const GExL::typeAssetID theAssetID, sf::Font& theAsset);
  /**
  * LoadFromNetwork is responsible for loading theAsset from network and
  * must be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromNetwork(const GExL::typeAssetID theAssetID, sf::Font& theAsset);
private:
  GExL::Uint32 mFontSize;
}; // class SurfaceHandler

#endif