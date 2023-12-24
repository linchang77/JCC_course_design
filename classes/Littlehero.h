#pragma once
#ifndef LITTLEHERO_H
#define LITTLEHERO_H
#define FIGHT 1 //ս��״̬
#define PREPARE 0 //׼��״̬
#include "cocos2d.h"
#include "Heroes.h"
#include "Map.h"
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
	/*��ʼ������*/
	CREATE_FUNC(Littlehero);
	virtual bool init();//��дinit����
	void init_layer();//��ʼ��ѡ��ͼ��
	void init_MyMap();//��ʼ����ͼͼ��
	void set_threelabel();//��ʾѪ��������͵ȼ��ı�ǩ
	/*
	*ССӢ�۵�Ѫ����غ���
	*/
	void deleteHp(int n) { Hp -= n; }//ССӢ�ۿ�Ѫ
	void set_HP_Bar();//��ʾѪ��
	void update_Hp(int hp);//����Ѫ��
	/*
	*ССӢ�۵ľ�����غ���
	*/
	void Buy_exp();//������ֵ
	void Update_exp(int exp);//���¾���ֵ
	void Checklevel();//�ж��Ƿ�Ҫ����
	/*
     *ССӢ�۵Ľ����غ���
     */
	void update_gold();//ÿ�غϸ��½��
	void update_gold(int num);//���½��
	/*
	*ССӢ�۵�IDͷ����غ���
	*/
	void set_IDs();//��ʾ����ǵ�ID
	void set_avatar();//��ʾͷ��
	/*
	*ССӢ���ڱ�ս�׶εĲ�������
	*/
	/*�϶�����*/
	void initMouseListeners();//��ʼ�����������
	bool onLeftMouseDown(EventMouse* event);
	void onLeftMouseMove(EventMouse* event);
	void onLeftMouseUp(EventMouse* event);
	bool onRightMouseDown(EventMouse* event);

	void addhero(Hero * hero);//������ӵ���սϯ
	/*
	*��ȡ���ڲ���Ա�ĺ���
	*/
	Vector<Hero*> GetEnemyFightingHeroes() {	return Enemy_fightheros;}
	void setEnemyFightingHeroes(Vector<Hero*> vec) { Enemy_fightheros = vec; }
	cocos2d::Layer* get_heroslayer() { return heroslayer; }
	MapData* get_MyMap() { return My_Map; }
	int getHp() { return Hp; }

	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, 
		                                   const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	std::string ID = "";//ССӢ�۵�ID
private:
	/*ССӢ������*/
	/*ID*******/  
	/*�ȼ�����*/int Explevel[LHNUM] = { 0,2,6,8,20,30 };//����������¼ÿ���ȼ��ľ���ֵ
	            int Level = 1;//�ȼ�
				Label* Levellabel;//��ʾ�ȼ��ı�ǩ
				int Exp = 0;//����
				Label* Explabel;//��ʾ����ı�ǩ
	/*Ѫ��*****/int Hp = 100;//Ѫ��
	            Label* Hplabel;//��ʾѪ���ı�ǩ
				int EnemyHp;
	/*���*****/int Gold = 0;//���
	            Label* Goldlabel;
	/*״̬*****/int status = PREPARE;//ССӢ�۵�״̬
	            int VICTORY = 0;//��¼���ܻ�����ʤ����
				bool isDragging;//��¼�Ƿ����϶�ͼƬ
	/*ͼ����***/Sprite *avatar;//��ҵ�ͷ��
	            Sprite* YourLittleHreo;//ССӢ��
				Sprite* Movinghero;//�����ƶ���Ӣ��
	/*ս����***/Vector<Hero*> Preparation_Position[9];//��սϯ
	            int chequers = 0;//��սϯ�����ӵ�����
				Hero* Map[6][6];//��ͼ�ϵ�����λ��
				Vector<Hero*> Enemy_fightheros;//�з���������


	cocos2d::Layer* heroslayer;//ѡ��ͼ��
	MapData* My_Map;//��Mapͼ����ССӢ���������ʼ��
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();  //��Ļ�ߴ�
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();     //����ԭ��
	/*
	*��Ҫ�ϴ�������
	*/
	Vector<Hero*> fightheros;//�ҷ����϶�ս������
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
