
#ifndef   DATA_ASSET_HPP_INCLUDED
#define   DATA_ASSET_HPP_INCLUDED

#include <GExL/assets/TAsset.hpp>
#include <GExL/assets/AssetManager.hpp>
#include <GExL/GExL_types.hpp>
#include "tinyxml2.h"
class DataAsset : public GExL::TAsset<std::string>
{
public:


  DataAsset(GExL::AssetManager& theAssetManager);


  DataAsset(GExL::AssetManager& theAssetManager,
    const GExL::typeAssetID theAssetID,
    GExL::AssetLoadTime theLoadTime = GExL::AssetLoadLater,
    GExL::AssetLoadStyle theLoadStyle = GExL::AssetLoadFromFile,
    GExL::AssetDropTime theDropTime = GExL::AssetDropAtZero);

  virtual ~DataAsset();

protected:

private:
  // Variables
  ///////////////////////////////////////////////////////////////////////////
}; // class ImageAsset

#endif // CORE_IMAGE_ASSET_HPP_INCLUDED

   /**
   * @class GQE::ImageAsset
   * @ingroup Core
   * The ImageAsset class is a wrapper around the SFML Image class and is
   * used by the AssetManager to keep track of and provide SFML Images to
   * game states and other entities.
   *
   * Copyright (c) 2010-2011 Ryan Lindeman
   * Permission is hereby granted, free of charge, to any person obtaining a copy
   * of this software and associated documentation files (the "Software"), to deal
   * in the Software without restriction, including without limitation the rights
   * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   * copies of the Software, and to permit persons to whom the Software is
   * furnished to do so, subject to the following conditions:
   *
   * The above copyright notice and this permission notice shall be included in
   * all copies or substantial portions of the Software.
   *
   * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   * THE SOFTWARE.
   */
