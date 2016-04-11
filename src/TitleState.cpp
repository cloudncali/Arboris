#include "TitleState.hpp"
#include "Application.hpp"
#include <GExL/utils/MathUtil.hpp>

TitleState::TitleState(Application& theApp) :
IState(theApp),
mBackgroundImage(theApp.mAssetManager, "resources/images/bg.png", GExL::AssetLoadNow),
mMainFont(theApp.mAssetManager, "resources/Aaargh.ttf", GExL::AssetLoadNow)
{

}
TitleState::~TitleState()
{

}
void TitleState::init()
{
}
void TitleState::reinit()
{
}
void TitleState::handleEvent(sf::Event theEvent)
{

}
void TitleState::update(float theDeltaTime)
{

}
void TitleState::render()
{
	//Apply the Background
}
void TitleState::start()
{
}
void TitleState::stop()
{
}