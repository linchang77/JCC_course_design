#pragma once

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "Heroes.h"
#include "Map.h"
#include "Littlehero.h"
#define SetitemPosition      cocos2d::Vec2(1600-50,925)
#define SetitemSize          cocos2d::Vec2(50,50)

//模式选项
enum Mode { Practice, Battle };

//需用图层
class Store;
class Board;
class Preparation;

//通用战场类
class Battlefield : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//菜单回调
	void menuReturnCallback(cocos2d::Ref* pSender);
	void menuSetCallback(cocos2d::Ref* pSender);
	void menuStoreCallback(cocos2d::Ref* pSender);

	//http回调
	void preparationCallback(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);

	//服务端数据交互
	void dataExchange(float dt);

	//返回图层
	Store* getCurrentStore();
	Preparation* getCurrentPreparation();

	//实现create方法
	CREATE_FUNC(Battlefield);

private:
	Store* store = nullptr;															//商店（与给定战场相绑定）
	Preparation* preparation = nullptr;												//备战席（与给定战场相绑定）
	static float prepareDuration;
};

//商店界面
class Store : public cocos2d::Layer
{
public:
	virtual bool init();

	//向英雄池增删英雄
	static bool addHero(Hero* newHero);
	static bool removeHero(Hero* toBeRemoved);

	//随机显示英雄
	static cocos2d::Vector<Hero*> randomDisplay();

	//返回当前池中指定价格棋子数目
	static int countHeroByCost(const int cost);

	//获取当前池中第i个n费棋子的拷贝
	static Hero* getHeroByCost(const int cost, const int i);
	
	//回调
	void purchaseCallback(cocos2d::Ref* pSender);	//购买回调
	void refreshCallback(cocos2d::Ref* pSender);	//刷新回调

	//返回/反转商店当前启闭状态
	bool getStatus();
	void reverseStatus();

	//实现create方法
	CREATE_FUNC(Store);

private:
	static cocos2d::Vector<Hero*> pool;								//英雄池（应该是启动游戏时就进行初始化的）
	static const int size = 5;										//商品个数
	cocos2d::Vector<Hero*> displayment;								//当前商店内容
	constexpr static int possibilityTable[MAX_GRADE][MAX_COST] = {	//概率表
		{100, 0, 0, 0, 0},
		{75, 25, 0, 0, 0},
		{55, 30, 15, 0, 0},
		{45, 33, 20, 2, 0},
		{30, 40, 25, 5, 0},
		{19, 35, 35, 10, 1},
		{18, 25, 36, 18, 3},
		{10, 20, 25, 35, 10},
		{5, 10, 20, 40, 25}
	};
	bool on = false;				//商店当前启闭状态
	cocos2d::Sprite* background;	//背景
	cocos2d::Menu* menu;			//菜单
	cocos2d::Menu* refresh;			//刷新按钮
};

//备战席
class Preparation
{
public:
	static Preparation* create();
	void placeHero(Hero* hero);
	bool is_full();

private:
	const int size = 9;																									//备战席尺寸
	const cocos2d::Vec2 startingPoint = { 340.0f, cocos2d::Director::getInstance()->getVisibleSize().height - 684.0f};	//最左侧席位锚点
	const float seatWidth = 104.0f;																						//席位宽度
};

#endif // !BATTLEFIELD_H
