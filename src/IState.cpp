#include "IState.hpp"

#include <GExL/utils/MathUtil.hpp>

IState::IState(Application& theApp) :
mApp(theApp),
mRunning(false)
{

}
IState::~IState()
{

}
void IState::run(GExL::Uint32 thePrevousState, GExL::Uint32 thePrevousSubState)
{
  mPrevousState = thePrevousState;
  mPrevousSubState = thePrevousSubState;
  if (!mRunning)
  {
    init();
    mRunning = true;
  }
  else
  {
    start();
  }
}