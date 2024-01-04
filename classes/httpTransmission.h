#pragma once

#ifndef HTTP_TRANSMISSION_H
#define HTTP_TRANSMISSION_H

#include "Littlehero.h"
#include "Room.h"
#include "Battlefield.h"
#include "network/HttpClient.h"
#include "curl/curl.h"

//单例http网络交互类
class httpTransmission
{
public:
	static httpTransmission* getInstance();

	//房间相关
	void joinRoom(Room* room);
	void seekRoom(Room* room);

	//发送己方棋子数据
	void upload(Battlefield* battlefield);

	//获取对方棋子数据
	void download(Battlefield* battlefield);

	//处理文本
	void convert(std::string file);

private:
	//将英雄数据转化为文本
	std::string write(cocos2d::Vector<Hero*> herodata);
};

#endif // !HTTP_TRANSMISSION_H



