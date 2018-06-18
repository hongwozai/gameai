#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Entity.h"
#include "Miner.h"

using namespace std;

int main(int argc, char *argv[])
{
    Miner miner(MinerBob);
    miner.machine.setCurrentState(EnterMinerAndDigForNugget::instance());
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
    return 0;
}
