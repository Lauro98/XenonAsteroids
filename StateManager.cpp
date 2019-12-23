#include "StateManager.h"

StateManager::StateManager() {
    isAdding = false;
    isReplacing = false;
    isRemoving = false;
}

StateManager::~StateManager() = default;

void StateManager::addState(StateRef newState, bool isReplacing) {
    this->newState = std::move (newState);
    this->isReplacing = isReplacing;
    this->isAdding = true;
}

void StateManager::popState() {
    isRemoving = true;
}

void StateManager::makeChanges() {
    if (isRemoving && !states.empty()){
        states.pop();
        if (!states.empty())
            states.top()->resume();
        isRemoving=false;
    }
    if (isAdding){
        if (!states.empty()){
            if(isReplacing)
                states.pop();
            else
                states.top()->pause();
        }
        states.push(std::move(newState));
        states.top()->init();
        isAdding = false;
    }
}

StateRef &StateManager::getActiveState() {
    return states.top();
}