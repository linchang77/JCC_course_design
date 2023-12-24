#pragma once

#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 9		//小小英雄最高等级
#define NUM_HEROES 3	//英雄数量
#define MAX_COST 5		//英雄最大价格

struct HeroImages;
enum HeroType { EXAMPLE };	//英雄种类

//英雄
class Hero : public cocos2d::Node
{
public:
	virtual bool init();							//初始化
	HeroImages getImages();							//获取英雄图像信息
	int getCost();									//获取价格
	HeroType getID();								//获取ID
	virtual void getSpriteReady();					//生成精灵
	static Hero* createExactHero(HeroType type);	//创建特定种类的英雄
	static Hero* copy(Hero* templt);				//拷贝
	//其它东西请棋子设计者自行实现

	CREATE_FUNC(Hero);

protected:
	cocos2d::Sprite* body;				//精灵指针
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成Vector）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
	int cost;							//价格
	std::string name;					//名称
	HeroType id;						//ID（种类标志）
};

//（样例）英雄子类
class Example : public Hero
{
public:
	virtual bool init();

	CREATE_FUNC(Example);
};

//英雄图像信息
struct HeroImages
{
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成序列）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
};

#endif // !HEROES_H
