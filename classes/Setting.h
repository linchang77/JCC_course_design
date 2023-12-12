#pragma once

#ifndef SETTING_H
#define SETTING_H

#include "cocos2d.h"

class Setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//�˵��ص�
	void menuReturnCallback(cocos2d::Ref* pSender);
	void musicSwitchCallback(cocos2d::Ref* pSender);

	//ʵ��create����
	CREATE_FUNC(Setting);

	//�˵���ť��������
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	//��ǩ��������
	cocos2d::Label* createLabel(const std::string& text, const std::string& font, const float fontSize, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	//���鴴������
	cocos2d::Sprite* createSprite(const std::string& image, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);

private:
	//Scene* self;																	//����
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();    //����ԭ��

	//������
	bool music = true;
	
};

#endif // !SETTING_H 
