#pragma once

#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 9		//ССӢ����ߵȼ�
#define NUM_HEROES 3	//Ӣ������
#define MAX_COST 5		//Ӣ�����۸�

//ССӢ��
class LittleHero : public cocos2d::Sprite
{
public:
	//������
	static LittleHero* getInstance();

	//���صȼ�
	int getGrade();

private:
	int grade;			//�ȼ�
};

struct HeroImages;

//Ӣ��
class Hero : public cocos2d::Node
{
public:
	virtual bool init();    //��ʼ��Ӣ��
	void setSpace(cocos2d::Layer* space)
	{
		hero_space = space;
	};
	void Appear_in_Preparation();    //��Ⱦ�������ڱ�սϯ
	bool initHp();    //��ʼ��Ѫ��
	void updateHp(float delta);    //Ѫ��ˢ��
	bool initMp();    //��ʼ������
	void updateMp(float delta);    //����ˢ��
	void Death();    //������������
	void Move();    //�����ƶ�
	void Attack();    //���ӹ���
	HeroImages getImages();							//��ȡӢ��ͼ����Ϣ
	int getCost();									//��ȡ�۸�
	static Hero* copy(Hero* templt);    //
	CREATE_FUNC(Hero);

private:
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ�������
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
	int cost;							//�۸�
	std::string name;					//����
	HeroPosition position;    //Ӣ��ս��λ������
	cocos2d::Layer* hero_space;    //�������ڵĿռ��
	cocos2d::Sprite* body;    //����
	cocos2d::Sprite* hp_bar;    //Ѫ����
	cocos2d::Sprite* hp;    //Ѫ��
	float maxhp;    //���Ѫ��
	float realhp;    //ʵʱѪ��
	float range;    //��������
	float frequency;    //����Ƶ��
	cocos2d::Sprite* mp_bar;    //������
	cocos2d::Sprite* mp;    //����
};

struct HeroPosition
	//Ӣ��ս��λ������
{
	int x;    //������
	int y;    //������
};



//Ӣ��ͼ����Ϣ
struct HeroImages
{
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ����У�
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
};

class Example :public Hero
	//��������Ӣ������
{
	virtual bool init() override;
};



#endif // !HEROES_H
