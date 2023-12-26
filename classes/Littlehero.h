#pragma once
#ifndef LITTLEHERO_H
#define LITTLEHERO_H
#define FIGHT 1 //ս��״̬
#define PREPARE 0 //׼��״̬
#include "cocos2d.h"
#include "Heroes.h"
#include "Map.h"
#define LHNUM 6
/*����ͼƬ�ĳߴ�*/
#define BuyexpButtonSize cocos2d::Vec2(211, 77)
#define RefreshButtonSize cocos2d::Vec2(211, 77)
/*���ֱ�ǩ��λ��*/           
#define GoldLabelPosition cocos2d::Vec2(694,209)
#define PopulationLabelPosition cocos2d::Vec2(755,948-252)
#define MESSAGELABEL  cocos2d::Vec2(755,948-145)
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
	/*��ʼ������*/
	CREATE_FUNC(Littlehero);
	virtual bool init();//��дinit����
	void init_layer();//��ʼ��ѡ��ͼ��
	void init_MyMap();//��ʼ����ͼͼ��
	void set_threelabel();//����Ѫ��������͵ȼ��ı�ǩ
	void set_ExpButton();//���ù�����İ�ť
	void set_Gold();   //���ý�ұ�ǩ,��ͼ��
	void set_Messagelabel();//������Ϣ��ǩ
	void set_PopulationLabel();//�����˿ڵ�ͼ��
	void set_Shop();//�����̵�
	void set_HP_Bar();//��ʾѪ��
	void add_Littlehero();//����ССӢ��
	/*
	*ССӢ�۵�Ѫ����غ���
	*/
	void deleteHp(int n) { Hp -= n; }//ССӢ�ۿ�Ѫ
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
	void showInterest();//��ʾ��Ϣͼ��
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
	*���ڲ���Ա�Ĳ�������
	*/
	Vector<Hero*> getEnemyFightingHeroes() { return Enemy_fightheros; }
	void setEnemyHp(int Hp) { EnemyHp = Hp; }
	void setEnemyFightingHeroes(Vector<Hero*> vec) { Enemy_fightheros = vec; }
	cocos2d::Layer* get_heroslayer() { return heroslayer; }
	std::string ID = "";//ССӢ�۵�ID
	int getHp() { return Hp; }
	int getLevel() { return Level; }
	int getEnemyHp() { return EnemyHp; }
	MapData* get_MyMap() { return My_Map; }
	void set_message(std::string str) { Messagelabel->setString(str); }
	/*���ڵ�ͼ�ĺ���*/
	Vec2 getmidposition(int x, int y);//�����������귵�ظ����е�����
	Vec2 getmidposition(Vec2 location);//����һ����ά���������ؾ��������ά��������ĸ����е�����
	Vec2 getmidposition(int x);//��������꣬��ȡ��սϯ�ϸ����е������

	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y,
		                                   const float anchorX = 0.5f, const float anchorY = 0.5f, const float contentsizex = 1600);
	cocos2d::Sprite* createSprite(const std::string& SpriteImage,const float x, const float y, const float anchorX = 0, 
		                          const float anchorY = 0,const float contentsizex= 1600, const float contentsizey=948 );
	
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
	            Label* Goldlabel;//���������ǩ
				
	/*״̬*****/int status = PREPARE;//ССӢ�۵�״̬
	            int VICTORY = 0;//��¼���ܻ�����ʤ����
				bool isDragging;//��¼�Ƿ����϶�ͼƬ
	/*ͼ����***/Sprite* YourLittleHreo;//ССӢ��
	            Sprite* Movinghero;//�����ƶ���Ӣ��
	            Sprite* Goldimage;//���ͼ��
	            Sprite* Population;//�˿�ͼ��
	            Sprite* avatarimage;//ͷ��ͼ��
				Sprite* Shopbackground;//�̵걳��
	            
	/*ս����***/Vector<Hero*> Preparation_Position[9];//��սϯ
	            int chequers = 0;//��սϯ�����ӵ�����
				Vec2 Lastposition;
				Hero* Map[8][4];//��ͼ�ϵ�����λ��
				float MapSizeX[9] = { 382,  490.125 ,  598.25 ,  706.375, 814.5  ,922.625  , 1030.75  , 1138.875   , 1247 };
				float MapSizeY[5] = {315,426.75,538.5,650.25,762 };
				float PreparationsSizeX[10] = { 279   ,386.88  ,  494.76  ,  602.64  , 710.52  , 818.4    ,926.28 ,   1034.16  ,  1142.04 , 1249.92 };
				float PreparationsSizeY[2] = { 215,315 };
				Vector<Hero*> Enemy_fightheros;//�з���������
	/*��Ϣ��ʾ��*/Label* Messagelabel;//��ʾ��ǩ

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
