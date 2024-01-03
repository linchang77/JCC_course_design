#pragma once

#ifndef ROOM_H
#define ROOM_H

#include "cocos2d.h"
#include "network/HttpClient.h"

//�������
class Room : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//��������
	void poll(float dt);

	//������Ϸ�ص�
	void intoBattlefieldCallback(float dt);

	//���뷿��ص�
	void intoRoomCallback(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);

	//��ѯ�ص�
	void pollCallback(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);

	//ʵ��create����
	CREATE_FUNC(Room);

private:
	int mySeq;				//�ҷ����
	std::string room_num;	//�����
};

#endif // !ROOM_H
