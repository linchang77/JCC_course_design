#pragma once

#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 9		//ССӢ����ߵȼ�
#define NUM_HEROES 3	//Ӣ������
#define MAX_COST 5		//Ӣ�����۸�

//ССӢ��
class LittleHero
{
public:
	//������
	static LittleHero* getInstance();

	//���ؾ���
	cocos2d::Sprite* getSprite();

	//���صȼ�
	int getGrade();

private:
	cocos2d::Sprite* body;		//����ָ��
	int grade;					//�ȼ�
};

struct HeroImages;

//Ӣ��
class Hero : public cocos2d::Node
{
public:
	virtual bool init();				//��ʼ��
	HeroImages getImages();				//��ȡӢ��ͼ����Ϣ
	int getCost();						//��ȡ�۸�
	virtual void getSpriteReady();		//���ɾ���
	static Hero* copy(Hero* templt);	//����
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
