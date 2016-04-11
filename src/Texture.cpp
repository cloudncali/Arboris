#include <SDL_image.h>
#include <GExL/Core/loggers/Log_macros.hpp>

#include "Texture.hpp"
SDL_Renderer* Texture::sRenderer = NULL;
void Texture::RegisterRenderer(SDL_Renderer* theRenderer)
{
	if (theRenderer != NULL)
	{
		sRenderer = theRenderer;
	}
	else
		FLOG(GExL::StatusAppInitFailed) << "Null Renderer pointer passed to Texture::RegisterRenderer()" << std::endl;
}



Texture::Texture() : mTexture(NULL){}

bool Texture::LoadFromFile(std::string theFilename)
{
	bool anResult = false;
	if (theFilename.length() > 0)
	{
		SDL_Texture* anTexture = NULL;
		SDL_Surface* anLoadedSurface = IMG_Load(theFilename.c_str());
		if (anLoadedSurface != NULL)
		{
			//Color key image
			SDL_SetColorKey(anLoadedSurface, SDL_TRUE, SDL_MapRGB(anLoadedSurface->format, 0xFF, 0, 0xFF));
			anTexture = SDL_CreateTextureFromSurface(Texture::sRenderer, anLoadedSurface);
			if (anTexture != NULL)
			{
				mTexture = anTexture;
				SDL_FreeSurface(anLoadedSurface);
				anResult = true;
			}
		}
	}
	return anResult;
}

void Texture::Render(GExL::Vector2f thePosition, float theRotation, GExL::Vector2f theScale, GExL::IntRect theClipRect, GExL::Vector2f theOrigin, Color theColor)
{
	SDL_Rect anSrcRect, anDstRect;
	if (mTexture != NULL)
	{
		anSrcRect.x = theClipRect.x;
		anSrcRect.y = theClipRect.y;

		anDstRect.x = (GExL::Int32)thePosition.x;
		anDstRect.y = (GExL::Int32)thePosition.y;
		if (theClipRect.w == 0 || theClipRect.h == 0)
		{
			SDL_QueryTexture(mTexture, NULL, NULL, &anDstRect.w, &anDstRect.h);
		}
		else
		{
			anDstRect.w = theClipRect.w;
			anDstRect.h = theClipRect.h;
		}
		anSrcRect.w = anDstRect.w;
		anSrcRect.h = anDstRect.h;
		anDstRect.w *= theScale.x;
		anDstRect.h *= theScale.y;
		anDstRect.x -= (anDstRect.w*(GExL::Int32)theOrigin.x);
		anDstRect.y -= (anDstRect.h*(GExL::Int32)theOrigin.y);
		SDL_SetTextureColorMod(mTexture, theColor.r, theColor.g, theColor.b);
		SDL_RenderCopy(sRenderer, mTexture, &anSrcRect, &anDstRect);
	}
}
bool Texture::GenerateTilemapTexture(Texture& mTileset, tmxparser::TmxMap& theMap)
{
  Uint32 anPixelFormat;
  SDL_QueryTexture(mTileset.mTexture, &anPixelFormat, NULL, NULL, NULL);
  SDL_Texture *anTilemapTexture = SDL_CreateTexture(sRenderer, anPixelFormat, SDL_TEXTUREACCESS_TARGET, theMap.width*32, theMap.height * 32);
  SDL_SetRenderTarget(sRenderer, anTilemapTexture);
  GExL::Uint32 anTileIndex = 0;
  for (auto it = theMap.layerCollection.begin(); it != theMap.layerCollection.end(); ++it)
  {
    for (auto it2 = it->tiles.begin(); it2 != it->tiles.end(); ++it2)
    {
      GExL::Uint32 anTileGID = it2->gid - theMap.tilesetCollection.at(it2->tilesetIndex).firstgid;
      GExL::Uint32 anTilesetWidth = theMap.tilesetCollection.at(it2->tilesetIndex).colCount;
      GExL::Int32 anTileSourceX = anTileGID % anTilesetWidth;
      GExL::Int32 anTileSourceY = anTileGID / anTilesetWidth;
      GExL::Int32 anTileDestX = anTileIndex % theMap.width;
      GExL::Int32 anTileDestY = anTileIndex / theMap.width;

      SDL_Rect anSourceRect, anDestRect;
      anSourceRect.x = anTileSourceX * 32;
      anSourceRect.y = anTileSourceY * 32;
      anDestRect.x = anTileDestX * 32;
      anDestRect.y = anTileDestY * 32;
      anSourceRect.w = anDestRect.w = anSourceRect.h = anDestRect.h = 32;
      SDL_RenderCopy(sRenderer, mTileset.mTexture, &anSourceRect, &anDestRect);
      anTileIndex++;
    }
  }
  mTexture = anTilemapTexture;
  SDL_SetRenderTarget(sRenderer, NULL);
  return true;
}