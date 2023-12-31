#pragma once
#ifndef LITTLEHERO_H
#define LITTLEHERO_H
#define FIGHT 1 //战斗状态
#define PREPARE 0 //准备状态
#include "cocos2d.h"
#include "Heroes.h"
#include "Map.h"
#include"Hextech.h"
#define ONLINENUM   2   //联网模式的小小英雄数量
#define M_LEVEL 5    //最大等级
#define Winning_Streak_Rewards 1//连胜或者连败奖励
#define Gold_Per_Turn  5//每回合固定金币
/*匹配模式*/
#define ONLINE 1
#define LOCAL  2
/*部分图片的尺寸*/
#define BuyexpButtonSize cocos2d::Vec2(211, 77)
#define RefreshButtonSize cocos2d::Vec2(211, 77)
#define CloseitemSize        cocos2d::Vec2(50,50)
/*部分标签和图片的位置*/
#define GoldLabelPosition cocos2d::Vec2(694,209)
#define PopulationLabelPosition cocos2d::Vec2(755,948-252)
#define MESSAGELABEL  cocos2d::Vec2(755,948-145)
#define EnditemPosition    cocos2d::Vec2(775,300)
#define DefeatPosition       cocos2d::Vec2(800,474)
/*九个英雄的宏定义*/

#define MONEY 1
#define CLEARMIND 2
#define POPULATION 3

USING_NS_CC;
/****************************************************************************
名称：小小英雄类
功能：记录角色在后台的各种信息,以及玩家的各种操作
操作有：从商店购买棋子，将备战席的棋子移动到棋盘上，购买经验，刷新商店，移动备战席上棋子的位置。
 ****************************************************************************/
class Littlehero : public cocos2d::Node
{
public:
	friend class httpTransmission;
	friend class LHcontroler;
	/*初始化函数*/
	CREATE_FUNC(Littlehero);
	virtual bool init();//重写init函数
	void init_layer();//初始化选手图层
	void init_MyMap();//初始化地图图层
	void set_threelabel();//放置血量，经验和等级的标签
	void set_ExpButton();//放置购买经验的按钮
	void set_Gold();   //放置金币标签,和图标
	void set_Messagelabel();//放置消息标签
	void set_PopulationLabel();//放置人口的图标
	void set_HP_Bar();//显示血条
	void add_Littlehero();//加入小小英雄
	/*
	*小小英雄的血量相关函数
	*/
	void deleteHp(int n) { Hp -= n; }//小小英雄扣血
	void update_Hp(int hp=0);//更新血量
	void setEnemyHp(int enemyHp) { this->enemyHp = enemyHp; }
	/*
	*小小英雄的经验相关函数
	*/
	void Buy_exp();//购买经验值
	void Update_exp(int exp);//更新经验值
	void Checklevel();//判断是否要升级
	/*
	 *小小英雄的金币相关函数
	 */
	void update_gold();//每回合更新金币
	void update_gold(int num);//更新金币
	int get_gold() { return Gold; }	//获取金币数
	void showInterest();//显示利息图标
	void update_WinOrLose(int Win,int Lose);
	/*
	*小小英雄的ID头像相关函数
	*/
	void set_IDs();//显示玩家们的ID
	void set_avatar();//显示头像
	/*
	*小小英雄在备战阶段的操作函数
	*/
	/*拖动棋子*/
	void initMouseListeners();//初始化多个监听器
	bool onLeftMouseDown(EventMouse* event);
	void onLeftMouseMove(EventMouse* event);
	void onLeftMouseUp(EventMouse* event);
	bool onRightMouseDown(EventMouse* event);
	void addhero(Hero* hero, int x) { Preparation[x - 1] = hero; }//添加棋子到备战席
	void addhero(Hero* hero) {};//添加棋子到战斗数组
	void remove(Hero* hero) { hero->removeFromParent(); }//删除这个棋子
	/*海克斯有关的函数*/
	bool is_ClearMind();
	/*
	*类内部成员的操作函数
	*/
	Vector<Hero*> getEnemyFightingHeroes() { return Enemy_fightheros; }
	void setEnemyFightingHeroes(Vector<Hero*> vec) { Enemy_fightheros = vec; }
	cocos2d::Layer* get_heroslayer() { return heroslayer; }

	int getHp() { return Hp; }
	int getEnemyHp() { return enemyHp; }
	int getLevel() { return Level; }
	int getNum() { return Num; }
	int getEnemyNum() { return EnemyNum; }
	void chooseEnemyNum(int Enemy_Num) { EnemyNum = Enemy_Num; }
	int getLastEnemyNum() { return LastEnemyNum; }
	bool getIsAI() { return IsAI; }
	void setHextechStatus(int status) { HextechStatus = status; }
	int getHextechStatus() { return HextechStatus; }
	/*海克斯类*/
	int HextechStatus;//当前英雄的海克斯状态

