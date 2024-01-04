#pragma once
#ifndef HEXTECH_H
#define HEXTECH_H
#include "cocos2d.h"
#include "GeneralCreator.h"
#include"Littlehero.h"
/*定义海克斯类型*/
#define MONEY 1
#define CLEARMIND 2
#define POPULATION 3
USING_NS_CC;
class Hextech :public cocos2d::Layer
{
public:
	CREATE_FUNC(Hextech);
	virtual bool init();//重写init函数
private:
	void choseCallback1(cocos2d::Ref* pSender);	//选择第一个的回调
	void choseCallback2(cocos2d::Ref* pSender);	//选择第二个的回调
	void choseCallback3(cocos2d::Ref* pSender);	//选择第三个的回调
};

#endif // !HEXTECH_H