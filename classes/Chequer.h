#pragma once
#ifndef __CHEQUER_NODE_H__
#define __CHEQUER_NODE_H__

#define Hp_Bar 1    //血条标记
#define Mp_Bar 2    //蓝条标记

#include "cocos2d.h"

class Chequer : public cocos2d::Node
    //棋子类，继承Node
{
public:
    virtual bool init();    //初始化棋子
    void setSpace(cocos2d::Layer* space)
    {
        chequer_space = space;
    };
    void Appear_in_Preparation();    //在备战席出现
    bool initHp();    //初始化血条
    void updateHp(float delta);    //血条刷新
    bool initMp();    //初始化蓝条
    void updateMp(float delta);    //蓝条刷新
    void Death();    //死亡淡出动画
    void Move();    //棋子移动
    void Attack();    //棋子攻击
    CREATE_FUNC(Chequer);
private:
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Layer* chequer_space;    //棋子所在的空间层
    cocos2d::Sprite* chequer_body;    //棋子
    cocos2d::Sprite* hp_bar;    //血条框
    cocos2d::Sprite* hp;    //血条
    float maxhp = 10;    //最大血量
    float realhp = 10;    //实时血量
    float range;    //攻击距离
    float frequency;    //攻击频率
    cocos2d::Sprite* mp_bar;    //蓝条框
    cocos2d::Sprite* mp;    //蓝条
};



class Mage :public Chequer
    //法师类，继承Chequer
{

};

class Warrior :public Chequer
    //战士类，继承Chequer
{

};

class Tank :public Chequer
    //坦克类，继承Chequer
{

};

class Assassin :public Chequer
    //刺客类，继承Chequer
{

};

#endif // __CHEQUER_NODE_H__