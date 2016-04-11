#ifndef STATE_MANAGER_HPP_INCLUDED
#define STATE_MANAGER_HPP_INCLUDED
#include "RPG_types.hpp"
#include <SFML/Window.hpp>
#include <GExL/container/TArray.hpp>
class StateManager
{
public:
  StateManager();
  ~StateManager();
  void Init(typeStateID theStartingState);
  void UpdateStates();
  void RegisterState(typeStateID theStateID, IState* theNewState);
  void handleEvent(sf::Event theEvent);
  void update(float theDeltaTime);
  void render();
  void SetNextState(typeStateID theStateID);
  void SetNextSubState(typeStateID theStateID);
  typeStateID GetCurrentState();
  typeStateID GetCurrentSubState();
private:
  typeStateID mCurrentState;
  typeStateID mCurrentSubState;
  typeStateID mNextState;
  typeStateID mNextSubState;
  GExL::TArray<IState*> mStates;
};
#endif
