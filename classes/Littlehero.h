#pragma once

#ifndef LITTLEHERO_H
#define LITTLEHERO_H

#include "cocos2d.h"
USING_NS_CC;
/****************************************************************************
���ƣ�ССӢ����
���ܣ���¼��ɫ�ں�̨�ĸ�����Ϣ
 ****************************************************************************/
class Littlehero : public cocos2d::Layer
{
public:
	void deleteHp(int n) { Hp -= n; }//ССӢ�ۿ�Ѫ

private:
	int Hp = 100;//Ѫ��
	Vector<Node*> Preparation_Position[9];//��սϯ
	int chequers = 0;//��սϯ�����ӵ�����
	//void addche(Chequer * che);//������ӵ���սϯ

};

#endif // !SETTING_H 
