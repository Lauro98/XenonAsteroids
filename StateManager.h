#ifndef XENON_STATEMANAGER_H
#define XENON_STATEMANAGER_H

#include <memory>
#include <stack>
#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateManager {
private:
    std::stack<StateRef> states;
    StateRef newState;
    bool isAdding;
    bool isReplacing;
    bool isRemoving;
public:
    StateManager();
    ~StateManager();
    void addState(StateRef newState, bool isReplacing);
    void popState();
    void makeChanges();
    StateRef &getActiveState();
};

#endif //XENON_STATEMANAGER_H