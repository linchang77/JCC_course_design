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
	friend class httpTransmission;
	CREATE_FUNC(Littlehero);
	void deleteHp(int n) { Hp -= n; }//小小英雄扣血
	void pulltopreparation();
	virtual bool init();//重写init函数
    void init_layer();//初始化选手图层
	void set_threelabel();//显示血量，经验和等级的标签
	void set_IDs();//显示玩家们的ID
	void set_HP_Bar();//显示血条
	void set_avatar();//显示头像
	void update_Hp(int hp);//更新血量
	void update_exp(int exp);//更新经验值
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, 
		                                   const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	cocos2d::Layer* get_heroslayer() { return heroslayer; }
	Vector<Hero*>* get_E_F() { return &Enemy_fightheros; }
	std::string ID = "";//小小英雄的ID
	int getLevel() { return level; }
	int getHp() { return Hp; }
	void setEnemyHp(int Hp) { EnemyHp = Hp; }
private:
	int Explevel[6] = {};//经验条，记录每个等级的经验值
	int Hp = 100;//血量
	int EnemyHp;//敌方血量
	Label* Hplabel;//显示血量的标签
	int gold = 0;//金币
	int level = 1;//等级
	Label* Levellabel;//显示等级的标签
	int Exp = 0;//经验
	Label* Explabel;//显示经验的标签
	int status = PREPARE;//小小英雄的状态
	Sprite avatar;//玩家的头像
 	Vector<Hero*> Preparation_Position[9];//备战席
	int chequers = 0;//备战席上棋子的数量
	Vector<Hero*> Enemy_fightheros;//敌方棋子
	//void addche(Chequer * che);//添加棋子到备战席
	cocos2d::Layer* heroslayer;//选手图层
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();  //屏幕尺寸
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();     //坐标原点
	/*
	*需要上传的数据
	*/
	Vector<Hero*> fightheros;//场上对战的棋子
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
