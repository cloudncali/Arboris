#ifndef DATA_PARSER_HPP_INCLUDED
#define DATA_PARSER_HPP_INCLUDED
#include "tinyxml2.h"
#include "RPG_types.hpp"
#include "entityx\entityx.h"
class DataParser
{
public:
  DataParser(Application& theApp);
  bool ParseCharacter(std::string theEntityname, entityx::Entity& theEntity);
private:
  Application& mApp;
};

#endif