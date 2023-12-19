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
class Hero : public cocos2d::Node
{
public:
	virtual bool init();    //初始化英雄
	void setSpace(cocos2d::Layer* space)
	{
		hero_space = space;
	};
	void Appear_in_Preparation();    //渲染并出现在备战席
	bool initHp();    //初始化血条
	void updateHp(float delta);    //血条刷新
	bool initMp();    //初始化蓝条
	void updateMp(float delta);    //蓝条刷新
	void Death();    //死亡淡出动画
	void Move();    //棋子移动
	void Attack();    //棋子攻击
	HeroImages getImages();							//获取英雄图像信息
	int getCost();									//获取价格
	static Hero* copy(Hero* templt);    //
	CREATE_FUNC(Hero);

private:
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成样例）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
	int cost;							//价格
	std::string name;					//名称
	HeroPosition position;    //英雄战斗位置坐标
	cocos2d::Layer* hero_space;    //棋子所在的空间层
	cocos2d::Sprite* body;    //棋子
	cocos2d::Sprite* hp_bar;    //血条框
	cocos2d::Sprite* hp;    //血条
	float maxhp;    //最大血量
	float realhp;    //实时血量
	float range;    //攻击距离
	float frequency;    //攻击频率
	cocos2d::Sprite* mp_bar;    //蓝条框
	cocos2d::Sprite* mp;    //蓝条
};

struct HeroPosition
	//英雄战斗位置坐标
{
	int x;    //横坐标
	int y;    //纵坐标
};



//英雄图像信息
struct HeroImages
{
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成序列）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
};

class Example :public Hero
	//派生具体英雄例子
{
	virtual bool init() override;
};



#endif // !HEROES_H
