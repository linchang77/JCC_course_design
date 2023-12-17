#pragma once

#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 9		//ССӢ����ߵȼ�
#define NUM_HEROES 3	//Ӣ������
#define MAX_COST 5		//Ӣ�����۸�

//ССӢ��
class LittleHero : public cocos2d::Node
{
public:
	//������
	static LittleHero* getInstance();

	//���صȼ�
	int getGrade() const;

	CREATE_FUNC(LittleHero);

private:
	cocos2d::Sprite* body;		//����ָ��
	int grade;					//�ȼ�
};

struct HeroImages;

//Ӣ��
class Hero : public cocos2d::Node
{
public:
	HeroImages getImages() const;		//��ȡӢ��ͼ����Ϣ
	int getCost() const;				//��ȡ�۸�
	//�����������������������ʵ��

	CREATE_FUNC(Hero);

protected:
	cocos2d::Sprite* body;				//����ָ��
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ�Vector��
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
	int cost;							//�۸�
	std::string name;					//����
};

//��������Ӣ������
class Example : public Hero
{
public:
	virtual bool init();

	CREATE_FUNC(Example);
};

//Ӣ��ͼ����Ϣ
struct HeroImages
{
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ����У�
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
};

#endif // !HEROES_H
