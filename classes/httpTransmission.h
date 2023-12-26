#pragma once

#ifndef HTTP_TRANSMISSION_H
#define HTTP_TRANSMISSION_H

#include "Littlehero.h"
#include "Battlefield.h"
#include "network/HttpClient.h"

//单例http网络交互类
class httpTransmission
{
public:
	static httpTransmission* getInstance();

	//发送己方棋子数据
	void upload(Battlefield* battlefield);

	//获取对方棋子数据
	void download(Battlefield* battlefield);

	//将字符串转化为英雄数据
	cocos2d::Vector<Hero*> stringToHeroData(std::string file);

private:
	//将英雄数据转化为字符串
	std::string heroDataToString(cocos2d::Vector<Hero*> herodata);
};

#endif // !HTTP_TRANSMISSION_H



