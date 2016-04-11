#include "OptionData.hpp"
#include <fstream>
#include <GExL/Core/templates/TParser.hpp>
#include <SDL.h>
OptionData::OptionData() :
mFilename("Options.cfg"),
mMusic(true),
mSFX(true),
#ifndef GExL_ANDROID
mControls(CTRL_KEY)
#else
mControls(CTRL_TOUCH)
#endif
{

}

OptionData::OptionData(std::string theFilename, bool theMusic, bool theSFX, GExL::Uint32 theControls):
mFilename(theFilename),
mMusic(theMusic),
mSFX(theSFX),
mControls(theControls)
{

}

void OptionData::SaveOptions()
{
#ifndef GExL_ANDROID
	std::ofstream anFileWriter(mFilename.c_str(), std::ios::out);
#else
	std::string anFilename = SDL_AndroidGetInternalStoragePath();
	anFilename += "/";
	anFilename += mFilename;
	std::ofstream anFileWriter(anFilename.c_str(), std::ios::out);
#endif
	if (anFileWriter.good())
	{
		anFileWriter << mMusic << std::endl;
		anFileWriter << mSFX << std::endl;
		anFileWriter << mControls << std::endl;
		anFileWriter.close();
	}
}

void OptionData::LoadOptions()
{
#ifndef GExL_ANDROID
	std::ifstream anFileReader(mFilename.c_str(), std::ios::in);
#else
	std::string anFilename = SDL_AndroidGetInternalStoragePath();
	anFilename += "/";
	anFilename += mFilename;
	std::ifstream anFileReader(anFilename.c_str(), std::ios::in);
#endif

	if (!anFileReader.good())
	{
		SaveOptions();
	}
	else
	{
			char* anCharString = new char[16];
			std::string anString;
			anFileReader.getline(anCharString, 20);
			anString = anCharString;
			mMusic = GExL::BoolParser::ToValue(anString, true);
			anFileReader.getline(anCharString, 20);
			anString = anCharString;
			mSFX = GExL::BoolParser::ToValue(anString, true);
			anFileReader.getline(anCharString, 20);
			anString = anCharString;
#ifndef GEXL_ANDROID
			mControls = GExL::Uint32Parser::ToValue(anString, CTRL_KEY);
#else
			mControls = GExL::Uint32Parser::ToValue(anString, CTRL_TOUCH);
#endif

		}
	anFileReader.close();

}