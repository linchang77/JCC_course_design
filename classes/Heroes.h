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
class Hero : public cocos2d::Sprite
{
public:
	HeroImages getImages();							//��ȡӢ��ͼ����Ϣ
	int getCost();									//��ȡ�۸�
	//�����������������������ʵ��


private:
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ�������
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
	int cost;							//�۸�
	std::string name;					//����
};

//Ӣ��ͼ����Ϣ
struct HeroImages
{
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ����У�
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
};

#endif // !HEROES_H
