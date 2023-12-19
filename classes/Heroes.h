#pragma once

#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 6		//小小英雄最高等级
#define NUM_HEROES 3	//英雄数量
#define MAX_COST 3		//英雄最大价格
#define Hp_Bar 1    //血条标记
#define Mp_Bar 2    //蓝条标记

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
struct HeroPosition;

//英雄
class Hero : public cocos2d::Node
{
public:
	virtual bool init();    //初始化英雄
	void setSpace(cocos2d::Layer* space)
	{
		hero_space = space;
	};
	bool initHp();    //初始化血条
	void updateHp(float delta);    //血条刷新
	bool initMp();    //初始化蓝条
	void updateMp(float delta);    //蓝条刷新
	void Death();    //死亡淡出动画
	void Move(HeroPosition destination);    //棋子移动，传入移动终点，棋子从当前位置移动到终点，并将棋子位置更新为终点位置
	virtual void Attack(Example* enemy);    //棋子攻击敌人
	HeroPosition getPosition();    //获取英雄位置位置
	HeroImages getImages();							//获取英雄图像信息
	int getCost();									//获取价格
	static Hero* copy(Hero* templt);    //
	CREATE_FUNC(Hero);

protected:
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成样例）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
	int cost;							//价格
	std::string name;					//名称
	HeroPosition position;    //英雄战斗位置坐标（英雄进入战场后赋值）
	cocos2d::Layer* hero_space;    //棋子所在的空间层
	cocos2d::Sprite* body;    //棋子
	cocos2d::Sprite* hp_bar;    //血条框
	cocos2d::Sprite* hp;    //血条
	cocos2d::Sprite* mp_bar;    //蓝条框
	cocos2d::Sprite* mp;    //蓝条
	float maxhp;    //最大血量
	float realhp;    //实时血量
	float maxmp;    //最大蓝量
	float realmp;    //实时蓝量
	float range;    //攻击距离
	float frequency;    //攻击频率
	float movespeed;    //移动速度
	bool ismove;    //判断是否在移动
	bool isdead;    //判断是否死亡（调用Death函数后判断为死亡，写战斗的需要在一轮战斗结束后将所有英雄数值回复，死亡情况改为false）
	int counter = 0;    //计数器
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
public:
	virtual bool init() override;
	virtual void Attack(Example* enemy) override;
protected:
	cocos2d::Sprite* bullet;    //攻击子弹（假定例子为射手）
};



#endif // !HEROES_H
