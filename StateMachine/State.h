/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：State.h
 ** 创建人：zeya
 ** 创建日期： 2018-06-16
 **
 ** 描  述：简要描述文件内容
 ** 注  意：本程序是否有些特殊说明
 **************************************************/
#ifndef STATE_H
#define STATE_H

#include <iostream>
#include "Troll.h"

using namespace std;

class State
{
public:

    virtual void enter() = 0;

    virtual void execute(Troll *troll) = 0;

    virtual void exit() = 0;

};

class RunWay : public State
{
public:

    void enter() { cout << "Enter Runway" << endl; }

    void exit() { cout << "Exit Runway" << endl; }

    void execute(Troll *troll);
};

class Patrol : public State
{
public:

    void enter() { cout << "Enter Patrol" << endl; }

    void exit() { cout << "Exit Patrol" << endl; }

    void execute(Troll *troll);
};

class Fight : public State
{
public:

    void enter() { cout << "Enter Fight" << endl; }

    void exit() { cout << "Exit Fight" << endl; }

    void execute(Troll *troll);
};

#endif /* STATE_H */
