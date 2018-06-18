/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：State.cpp
 ** 创建人：zeya
 ** 创建日期： 2018-06-16
 **
 ** 描  述：简要描述文件内容
 ** 注  意：本程序是否有些特殊说明
 **************************************************/
#include "State.h"
#include "Troll.h"

void RunWay::execute(Troll *troll)
{
    if (troll->isSafe()) {
        troll->changeState(new Patrol());
    }
}

void Patrol::execute(Troll *troll)
{
    if (troll->isFight()) {
        troll->changeState(new Fight());
    } else {
        troll->changeState(new RunWay());
    }
}

void Fight::execute(Troll *troll)
{
    if (troll->isVictory()) {
        troll->changeState(new Patrol());
    } else {
        troll->changeState(new RunWay());
    }
}
