#pragma once
#ifndef LITTLEHERO_H
#define LITTLEHERO_H
#define FIGHT 1 //ս��״̬
#define PREPARE 0 //׼��״̬
#include "cocos2d.h"
#include "Heroes.h"
#define LHNUM 6
USING_NS_CC;
/****************************************************************************
���ƣ�ССӢ����
���ܣ���¼��ɫ�ں�̨�ĸ�����Ϣ,�Լ���ҵĸ��ֲ���
�����У����̵깺�����ӣ�����սϯ�������ƶ��������ϣ������飬ˢ���̵꣬�ƶ���սϯ�����ӵ�λ�á�
 ****************************************************************************/
class Littlehero : public cocos2d::Node
{
public:
	CREATE_FUNC(Littlehero);
	void deleteHp(int n) { Hp -= n; }//ССӢ�ۿ�Ѫ
	void pulltopreparation();
	virtual bool init();//��дinit����
    void init_layer();//��ʼ��ѡ��ͼ��
	void set_threelabel();//��ʾѪ��������͵ȼ��ı�ǩ
	void set_IDs();//��ʾ����ǵ�ID
	void set_HP_Bar();//��ʾѪ��
	void set_avatar();//��ʾͷ��
	cocos2d::Layer* get_heroslayer() { return heroslayer; }
	std::string ID = "";//ССӢ�۵�ID
private:
	int Hp = 100;//Ѫ��
	Label* Hplabel;//��ʾѪ���ı�ǩ
	int gold = 0;//���
	int level = 1;//�ȼ�
	Label* Levellabel;//��ʾ�ȼ��ı�ǩ
	int Exp = 0;//����
	Label* Explabel;//��ʾ����ı�ǩ
	int status = PREPARE;//ССӢ�۵�״̬
	Sprite avatar;//��ҵ�ͷ��
	Vector<Hero*> fightheros;//
 	Vector<Hero*> Preparation_Position[9];//��սϯ
	int chequers = 0;//��սϯ�����ӵ�����
	//void addche(Chequer * che);//������ӵ���սϯ
	cocos2d::Layer* heroslayer;//ѡ��ͼ��
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();  //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();     //����ԭ��
};
/****************************************************************************
���ƣ�ССӢ�ۿ�������
���ܣ�����ССӢ�ۣ���һ������
�����У���ȡССӢ��ָ�������
 ****************************************************************************/
class LHcontroler : public cocos2d::Ref
{
public:
	static int get_mynumber();//��ȡ���ССӢ����controler�����λ��
	friend Littlehero;
	static LHcontroler* getInstance();
	virtual bool init();
	Vector<Littlehero*> heros;

};
#endif // !SETTING_H 
