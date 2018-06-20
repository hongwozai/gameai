/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：Elsa.h
 ** 创建人：zeya
 ** 创建日期： 2018-06-20
 **
 ** 描  述：简要描述文件内容
 ** 注  意：本程序是否有些特殊说明
 **************************************************/
#ifndef ELSA_H
#define ELSA_H

#include <iostream>

#include "Entity.h"
#include "State.h"
#include "BaseGameEntity.h"

using namespace std;

class Elsa : public BaseGameEntity
{
public:

    Elsa()
        : BaseGameEntity(ELSA),
          fatigue(0),
          machine(this)
    {}

    bool isFatigue() {
        return fatigue > 10;
    }

    void update() {
        machine.update();
    }

    ~Elsa() {}

public:

    int fatigue;

public:

    StateMachine<Elsa> machine;
};

class VisitBashroom : public State<Elsa>
{
public:

    void execute(Elsa *entity) {
        cout << "Elsa visbashroom" << endl;
        entity->fatigue = 0;
        entity->machine.revertToPrevState();
    }

    void enter(Elsa *entity) {
        cout << "Elsa visit bashroom" << endl;
    }

    void exit(Elsa *entity) {
        cout << "Elsa go away" << endl;
    }

    static VisitBashroom *instance() {
        static VisitBashroom vb;
        return &vb;
    }

private:

};

class WifeGlobalState : public State<Elsa>
{
public:

    void execute(Elsa *entity) {
        if (entity->isFatigue()) {
            entity->machine.changeState(VisitBashroom::instance());
        }
    }

    void enter(Elsa *entity) {}

    void exit(Elsa *entity) {}

public:

    static WifeGlobalState *instance() {
        static WifeGlobalState wgs;
        return &wgs;
    }
};

class Sweet : public State<Elsa>
{
public:

    void execute(Elsa *entity) {
        entity->fatigue++;
        cout << "Elsa Sweet ..." << endl;
    }

    void enter(Elsa *entity) {
        cout << "Elsa Start Sweet." << endl;
    }

    void exit(Elsa *entity) {}

    static Sweet *instance() {
        static Sweet sw;
        return &sw;
    }
};

#endif /* ELSA_H */
