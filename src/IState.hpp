#ifndef ISTATE_HPP_INCLUDED
#define ISTATE_HPP_INCLUDED
#include <SFML/Window.hpp>
#include "Application.hpp"

#include "TextureAsset.hpp"
#include "FontAsset.hpp"
class IState
{
public:
  IState(Application& theApp);
  ~IState();
  void run(GExL::Uint32 thePrevousState, GExL::Uint32 thePrevousSubState);
  virtual void init() = 0;
  virtual void handleEvent(sf::Event theEvent) = 0;
  virtual void update(float theDeltaTime) = 0;
  virtual void render() = 0;
  virtual void reinit() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
protected:
  bool mRunning;
  Application& mApp;
  GExL::Uint32 mPrevousState;
  GExL::Uint32 mPrevousSubState;
};
#endif