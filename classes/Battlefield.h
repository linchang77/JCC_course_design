#pragma once

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "cocos2d.h"
#include "Heroes.h"
#include "Map.h"
#include "Littlehero.h"

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

	//����ͼ��
	Store* getCurrentStore();
	Preparation* getCurrentPreparation();

	//ʵ��create����
	CREATE_FUNC(Battlefield);

	//�˵���ť��������
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);

private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();    //����ԭ��
	Store* store = nullptr;															//�̵꣨�����ս����󶨣�
	Preparation* preparation = nullptr;												//��սϯ�������ս����󶨣�
};

//ģʽѡ������������ս���������
class ModeSelector
{
public:
	//ģʽѡ�����ǵ�����
	static ModeSelector* getInstance();
	bool setMode(const Mode mode, cocos2d::Scene* scene);
	Mode getMode(); 

private:
	Mode mode;
	cocos2d::Scene* scene;
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
	
	//����ص�
	void purchaseCallback(cocos2d::Ref* pSender);	//���ֻ���������ƣ����������������������ʵ��

	//����/��ת�̵굱ǰ����״̬
	bool getStatus();
	void reverseStatus();

	//ʵ��create����
	CREATE_FUNC(Store);

	//�˵���ť��������
	static cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);

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
	bool on = false;	//�̵굱ǰ����״̬
	cocos2d::Menu* menu;	//����
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();    //����ԭ��
};

//����
class Board : public cocos2d::Layer
{
public:
	virtual bool init();

	//ʵ��create����
	CREATE_FUNC(Board);

private:

};

//��սϯ
class Preparation : public cocos2d::Layer
{
public:
	virtual bool init();

	void placeHero(Hero* hero);

	//ʵ��create����
	CREATE_FUNC(Preparation);

private:
	const std::string seat = "preparationSeat.png";	//����ϯλͼƬ
	const int size = 9;								//��սϯ�ߴ�
	int occupied = 0;								//��ռ��ϯλ��
};

#endif // !BATTLEFIELD_H
