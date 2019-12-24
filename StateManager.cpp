#include "StateManager.h"

StateManager::StateManager() {
    adding = false;
    replacing = false;
    removing = false;
}

StateManager::~StateManager() = default;

void StateManager::addState(StateRef newState, bool replacing) {
    this->newState = std::move (newState);
    this->replacing = replacing;
    this->adding = true;
}

void StateManager::popState() {
    removing = true;
}

void StateManager::makeChanges() {
    if (removing && !states.empty()){
        states.pop();
        if (!states.empty())
            states.top()->resume();
        removing=false;
    }
    if (adding){
        if (!states.empty()){
            if(replacing)
                states.pop();
            else
                states.top()->pause();
        }
        states.push(std::move(newState));
        states.top()->init();
        adding = false;
    }
}

StateRef &StateManager::getActiveState() {
    return states.top();
}