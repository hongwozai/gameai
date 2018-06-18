/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：Main.cpp
 ** 创建人：zeya
 ** 创建日期： 2018-06-16
 **
 ** 描  述：简要描述文件内容
 ** 注  意：本程序是否有些特殊说明
 **************************************************/
#include <iostream>
#include "Troll.h"
#include "State.h"

using namespace std;

int main(int argc, char *argv[])
{
    Troll troll(new Patrol());

    troll.update();
    troll.update();
    troll.update();
    troll.update();
    troll.update();
    return 0;
}