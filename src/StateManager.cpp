#include "StateManager.hpp"
#include "IState.hpp"
StateManager::StateManager() :
mStates(STATE_COUNT),
mNextState(STATE_NONE),
mCurrentState(STATE_NONE),
mNextSubState(STATE_NONE),
mCurrentSubState(STATE_NONE)
{
	for (int anStateIndex = 0; anStateIndex < STATE_COUNT; ++anStateIndex)
	{
		mStates[anStateIndex] = NULL;
	}
}
StateManager::~StateManager()
{

}
typeStateID StateManager::GetCurrentState()
{
  return mCurrentState;
}
typeStateID StateManager::GetCurrentSubState()
{
  return mCurrentSubState;
}
void StateManager::RegisterState(typeStateID theStateID, IState* theNewState)
{
	if (theNewState != NULL && theStateID<STATE_COUNT && theStateID>STATE_NONE && mStates[theStateID] == NULL)
	{
		mStates[theStateID] = theNewState;
		ILOG() << "State: " << theStateID << "registerd.";
	}
	else if (theNewState == NULL)
	{
		ELOG() << "State assigned as: State" << theStateID << "is NULL" << std::endl;
	}
	else if (theNewState == NULL)
	{
		ELOG() << "State assigned an ID of:" << theStateID << "which is out of bounds." << std::endl;
	}
	else if (mStates[theStateID] == NULL)
	{
		ELOG() << "State is already registerd." << std::endl;
	}
}
void StateManager::SetNextState(GExL::Uint32 theStateID)
{
	if (theStateID != STATE_NONE)
	{
		mNextState = theStateID;
	}
}
void StateManager::SetNextSubState(GExL::Uint32 theStateID)
{
	mNextSubState = theStateID;
}
void StateManager::UpdateStates()
{
	if (mCurrentState != mNextState)
	{
		if (mStates[mCurrentState]!=NULL)
			mStates[mCurrentState]->stop();
		mStates[mNextState]->run(mCurrentState, mCurrentSubState);
		mCurrentState = mNextState;
	}
	if (mCurrentSubState != mNextSubState)
	{
		if (mCurrentSubState != STATE_NONE)
			mStates[mCurrentSubState]->stop();
		if (mNextSubState != STATE_NONE)
			mStates[mNextSubState]->run(mCurrentState, mCurrentSubState);
		else if (mStates[mCurrentState] != NULL && mCurrentState != STATE_NONE)
			mStates[mCurrentState]->run(mCurrentState, mCurrentSubState);
		mCurrentSubState = mNextSubState;
	}
}
void StateManager::handleEvent(sf::Event theEvent)
{
	if (mStates[mCurrentSubState] != NULL && mCurrentSubState != STATE_NONE)
	{
		mStates[mCurrentSubState]->handleEvent(theEvent);
	}
	else if (mStates[mCurrentState] != NULL && mCurrentState != STATE_NONE)
	{
		mStates[mCurrentState]->handleEvent(theEvent);
	}
}
void StateManager::update(float theDeltaTime)
{
	if (mStates[mCurrentSubState] != NULL && mCurrentSubState != STATE_NONE)
	{
		mStates[mCurrentSubState]->update(theDeltaTime);
	}
	else if (mStates[mCurrentState] != NULL && mCurrentState != STATE_NONE)
	{
		mStates[mCurrentState]->update(theDeltaTime);
	}
}
void StateManager::render()
{
	if (mStates[mCurrentState] != NULL && mCurrentState != STATE_NONE)
	{
		mStates[mCurrentState]->render();
	}
	if (mStates[mCurrentSubState] != NULL && mCurrentSubState != STATE_NONE)
	{
		mStates[mCurrentSubState]->render();
	}
}