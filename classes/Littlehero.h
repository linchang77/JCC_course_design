#pragma once

#ifndef LITTLEHERO_H
#define LITTLEHERO_H

#include "cocos2d.h"
USING_NS_CC;
/****************************************************************************
名称：小小英雄类
功能：记录角色在后台的各种信息
 ****************************************************************************/
class Littlehero : public cocos2d::Layer
{
public:
	void deleteHp(int n) { Hp -= n; }//小小英雄扣血

private:
	int Hp = 100;//血量
	Vector<Node*> Preparation_Position[9];//备战席
	int chequers = 0;//备战席上棋子的数量
	//void addche(Chequer * che);//添加棋子到备战席

};

#endif // !SETTING_H 
