#pragma once
#ifndef __CHEQUER_NODE_H__
#define __CHEQUER_NODE_H__

#define Hp_Bar 1    //Ѫ�����
#define Mp_Bar 2    //�������

#include "cocos2d.h"

class Chequer : public cocos2d::Node
    //�����࣬�̳�Node
{
public:
    virtual bool init();    //��ʼ������
    void setSpace(cocos2d::Layer* space)
    {
        chequer_space = space;
    };
    void Appear_in_Preparation();    //�ڱ�սϯ����
    bool initHp();    //��ʼ��Ѫ��
    void updateHp(float delta);    //Ѫ��ˢ��
    bool initMp();    //��ʼ������
    void updateMp(float delta);    //����ˢ��
    void Death();    //������������
    void Move();    //�����ƶ�
    void Attack();    //���ӹ���
    CREATE_FUNC(Chequer);
private:
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Layer* chequer_space;    //�������ڵĿռ��
    cocos2d::Sprite* chequer_body;    //����
    cocos2d::Sprite* hp_bar;    //Ѫ����
    cocos2d::Sprite* hp;    //Ѫ��
    float maxhp = 10;    //���Ѫ��
    float realhp = 10;    //ʵʱѪ��
    float range;    //��������
    float frequency;    //����Ƶ��
    cocos2d::Sprite* mp_bar;    //������
    cocos2d::Sprite* mp;    //����
};



class Mage :public Chequer
    //��ʦ�࣬�̳�Chequer
{

};

class Warrior :public Chequer
    //սʿ�࣬�̳�Chequer
{

};

class Tank :public Chequer
    //̹���࣬�̳�Chequer
{

};

class Assassin :public Chequer
    //�̿��࣬�̳�Chequer
{

};

#endif // __CHEQUER_NODE_H__