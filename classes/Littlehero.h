#pragma once
#ifndef LITTLEHERO_H
#define LITTLEHERO_H
#define FIGHT 1 //战斗状态
#define PREPARE 0 //准备状态
#include "cocos2d.h"
#include "Heroes.h"
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
	CREATE_FUNC(Littlehero);
	void deleteHp(int n) { Hp -= n; }//小小英雄扣血
	void pulltopreparation();
	virtual bool init();//重写init函数
    void init_layer();//初始化选手图层
	void set_threelabel();//显示血量，经验和等级的标签
	void set_IDs();//显示玩家们的ID
	void set_HP_Bar();//显示血条
	void set_avatar();//显示头像
	cocos2d::Layer* get_heroslayer() { return heroslayer; }
	std::string ID = "";//小小英雄的ID
private:
	int Hp = 100;//血量
	Label* Hplabel;//显示血量的标签
	int gold = 0;//金币
	int level = 1;//等级
	Label* Levellabel;//显示等级的标签
	int Exp = 0;//经验
	Label* Explabel;//显示经验的标签
	int status = PREPARE;//小小英雄的状态
	Sprite avatar;//玩家的头像
	Vector<Hero*> fightheros;//
 	Vector<Hero*> Preparation_Position[9];//备战席
	int chequers = 0;//备战席上棋子的数量
	//void addche(Chequer * che);//添加棋子到备战席
	cocos2d::Layer* heroslayer;//选手图层
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();  //屏幕尺寸
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();     //坐标原点
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
