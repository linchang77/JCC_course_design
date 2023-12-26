#pragma once

#ifndef GENERAL_CREATOR_H
#define GENERAL_CREATOR_H

#include "cocos2d.h"

//���ֽ�㼰���������һ��������
class GCreator
{
public:
	static GCreator* getInstance();						//��ȡ����

	//��������
	cocos2d::Sprite* createSprite(const std::string& image, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	//�����˵���
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	//������ǩ
	cocos2d::Label* createLabel(const std::string& text, const std::string& font, const float fontSize, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);	
	
	static void problemLoading(const std::string filename);	//���������Ϣ

private:
	cocos2d::Size visibleSize;	//��Ļ�ߴ�
	cocos2d::Vec2 origin;		//����ԭ��
};

#endif // !GENERAL_CREATOR_H
