#pragma once

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "Heroes.h"
#include "Map.h"
#include "Littlehero.h"
#define SetitemPosition      cocos2d::Vec2(1600-50,925)
#define SetitemSize          cocos2d::Vec2(50,50)

//ģʽѡ��
enum Mode { Practice, Battle };

//����ͼ��
class Store;
class Board;
class Preparation;

//ͨ��ս����
class Battlefield : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//�˵��ص�
	void menuReturnCallback(cocos2d::Ref* pSender);
	void menuSetCallback(cocos2d::Ref* pSender);
	void menuStoreCallback(cocos2d::Ref* pSender);

	//http�ص�
	void preparationCallback(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);

	//��������ݽ���
	void dataExchange(float dt);

	//����ͼ��
	Store* getCurrentStore();
	Preparation* getCurrentPreparation();

	//ʵ��create����
	CREATE_FUNC(Battlefield);

private:
	Store* store = nullptr;															//�̵꣨�����ս����󶨣�
	Preparation* preparation = nullptr;												//��սϯ�������ս����󶨣�
	static float prepareDuration;
};

//�̵����
class Store : public cocos2d::Layer
{
public:
	virtual bool init();

	//��Ӣ�۳���ɾӢ��
	static bool addHero(Hero* newHero);
	static bool removeHero(Hero* toBeRemoved);

	//�����ʾӢ��
	static cocos2d::Vector<Hero*> randomDisplay();

	//���ص�ǰ����ָ���۸�������Ŀ
	static int countHeroByCost(const int cost);

	//��ȡ��ǰ���е�i��n�����ӵĿ���
	static Hero* getHeroByCost(const int cost, const int i);
	
	//�ص�
	void purchaseCallback(cocos2d::Ref* pSender);	//����ص�
	void refreshCallback(cocos2d::Ref* pSender);	//ˢ�»ص�

	//����/��ת�̵굱ǰ����״̬
	bool getStatus();
	void reverseStatus();

	//ʵ��create����
	CREATE_FUNC(Store);

private:
	static cocos2d::Vector<Hero*> pool;								//Ӣ�۳أ�Ӧ����������Ϸʱ�ͽ��г�ʼ���ģ�
	static const int size = 5;										//��Ʒ����
	cocos2d::Vector<Hero*> displayment;								//��ǰ�̵�����
	constexpr static int possibilityTable[MAX_GRADE][MAX_COST] = {	//���ʱ�
		{100, 0, 0, 0, 0},
		{75, 25, 0, 0, 0},
		{55, 30, 15, 0, 0},
		{45, 33, 20, 2, 0},
		{30, 40, 25, 5, 0},
		{19, 35, 35, 10, 1},
		{18, 25, 36, 18, 3},
		{10, 20, 25, 35, 10},
		{5, 10, 20, 40, 25}
	};
	bool on = false;				//�̵굱ǰ����״̬
	cocos2d::Sprite* background;	//����
	cocos2d::Menu* menu;			//�˵�
	cocos2d::Menu* refresh;			//ˢ�°�ť
};

//��սϯ
class Preparation
{
public:
	static Preparation* create();
	void placeHero(Hero* hero);
	bool is_full();

private:
	const int size = 9;																									//��սϯ�ߴ�
	const cocos2d::Vec2 startingPoint = { 340.0f, cocos2d::Director::getInstance()->getVisibleSize().height - 684.0f};	//�����ϯλê��
	const float seatWidth = 104.0f;																						//ϯλ���
};

#endif // !BATTLEFIELD_H
