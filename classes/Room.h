#pragma once

#ifndef ROOM_H
#define ROOM_H

#include "cocos2d.h"
#include "network/HttpClient.h"

//房间界面
class Room : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//调度器绑定
	void poll(float dt);

	//进入游戏回调
	void intoBattlefieldCallback(float dt);

	//进入房间回调
	void intoRoomCallback(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);

	//轮询回调
	void pollCallback(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);

	//实现create方法
	CREATE_FUNC(Room);

private:
	int mySeq;				//我方序号
	std::string room_num;	//房间号
};

#endif // !ROOM_H
