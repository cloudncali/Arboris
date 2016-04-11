#ifndef OPTION_DATA_HPP_INCLUDED
#define OPTION_DATA_HPP_INCLUDED
#include <GExL/GExL_types.hpp>

enum CONTROL_OPTIONS
{
  CTRL_KEY=0,
  CTRL_TOUCH,
  CTRL_TILT
};
class OptionData
{
public:
  std::string mFilename;
  bool mMusic;
  bool mSFX;
  GExL::Uint32 mControls;
  OptionData();
  OptionData(std::string theFilename, bool theMusic, bool theSFX, GExL::Uint32 theControls);
  void LoadOptions();
  void SaveOptions();
};

#endif
