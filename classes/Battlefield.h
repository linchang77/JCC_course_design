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

<<<<<<< HEAD
	//�˵���ť��������
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
=======
	//�˵���������
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, float x, float y);
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2

private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();    //����ԭ��
	cocos2d::Menu* store = nullptr;													//�̵꣨�����ս����󶨣�
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
<<<<<<< HEAD
	Mode mode;
=======
	static Mode mode;
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
	cocos2d::Scene* scene;
};

//�̵����
class Store : public cocos2d::Menu
{
public:
	//�����ʾӢ��
	void randomDisplay();

	//ʵ��create����
	CREATE_FUNC(Store);

private:
	//Ӣ�۳�
<<<<<<< HEAD
	cocos2d::Vector<Hero*> pool;
=======
	cocos2d::Vector<Hero> pool;
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
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
<<<<<<< HEAD
	const int size = 9;								//��սϯ�ߴ�
=======
	int size;										//��սϯ�ߴ�
	const int MaxSize = 9;							//��սϯ���ߴ�
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
};

#endif // !BATTLEFIELD_H
