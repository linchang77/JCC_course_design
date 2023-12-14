#pragma once

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "cocos2d.h"
#include "Heroes.h"

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

	//ʵ��create����
	CREATE_FUNC(Battlefield);

	//�˵���ť��������
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);

private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();    //����ԭ��
	cocos2d::Layer* store = nullptr;												//�̵꣨�����ս����󶨣�
	cocos2d::Layer* preparation = nullptr;											//��սϯ�������ս����󶨣�
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
	static cocos2d::Layer* createLayer();

	virtual bool init();

	//�����ʾӢ��
	static cocos2d::Vector<Hero*> randomDisplay();

	//����ص�
	void purchaseCallback(cocos2d::Ref* pSender);	//���ֻ���������ƣ����������������������ʵ��

	//ʵ��create����
	CREATE_FUNC(Store);

	//�˵���ť��������
	static cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);

private:
	static cocos2d::Vector<Hero*> pool[MAX_COST];			//Ӣ�۳�
	static const int size = 5;								//��Ʒ����
	cocos2d::Vector<Hero*> displayment;						//��ǰ�̵�����
	static const int possibilityTable[MAX_GRADE][MAX_COST];	//���ʱ�
};

//����
class Board : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	//ʵ��create����
	CREATE_FUNC(Board);

private:

};

//��սϯ
class Preparation : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	//ʵ��create����
	CREATE_FUNC(Preparation);

private:
	const std::string seat = "preparationSeat.png";	//����ϯλͼƬ
	const int size = 9;								//��սϯ�ߴ�
};

#endif // !BATTLEFIELD_H
