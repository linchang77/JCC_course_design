#pragma once
#ifndef LITTLEHERO_H
#define LITTLEHERO_H
#define FIGHT 1 //战斗状态
#define PREPARE 0 //准备状态
#include "cocos2d.h"
#include "Heroes.h"
#include "Map.h"
#define LHNUM 6
USING_NS_CC;
/****************************************************************************
名称：小小英雄类
功能：记录角色在后台的各种信息,以及玩家的各种操作
操作有：从商店购买棋子，将备战席的棋子移动到棋盘上，购买经验，刷新商店，移动备战席上棋子的位置。
 ****************************************************************************/
class Littlehero : public cocos2d::Node
{
public:
	/*初始化函数*/
	CREATE_FUNC(Littlehero);
	virtual bool init();//重写init函数
	void init_layer();//初始化选手图层
	void init_MyMap();//初始化地图图层
	void set_threelabel();//显示血量，经验和等级的标签
	/*
	*小小英雄的血量相关函数
	*/
	void deleteHp(int n) { Hp -= n; }//小小英雄扣血
	void set_HP_Bar();//显示血条
	void update_Hp(int hp);//更新血量
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

	void addhero(Hero * hero);//添加棋子到备战席
	/*
	*获取类内部成员的函数
	*/
	Vector<Hero*> GetEnemyFightingHeroes() {	return Enemy_fightheros;}
	void setEnemyFightingHeroes(Vector<Hero*> vec) { Enemy_fightheros = vec; }
	cocos2d::Layer* get_heroslayer() { return heroslayer; }
	MapData* get_MyMap() { return My_Map; }
	int getHp() { return Hp; }

	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, 
		                                   const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	std::string ID = "";//小小英雄的ID
private:
	/*小小英雄数据*/
	/*ID*******/  
	/*等级经验*/int Explevel[LHNUM] = { 0,2,6,8,20,30 };//经验条，记录每个等级的经验值
	            int Level = 1;//等级
				Label* Levellabel;//显示等级的标签
				int Exp = 0;//经验
				Label* Explabel;//显示经验的标签
	/*血量*****/int Hp = 100;//血量
	            Label* Hplabel;//显示血量的标签
				int EnemyHp;
	/*金币*****/int Gold = 0;//金币
	            Label* Goldlabel;
	/*状态*****/int status = PREPARE;//小小英雄的状态
	            int VICTORY = 0;//记录连败或者连胜次数
				bool isDragging;//记录是否在拖动图片
	/*图像类***/Sprite *avatar;//玩家的头像
	            Sprite* YourLittleHreo;//小小英雄
				Sprite* Movinghero;//正在移动的英雄
	/*战斗类***/Vector<Hero*> Preparation_Position[9];//备战席
	            int chequers = 0;//备战席上棋子的数量
				Hero* Map[6][6];//地图上的棋子位置
				Vector<Hero*> Enemy_fightheros;//敌方棋子数组


	cocos2d::Layer* heroslayer;//选手图层
	MapData* My_Map;//在Map图层在小小英雄类里面初始化
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();  //屏幕尺寸
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();     //坐标原点
	/*
	*需要上传的数据
	*/
	Vector<Hero*> fightheros;//我方场上对战的棋子
};
/****************************************************************************
名称：小小英雄控制器类
功能：管理小小英雄，是一个单例
操作有：获取小小英雄指针的数组
 ****************************************************************************/
class LHcontroler : public cocos2d::Ref
{
public:
	static int get_mynumber();//获取这个小小英雄在controler里面的位置
	friend Littlehero;
	static LHcontroler* getInstance();
	virtual bool init();
	Vector<Littlehero*> heros;

};
#endif // !SETTING_H 
