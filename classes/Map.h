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
名称：格子信息类
功能：存放格子上的各种信息
 ****************************************************************************/
class  PieceData
{
public:
	Vec2 position;//二维的位置
	//Hero* hero=NULL;//指向这个格子上英雄的指针
private:

};
/****************************************************************************
名称：地图类
功能：保存地图的各种信息
 ****************************************************************************/
class MapData : public cocos2d::Layer
{
public:
	//friend PieceData;//PieceData 是MapData的友元
	CREATE_FUNC(MapData);//创造一个MapData图层，计划是搞一个6x6的格子图
	//void onEnter();
	virtual bool init();//重写init函数
	PieceData plaids[6][6] ;//存储每个格子的信息
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//小小英雄的回调函数
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void putchequer(Node* che,int x,int j);//将棋子放到第x列，y行
	Vec2 mapposition(int x, int y);//根据格子的坐标转换出锚点在map图层上的坐标
private:
	Sprite* background;//地图背景
};



#endif // !SETTING_H 
