#pragma once

#ifndef MAP_H
#define MAP_H

#include "cocos2d.h"
#include "Heroes.h"
USING_NS_CC;
#define Enemy -1
#define Empty 0
#define ME    1
class MapData;
class PieceData;
/****************************************************************************
���ƣ���ͼ��
���ܣ������ͼ�ĸ�����Ϣ
 ****************************************************************************/
class MapData : public cocos2d::Layer
{
public:
	//friend PieceData;//PieceData ��MapData����Ԫ
	CREATE_FUNC(MapData);//����һ��MapDataͼ�㣬�ƻ��Ǹ�һ��6x6�ĸ���ͼ
	//void onEnter();
	virtual bool init();//��дinit����
	void putchequer(Node* che, int x, int j);//�����ӷŵ���x�У�y��
	Vec2 mapposition(int x, int y);//���ݸ��ӵ�����ת����ê����mapͼ���ϵ�����
	void setmaplines(int n) { Mapline->setOpacity(n); }//���õ�ͼ���ӵ�͸����
	static Vec2 getposition(int i, int j);//�����ڲ���������꣬������������
private:
	Sprite* Background;//��ͼ����
	Sprite* Mapline;
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();  //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();     //����ԭ��
};
#endif // !SETTING_H 
