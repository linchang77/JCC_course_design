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
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//小小英雄的回调函数
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void putchequer(Node* che, int x, int j);//将棋子放到第x列，y行
	Vec2 mapposition(int x, int y);//根据格子的坐标转换出锚点在map图层上的坐标
	static Vec2 getposition(int i, int j);//输入内部数组的坐标，返回世界坐标
private:
	Sprite* background;//地图背景
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();  //屏幕尺寸
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();     //坐标原点
};
#endif // !SETTING_H 
