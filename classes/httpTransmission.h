#pragma once

#ifndef HTTP_TRANSMISSION_H
#define HTTP_TRANSMISSION_H

#include "Littlehero.h"
#include "Room.h"
#include "Battlefield.h"
#include "network/HttpClient.h"
#include "curl/curl.h"

//����http���罻����
class httpTransmission
{
public:
	static httpTransmission* getInstance();

	//�������
	void joinRoom(Room* room);
	void seekRoom(Room* room);

	//���ͼ�����������
	void upload(Battlefield* battlefield);

	//��ȡ�Է���������
	void download(Battlefield* battlefield);

	//�����ı�
	void convert(std::string file);

private:
	//��Ӣ������ת��Ϊ�ı�
	std::string write(cocos2d::Vector<Hero*> herodata);
};

#endif // !HTTP_TRANSMISSION_H



