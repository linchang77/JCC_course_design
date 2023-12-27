#pragma once

#ifndef HTTP_TRANSMISSION_H
#define HTTP_TRANSMISSION_H

#include "Littlehero.h"
#include "Battlefield.h"
#include "network/HttpClient.h"

//����http���罻����
class httpTransmission
{
public:
	static httpTransmission* getInstance();

	//���ͼ�����������
	void upload(Battlefield* battlefield);

	//��ȡ�Է���������
	void download(Battlefield* battlefield);

	//���ַ���ת��ΪӢ������
	cocos2d::Vector<Hero*> stringToHeroData(std::string file);

private:
	//��Ӣ������ת��Ϊ�ַ���
	std::string heroDataToString(cocos2d::Vector<Hero*> herodata);
};

#endif // !HTTP_TRANSMISSION_H



