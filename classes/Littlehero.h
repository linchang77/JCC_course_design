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
	friend class httpTransmission;
	CREATE_FUNC(Littlehero);
	void deleteHp(int n) { Hp -= n; }//ССӢ�ۿ�Ѫ
	void pulltopreparation();
	virtual bool init();//��дinit����
    void init_layer();//��ʼ��ѡ��ͼ��
	void set_threelabel();//��ʾѪ��������͵ȼ��ı�ǩ
	void set_IDs();//��ʾ����ǵ�ID
	void set_HP_Bar();//��ʾѪ��
	void set_avatar();//��ʾͷ��
	void update_Hp(int hp);//����Ѫ��
	void update_exp(int exp);//���¾���ֵ
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, 
		                                   const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	cocos2d::Layer* get_heroslayer() { return heroslayer; }
	Vector<Hero*>* get_E_F() { return &Enemy_fightheros; }
	std::string ID = "";//ССӢ�۵�ID
	int getLevel() { return level; }
	int getHp() { return Hp; }
	void setEnemyHp(int Hp) { EnemyHp = Hp; }
private:
	int Explevel[6] = {};//����������¼ÿ���ȼ��ľ���ֵ
	int Hp = 100;//Ѫ��
	int EnemyHp;//�з�Ѫ��
	Label* Hplabel;//��ʾѪ���ı�ǩ
	int gold = 0;//���
	int level = 1;//�ȼ�
	Label* Levellabel;//��ʾ�ȼ��ı�ǩ
	int Exp = 0;//����
	Label* Explabel;//��ʾ����ı�ǩ
	int status = PREPARE;//ССӢ�۵�״̬
	Sprite avatar;//��ҵ�ͷ��
 	Vector<Hero*> Preparation_Position[9];//��սϯ
	int chequers = 0;//��սϯ�����ӵ�����
	Vector<Hero*> Enemy_fightheros;//�з�����
	//void addche(Chequer * che);//������ӵ���սϯ
	cocos2d::Layer* heroslayer;//ѡ��ͼ��
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();  //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();     //����ԭ��
	/*
	*��Ҫ�ϴ�������
	*/
	Vector<Hero*> fightheros;//���϶�ս������
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
