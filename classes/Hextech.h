#pragma once
#ifndef HEXTECH_H
#define HEXTECH_H
#include "cocos2d.h"
#include "GeneralCreator.h"
#include"Littlehero.h"
/*���庣��˹����*/
#define MONEY 1
#define CLEARMIND 2
#define POPULATION 3
USING_NS_CC;
class Hextech :public cocos2d::Layer
{
public:
	CREATE_FUNC(Hextech);
	virtual bool init();//��дinit����
private:
	void choseCallback1(cocos2d::Ref* pSender);	//ѡ���һ���Ļص�
	void choseCallback2(cocos2d::Ref* pSender);	//ѡ��ڶ����Ļص�
	void choseCallback3(cocos2d::Ref* pSender);	//ѡ��������Ļص�
};

#endif // !HEXTECH_H