	void changeHps(int change, int HpsTochange) { Hps[HpsTochange] = Hps[HpsTochange] - change > 0 ? Hps[HpsTochange] - change : 0; }
	int getHps(int which) { return Hps[which]; }
	MapData* get_MyMap() { return My_Map; }
	void set_message(std::string str) { Messagelabel->setString(str); }
	std::string getID() { return ID; }
	void setID(std::string ID) { this->ID = ID; }
	void setRoomParam(int seq, std::string room_num) { this->seq = seq, this->room_num = room_num; }
	/*关于地图的函数*/
	Vec2 getmidposition(int x, int y);//输入数组坐标返回格子中点坐标
	Vec2 getmidposition(Vec2 location);//传入一个二维向量，返回距离这个二维向量最近的格子中点坐标
	Vec2 getmidposition(int x);//输入横坐标，获取备战席上格子中点的坐标
	Vec2 getFightarrayposition(Vec2 location);//输入坐标返回返回距离这个二维向量最近的战场数组坐标
	int getPreparationarrayposition(Vec2 location);//输入输入坐标返回返回距离这个二维向量最近的备战席数组坐标
	/*战斗类***/Hero* Preparation[9] = { nullptr,nullptr,nullptr ,nullptr,nullptr,nullptr,nullptr ,nullptr,nullptr };//备战席
	Hero* Fightfield[4][4] = { {nullptr,nullptr,nullptr ,nullptr},{nullptr,nullptr,nullptr ,nullptr },
							   {nullptr,nullptr,nullptr ,nullptr},{nullptr,nullptr,nullptr ,nullptr } };//战场上的棋子分布
	int HerosType[18] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//记录棋子种类
	/*升星函数*/
	bool FindUpgradeHero(Hero* &hero1, Hero* &hero2, Hero* &hero3);//找到可以升星的英雄们
	void CheckUpgrade(Hero* hero);
private:
	/*小小英雄数据*/
	/*ID*******/
	std::string ID = "";//小小英雄的ID
	int seq;
	std::string room_num;
	/*等级经验*/int Explevel[M_LEVEL] = { 0,4,10,18,30};//经验条，记录每个等级的经验值
	int Level = 1;//等级
	Label* Levellabel;//显示等级的标签
	int Exp = 0;//经验
	Label* Explabel;//显示经验的标签
	Label* PopulationLabel;//人口的标签
	int MaxPeople = 5; 

	/*血量*****/int Hps[4] = { 100,100,100,100 };//血量
	int Hp = 100;
	int enemyHp = 100;
	Label* Hplabel;//显示血量的标签
	Sprite* Hpbar[4];//四个血条
	Sprite* Hpframe;//血条框

	/*金币*****/int Gold = 15;//金币
	Label* Goldlabel;//金币数量标签
	const int WinOrLoseReword[6] = { 0,0,1,1,2,3 };

	/*状态*****/int status = PREPARE;//小小英雄的状态
	int VICTORY = 0;//记录连胜次数
	int LOST = 0;  //记录连败次数
	bool isDragging;//记录是否在拖动图片
	/*图像类***/Sprite* YourLittleHreo;//小小英雄
	Sprite* Movinghero;//正在移动的英雄
	Sprite* Goldimage;//金币图标
	Sprite* Population;//人口图标
	Sprite* avatarimage;//头像图标
	Sprite* Shopbackground;//商店背景
	Sprite* sellarea;//出售区域的图片


	/*棋子拖拽类*/
	int chequers = 0;//场上棋子的数量
	Vec2 Lastposition;
	Hero* Draging_hero;

	Hero* Map[8][4];//地图上的棋子位置
	float MapSizeX[9] = { 382,  490.125 ,  598.25 ,  706.375, 814.5  ,922.625  , 1030.75  , 1138.875   , 1247 };
	float MapSizeY[5] = { 315,426.75,538.5,650.25,762 };
	float PreparationsSizeX[10] = { 279   ,386.88  ,  494.76  ,  602.64  , 710.52  , 818.4    ,926.28 ,   1034.16  ,  1142.04 , 1249.92 };
	float PreparationsSizeY[2] = { 215,315 };
	Vector<Hero*> Enemy_fightheros;//敌方棋子数组
	int Num = 0; //小小英雄编号
	int EnemyNum = 0; //敌人的编号
	int LastEnemyNum = 0; //上把敌人的编号
	bool IsAI = 1; //是不是AI

	/*消息提示类*/Label* Messagelabel;//提示标签

	cocos2d::Layer* heroslayer;//选手图层
	MapData* My_Map;//在Map图层在小小英雄类里面初始化

	/*
	*需要上传的数据
	*/
	Vector<Hero*>fightheros;

};
/****************************************************************************
名称：小小英雄控制器类
功能：管理小小英雄，是一个单例
操作有：获取小小英雄指针的数组
 ****************************************************************************/
class LHcontroler : public cocos2d::Ref
{
public:
	friend Littlehero;
	/*初始化函数*/
	void initlocal();
	void initonline();
    int get_mynumber();//获取这个小小英雄在controler里面的位置
	static LHcontroler* getInstance();//获取单例
	static void clearInstance();//重置单例
	int GetStatus();
	virtual bool init();//初始化
	Littlehero* getMyLittleHero() { return heros.at(get_mynumber()); }
	bool Gameover = 0;
	void Godie(Node* layer);//死亡的结算动画
	void menuCloseCallback(cocos2d::Ref* pSender);
	void Govictory(Node* layer);//赢了的结算动画

	/*数据*/
	Vector<Littlehero*> heros = {};

};
#endif // !SETTING_H 