#ifndef DATA_HANDLER_HPP_INCLUDED
#define DATA_HANDLER_HPP_INCLUDED
#include <GExL/assets/TAssetHandler.hpp>
#include "RPG_types.hpp"

class DataHandler : public GExL::TAssetHandler < sf::Texture >
{
public:
  DataHandler();
  /// Provides the DataHandler class for managing sf::Image assets

  /**
  * DataHandler deconstructor
  */
  virtual ~DataHandler();

protected:
  /**
  * LoadFromFile is responsible for loading theAsset from a file and must
  * be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromFile(const GExL::typeAssetID theAssetID, std::string & theAsset);
  /**
  * LoadFromMemory is responsible for loading theAsset from memory and
  * must be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromMemory(const GExL::typeAssetID theAssetID, sf::Texture& theAsset);
  /**
  * LoadFromNetwork is responsible for loading theAsset from network and
  * must be defined by the derived class since the interface for TYPE is
  * unknown at this stage.
  * @param[in] theAssetID of the asset to be loaded
  * @param[in] theAsset pointer to load
  * @return true if the asset was successfully loaded, false otherwise
  */
  virtual bool LoadFromNetwork(const GExL::typeAssetID theAssetID, sf::Texture& theAsset);
private:
}; // class TextureHandler

#endif