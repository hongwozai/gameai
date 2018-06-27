#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Entity.h"
#include "Miner.h"
#include "Elsa.h"

using namespace std;

int main(int argc, char *argv[])
{
    Miner miner(MinerBob);
    miner.machine.setCurrentState(EnterMinerAndDigForNugget::instance());
    EntityMgr->registerEntity(MinerBob, &miner);

    Elsa elsa;
    elsa.machine.setGlobalState(WifeGlobalState::instance());
    elsa.machine.setCurrentState(Sweet::instance());
    EntityMgr->registerEntity(ELSA, &elsa);

    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    miner.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    elsa.update();
    return 0;
}
