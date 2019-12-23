#ifndef XENON_STATE_H
#define XENON_STATE_H


class State {
public:
    virtual ~State();
    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw () = 0;
    virtual void pause ();
    virtual void resume();
};


#endif //XENON_STATE_H
