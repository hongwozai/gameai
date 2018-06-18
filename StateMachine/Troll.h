/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：Troll.h
 ** 创建人：zeya
 ** 创建日期： 2018-06-16
 **
 ** 描  述：Troll巨魔
 ** 注  意：本程序是否有些特殊说明
 **************************************************/
#ifndef TROLL_H
#define TROLL_H

#include <memory>

class State;
class Troll
{
public:

    Troll(State *state);

    void update();

    void changeState(State *state);

    bool isSafe();

    bool isFight();

    bool isVictory();

private:

    std::shared_ptr<State> state;
};

#endif /* TROLL_H */
