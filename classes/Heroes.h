#pragma once

#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 9		//小小英雄最高等级
#define NUM_HEROES 3	//英雄数量
#define MAX_COST 5		//英雄最大价格

//小小英雄
class LittleHero : public cocos2d::Sprite
{
public:
	//单例？
	static LittleHero* getInstance();

	//返回等级
	int getGrade();

private:
	int grade;			//等级
};

struct HeroImages;

//英雄
class Hero : public cocos2d::Sprite
{
public:
	HeroImages getImages();							//获取英雄图像信息
	int getCost();									//获取价格
	//其它东西请棋子设计者自行实现


private:
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成样例）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
	int cost;							//价格
	std::string name;					//名称
};

//英雄图像信息
struct HeroImages
{
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成序列）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
};

#endif // !HEROES_H
