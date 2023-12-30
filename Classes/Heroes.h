#pragma once

#ifndef HEROES_H
#define HEROES_H
#include "cocos2d.h"

#define MAX_GRADE 9		//小小英雄最高等级
#define NUM_HEROES 3	//英雄数量
#define MAX_COST 5		//英雄最大价格
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
enum HeroType { GOLEM };	//英雄种类

struct HeroPosition
	//英雄战斗位置坐标
{
	int x;    //横坐标
	int y;    //纵坐标
};

//英雄
class Hero : public cocos2d::Node
{
public:
	virtual bool init();    //初始化英雄
	HeroType getID() const { return id; }    //获取ID
	virtual void getSpriteReady();					//生成精灵
	static Hero* createExactHero(HeroType type);	//创建特定种类的英雄
	void SetSpace(cocos2d::Layer* space)
	{
		hero_space = space;
	};
	bool InitHp();    //初始化血条
	void UpdateHp(float delta);    //血条刷新
	bool InitMp();    //初始化蓝条
	void UpdateMp(float delta);    //蓝条刷新
	virtual void Death();    //死亡动画
	virtual void Attack();    //攻击动画
	virtual void Move(HeroPosition destination);    //移动动画
	void StarUp(Hero* a, Hero* b, Hero* c);    //升星动画
	//virtual void Ultimate();    //大招动画
	HeroPosition getHeroPosition();    //获取英雄位置位置
	void setHeroPosition(HeroPosition NowPosition);
	HeroImages getImages();							//获取英雄图像信息
	int getCost();									//获取价格
	float getMaxHp() const { return maxHp; }    //获取英雄最大血量
	float getRealHp() const { return realHp; }    //获取实时血量
	float getMaxMp() const { return maxMp; }    //获取英雄最大蓝量
	float getRealMp() const { return realMp; }    //获取实时蓝量
	float getHurtMp() const { return hurtMp; }    //获得受伤回蓝量
	int getRange() const { return range; }    //获取攻击距离
	float getFrequency() const { return frequency; }    //获取攻击频率
	float getAttackCounter() const { return attackCounter; }    //获取用于判断攻击的计数器
	void ChangeAttackCounter(float ATK) { attackCounter = ATK; }    //改变判断攻击的计数器
	Hero* getEnemy() const { return enemy; }    //获取正在攻击的敌人
	cocos2d::Sprite* getBody() const { return body; }    //获取英雄精灵
	static Hero* copy(Hero* templt);    //拷贝
	void ChangeRealHp(float a) { realHp = a; }    //改变实时血量
	void ChangeRealMp(float a) { realMp = a; }    //改变实时蓝量
	bool IsAttack() const { return isAttack; }    //判断是否在攻击
	bool IsMove() const { return isMove; }    //判断是否在移动
	bool IsDead() const { return isDead; }    //判断是否死亡
	bool IsDying() const { return isDying; }    //判断是否正在死亡
	void ChangeDead() { isDead = 0; }     //将死亡状态置为存活
	void ChooseEnemy(Hero* a) { enemy = a; }    //选择攻击的目标
	void ChangeFaceRight(bool Face1) { FaceRight = Face1; }   //改变朝向
	bool getFaceRight() { return FaceRight; }   //获取朝向
	CREATE_FUNC(Hero);
protected:
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成样例）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
	int cost;							//价格
	HeroPosition position;    //英雄战斗位置坐标（英雄进入战场后赋值）
	cocos2d::Layer* hero_space;    //棋子所在的空间层
	cocos2d::Sprite* body;    //棋子
	cocos2d::Sprite* hp_bar;    //血条框
	cocos2d::Sprite* hp;    //血条
	cocos2d::Sprite* mp_bar;    //蓝条框
	cocos2d::Sprite* mp;    //蓝条
	float maxHp;    //最大血量
	float realHp;    //实时血量
	float maxMp;    //最大蓝量
	float realMp;    //实时蓝量
	float attackMp;    //攻击回蓝量
	float hurtMp;    //受伤回蓝量
	int range;    //攻击距离
	int damage;    //攻击伤害
	float frequency;    //攻击频率
	float moveSpeed;    //移动速度
	bool isAttack = 0;    //判断是否在攻击（Heroes在场上只具有三种状态，攻击，移动，死亡）
	bool isMove = 0;    //判断是否在移动
	bool isDead = 0;    //判断是否死亡
	bool isDying = 0;    //判断是否正在死亡
	bool FaceRight = 1;   //判断面朝的方向是不是右边
	float attackCounter = 0;    //用于判断攻击的计数器
	Hero* enemy = nullptr;    //攻击的目标
	HeroType id;						//ID（种类标志）
};

//英雄图像信息
struct HeroImages
{
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成序列）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
};

class Golem :public Hero
	//坦克-Golem
{
public:
	bool init() override;
	void Attack() override;
	void Death() override;
	void Move(HeroPosition destination) override;
	CREATE_FUNC(Golem);
protected:
};
#endif // !HEROES_H
