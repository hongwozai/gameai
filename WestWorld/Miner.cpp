#include <iostream>

#include "Entity.h"
#include "Miner.h"

using namespace std;

void Miner::update()
{
    this->thirst++;
    machine.update();
}

void Miner::changeLocation(int location)
{
    this->location = location;
}

bool Miner::PocketFull()
{
    if (goldCarried > 10) {
        return true;
    } else {
        return false;
    }
}

bool Miner::Thirsty()
{
    if (thirst > 10) {
        return true;
    } else {
        return false;
    }
}

void EnterMinerAndDigForNugget::execute(Miner *entity)
{
    entity->goldCarried++;
    entity->fatigue++;

    cout << "id: " << entity->getID() << ":"
         << "Pickin' up a nugget" << endl;

    if (entity->PocketFull()) {
        entity->machine.changeState(VisitBankAndDepositGold::instance());
    }
    if (entity->Thirsty()) {
        entity->machine.changeState(QuenchThirst::instance());
    }
}

void EnterMinerAndDigForNugget::enter(Miner *entity)
{
    if (entity->location != GOLDMINE) {
        cout << "id: " << entity->getID() << ":"
             << "Walkin' to the gold mine" << endl;
        entity->changeLocation(GOLDMINE);
    }
}

void EnterMinerAndDigForNugget::exit(Miner *entity)
{
    cout << "id: " << entity->getID() << ":"
         << "Ah'm leavin' the gold mine with mah pockets full sweet gold" << endl;
}

void QuenchThirst::enter(Miner *)
{}
void QuenchThirst::exit(Miner *)
{}
void QuenchThirst::execute(Miner *)
{}

void VisitBankAndDepositGold::enter(Miner *)
{}
void VisitBankAndDepositGold::exit(Miner *)
{}
void VisitBankAndDepositGold::execute(Miner *)
{}

void GoHomeAndSleepThrested::enter(Miner *)
{}
void GoHomeAndSleepThrested::exit(Miner *)
{}
void GoHomeAndSleepThrested::execute(Miner *)
{}
