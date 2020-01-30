#ifndef XENON_STATEMANAGER_H
#define XENON_STATEMANAGER_H
#include <memory>
#include <stack>
#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateManager {
public:
    StateManager();
    ~StateManager()= default;
    void addState(StateRef newState, bool replacing);
    void popState();
    void makeChanges();
    StateRef &getActiveState();
private:
    std::stack<StateRef> states;
    StateRef newState;
    bool adding;
    bool replacing;
    bool removing;
};

#endif