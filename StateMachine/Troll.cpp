/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：Troll.cpp
 ** 创建人：zeya
 ** 创建日期： 2018-06-16
 **
 ** 描  述：简要描述文件内容
 ** 注  意：本程序是否有些特殊说明
 **************************************************/
#include <time.h>
#include "Troll.h"
#include "State.h"

using namespace std;

Troll::Troll(State *state)
{
    this->state.reset(state);
    this->state->enter();
    srand(time(0));
}

void Troll::update()
{
    this->state->execute(this);
}

void Troll::changeState(State *state)
{
    this->state->exit();

    // this->state = state;
    this->state.reset(state);

    this->state->enter();
}

bool Troll::isSafe()
{
    return true;
}

bool Troll::isFight()
{
    if ((rand() % 2) == 0) {
        cout << "Troll Fight!" << endl;
        return true;
    } else {
        cout << "Troll not Fight!" << endl;
        return false;
    }
}

bool Troll::isVictory()
{
    if ((rand() % 2) == 0) {
        cout << "Troll victory!" << endl;
        return true;
    } else {
        cout << "Troll failure!" << endl;
        return false;
    }
}