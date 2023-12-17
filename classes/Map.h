#pragma once

#ifndef MAP_H
#define MAP_H

#include "cocos2d.h"
USING_NS_CC;
#define Enemy -1
#define Empty 0
#define ME    1
class MapData;
class PieceData;
/****************************************************************************
���ƣ�������Ϣ��
���ܣ���Ÿ����ϵĸ�����Ϣ
 ****************************************************************************/
class  PieceData
{
public:
	Vec2 position;//��ά��λ��
	//Hero* hero=NULL;//ָ�����������Ӣ�۵�ָ��
private:

};
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
	PieceData plaids[6][6] ;//�洢ÿ�����ӵ���Ϣ
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//ССӢ�۵Ļص�����
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void putchequer(Node* che,int x,int j);//�����ӷŵ���x�У�y��
	Vec2 mapposition(int x, int y);//���ݸ��ӵ�����ת����ê����mapͼ���ϵ�����
private:
	Sprite* background;//��ͼ����
};



#endif // !SETTING_H 
