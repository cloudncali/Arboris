#include "DataParser.hpp"
#include <GExL/utils/StringUtil.hpp>
#include <GExL/utils/String_types.hpp>
#include "Application.hpp"
#include "TextureAsset.hpp"
DataParser::DataParser(Application& theApp, std::string theFilename) :
  mApp(theApp)
{
  mDoc.LoadFile(theFilename.c_str());
}

bool DataParser::ParseCharacter(std::string theEntityname, entityx::Entity& theEntity)
{

  tinyxml2::XMLElement* anRoot = mDoc.FirstChildElement();
  tinyxml2::XMLElement* anCat = anRoot->FirstChildElement("characters");
  tinyxml2::XMLElement* anData = NULL;
  tinyxml2::XMLElement* anComponent = NULL;
  tinyxml2::XMLElement* anValue = NULL;

  if (anCat != NULL)
  {
    anData = anCat->FirstChildElement(theEntityname.c_str());
    //is this the correct entity.
    if (anData!=NULL)
    {
      theEntity = mApp.mWorld.entities.create();
      theEntity.assign<EntityTransformable>();
      anComponent = anData->FirstChildElement("physical");
      if (anComponent != NULL)
      {
        entityx::ComponentHandle<EntityPhysical> anPhysical=theEntity.assign<EntityPhysical>();
        anPhysical->name = anComponent->FirstChildElement("name")->GetText();
        anPhysical->condition = GExL::FloatParser::ToValue(anComponent->FirstChildElement("condition")->GetText(), 100.0f);
        anPhysical->toughness = GExL::FloatParser::ToValue(anComponent->FirstChildElement("toughness")->GetText(), 100.0f);
        anPhysical->blocking = GExL::BoolParser::ToValue(anComponent->FirstChildElement("blocking")->GetText(), true);
        anPhysical->weight = GExL::FloatParser::ToValue(anComponent->FirstChildElement("weight")->GetText(), 1.0f);
        anPhysical->size = GExL::Uint32Parser::ToValue(anComponent->FirstChildElement("size")->GetText(), 1);
        anPhysical->destroyed = GExL::BoolParser::ToValue(anComponent->FirstChildElement("destroyed")->GetText(), false);
      }
      anComponent = anData->FirstChildElement("alive");
      if (anComponent != NULL)
      {
        tinyxml2::XMLElement* anStat,*anSkill;
        entityx::ComponentHandle<EntityAlive> anAlive = theEntity.assign<EntityAlive>();
        anAlive->health = GExL::FloatParser::ToValue(anComponent->FirstChildElement("health")->GetText(), 100.0f);
        anAlive->energy = GExL::FloatParser::ToValue(anComponent->FirstChildElement("energy")->GetText(), 100.0f);
        anValue = anComponent->FirstChildElement("behavior");
        
        while (anValue != NULL)
        {
          std::string anBehavior = anValue->GetText();
          if (anBehavior == "wander")
          {
            anAlive->behaviorFlags |= BEHAVIOR_WANDER;
          }
          else if (anBehavior == "controlled")
          {
            anAlive->behaviorFlags |= BEHAVIOR_CONTROLLED;
          }
          anValue = anValue->NextSiblingElement("behavior");
        }
        anValue = anData->FirstChildElement("stats");

        if (anValue != NULL)
        {
          anStat = anValue->FirstChildElement();
          while (anStat != NULL)
          {
            std::string anStatName = anStat->Value();
            if (anStatName == "phys")
            {
              anAlive->stats.phys = GExL::FloatParser::ToValue(anStat->GetText(), 0.0f);
            }
            else if (anStatName == "intel")
            {
              anAlive->stats.intel = GExL::FloatParser::ToValue(anStat->GetText(), 0.0f);
            }
            else if (anStatName == "wit")
            {
              anAlive->stats.wit = GExL::FloatParser::ToValue(anStat->GetText(), 0.0f);
            }
            else if (anStatName == "luck")
            {
              anAlive->stats.luck = GExL::FloatParser::ToValue(anStat->GetText(), 0.0f);
            }
            anStat = anStat->NextSiblingElement();
          }
        }
        anValue = anData->FirstChildElement("skills");

        if (anValue != NULL)
        {
          anSkill = anValue->FirstChildElement();
          while (anSkill != NULL)
          {
            std::string anSkillName = anSkill->Value();
            if (anSkillName == "combat")
            {
              anAlive->skills.combat = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "stealth")
            {
              anAlive->skills.stealth = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "reflex")
            {
              anAlive->skills.reflex= GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "strength")
            {
              anAlive->skills.stealth = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "fortitude")
            {
              anAlive->skills.fortitude = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "magic")
            {
              anAlive->skills.magic = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "lore")
            {
              anAlive->skills.lore = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "craft")
            {
              anAlive->skills.craft = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "willpower")
            {
              anAlive->skills.willpower = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "charisma")
            {
              anAlive->skills.charisma = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            else if (anSkillName == "perception")
            {
              anAlive->skills.perception = GExL::FloatParser::ToValue(anSkill->GetText(), 0.0f);
            }
            anStat = anValue->NextSiblingElement();
          }
        }
      }
      anComponent = anData->FirstChildElement("mobile");
      if (anComponent != NULL)
      {
        entityx::ComponentHandle<EntityMobile> anMobile = theEntity.assign<EntityMobile>();
        anMobile->speed = GExL::FloatParser::ToValue(anComponent->FirstChildElement("speed")->GetText(), 100.0f);
        
        anValue = anComponent->FirstChildElement("type");
        while (anValue != NULL)
        {
          if (anValue->GetText() == "bi")
          {
            anMobile->type |= MOVEMENT_WALK_BI;
          }
          else if (anValue->GetText() == "quad")
          {
            anMobile->type |= MOVEMENT_WALK_QUAD;
          }
          anValue = anValue->NextSiblingElement("type");
        }
      }
      anComponent = anData->FirstChildElement("render");
      if (anComponent != NULL)
      {
        TextureAsset anTexture(mApp.mAssetManager, anComponent->FirstChildElement("texture")->GetText(), GExL::AssetLoadNow);
        entityx::ComponentHandle<EntityRender> anRender = theEntity.assign<EntityRender>(anTexture.GetAsset());
        
        GExL::Uint32 anIndex= GExL::Uint32Parser::ToValue(anComponent->FirstChildElement("index")->GetText(), 0);
        GExL::Uint32 anTilesPerRow = anTexture.GetAsset().getSize().x / Tilemap::TileSize;
        GExL::Uint32 anClipX = (anIndex) % anTilesPerRow;
        GExL::Uint32 anClipY = (anIndex) / anTilesPerRow;
        anRender->SetClipRect(anClipX*Tilemap::TileSize, anClipY*Tilemap::TileSize, Tilemap::TileSize, Tilemap::TileSize);
        
      }
      return true;
    }
  }
  return false;
}