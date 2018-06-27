#ifndef STATE_H
#define STATE_H

#include "Message.h"

template <class Entity>
class State
{
public:

    virtual ~State() {}
    virtual void execute(Entity *entity) = 0;
    virtual void enter(Entity *entity)   = 0;
    virtual void exit(Entity *entity)    = 0;

    virtual bool onMessage(Entity *entity, Telegram &telegram) = 0;

protected:
    State() {}

};

template <class Entity>
class StateMachine
{
public:

    StateMachine(Entity *entity)
        : currentState(0),
          previousState(0),
          globalState(0),
          entity(entity)
    {}

    void update() const;

    void changeState(State<Entity> *state);

    void revertToPrevState();

    State<Entity> *getCurrentState() const { return currentState; }

    State<Entity> *getPrevState() const { return previousState; }

    State<Entity> *getGlobalState() const { return globalState; }

    void setCurrentState(State<Entity> *s) { currentState = s; };
    void setPrevState(State<Entity> *s) { previousState = s; };
    void setGlobalState(State<Entity> *s) { globalState = s; };

    bool handleMessage(Telegram &telegram);

private:

    State<Entity> *currentState;

    State<Entity> *previousState;

    State<Entity> *globalState;

private:

    Entity *entity;
};

template <class Entity>
void StateMachine<Entity>::update() const
{
    if (globalState) {
        globalState->execute(entity);
    }
    if (currentState) {
        currentState->execute(entity);
    }
}

template <class Entity>
void StateMachine<Entity>::changeState(State<Entity> *state)
{
    currentState->exit(entity);
    previousState = currentState;
    currentState  = state;
    currentState->enter(entity);
}

template <class Entity>
void StateMachine<Entity>::revertToPrevState()
{
    currentState->exit(entity);
    currentState = previousState;
    currentState->enter(entity);
}

template <class Entity>
bool StateMachine<Entity>::handleMessage(Telegram &telegram)
{
    return ((currentState && currentState->onMessage(entity, telegram)) &&
            (globalState && globalState->onMessage(entity, telegram)));
}

#endif /* STATE_H */