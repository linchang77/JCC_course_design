#pragma once

#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 6		//ССӢ����ߵȼ�
#define NUM_HEROES 3	//Ӣ������
#define MAX_COST 3		//Ӣ�����۸�
#define Hp_Bar 1    //Ѫ�����
#define Mp_Bar 2    //�������

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
struct HeroPosition;

//Ӣ��
class Hero : public cocos2d::Node
{
public:
	virtual bool init();    //��ʼ��Ӣ��
	void setSpace(cocos2d::Layer* space)
	{
		hero_space = space;
	};
	bool initHp();    //��ʼ��Ѫ��
	void updateHp(float delta);    //Ѫ��ˢ��
	bool initMp();    //��ʼ������
	void updateMp(float delta);    //����ˢ��
	void Death();    //������������
	void Move(HeroPosition destination);    //�����ƶ��������ƶ��յ㣬���Ӵӵ�ǰλ���ƶ����յ㣬��������λ�ø���Ϊ�յ�λ��
	virtual void Attack(Example* enemy);    //���ӹ�������
	HeroPosition getPosition();    //��ȡӢ��λ��λ��
	HeroImages getImages();							//��ȡӢ��ͼ����Ϣ
	int getCost();									//��ȡ�۸�
	static Hero* copy(Hero* templt);    //
	CREATE_FUNC(Hero);

protected:
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ�������
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
	int cost;							//�۸�
	std::string name;					//����
	HeroPosition position;    //Ӣ��ս��λ�����꣨Ӣ�۽���ս����ֵ��
	cocos2d::Layer* hero_space;    //�������ڵĿռ��
	cocos2d::Sprite* body;    //����
	cocos2d::Sprite* hp_bar;    //Ѫ����
	cocos2d::Sprite* hp;    //Ѫ��
	cocos2d::Sprite* mp_bar;    //������
	cocos2d::Sprite* mp;    //����
	float maxhp;    //���Ѫ��
	float realhp;    //ʵʱѪ��
	float maxmp;    //�������
	float realmp;    //ʵʱ����
	float range;    //��������
	float frequency;    //����Ƶ��
	float movespeed;    //�ƶ��ٶ�
	bool ismove;    //�ж��Ƿ����ƶ�
	bool isdead;    //�ж��Ƿ�����������Death�������ж�Ϊ������дս������Ҫ��һ��ս������������Ӣ����ֵ�ظ������������Ϊfalse��
	int counter = 0;    //������
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
public:
	virtual bool init() override;
	virtual void Attack(Example* enemy) override;
protected:
	cocos2d::Sprite* bullet;    //�����ӵ����ٶ�����Ϊ���֣�
};



#endif // !HEROES_H
