#ifndef MINER_H
#define MINER_H

#include "State.h"
#include "Message.h"
#include "BaseGameEntity.h"

class Miner : public BaseGameEntity
{
public:

    Miner(int id)
        : BaseGameEntity(id),
          machine(this),
          goldCarried(0),
          moneyInBank(0),
          thirst(0),
          fatigue(0)
    {}

    void update();

    void changeLocation(int location);

    bool PocketFull();

    bool Thirsty();

    bool handleMessage(Telegram &telegram);

public:

    StateMachine<Miner> machine;

public:

    int goldCarried;
    int moneyInBank;
    int thirst;
    int fatigue;
    int location;
};

class EnterMinerAndDigForNugget : public State<Miner>
{
public:
    void execute(Miner *entity);
    void enter(Miner *entity);
    void exit(Miner* entity);
    bool onMessage(Miner *miner, Telegram &telegram) { return true; }

    // singleton
    static State *instance() {
        static EnterMinerAndDigForNugget in;
        return &in;
    }
};

class QuenchThirst : public State<Miner>
{
public:
    void execute(Miner *entity);
    void enter(Miner *entity);
    void exit(Miner* entity);
    bool onMessage(Miner *miner, Telegram &telegram) { return true; }

    static State *instance() {
        static QuenchThirst in;
        return &in;
    }
};

class VisitBankAndDepositGold : public State<Miner>
{
public:
    void execute(Miner *entity);
    void enter(Miner *entity);
    void exit(Miner* entity);
    bool onMessage(Miner *miner, Telegram &telegram) { return true; }

    static State *instance() {
        static VisitBankAndDepositGold in;
        return &in;
    }

};

class GoHomeAndSleepThrested : public State<Miner>
{
public:
    void execute(Miner *entity);
    void enter(Miner *entity);
    void exit(Miner* entity);
    bool onMessage(Miner *miner, Telegram &telegram) { return true; }

    static State *instance() {
        static GoHomeAndSleepThrested in;
        return &in;
    }
};

#endif /* MINER_H */