#pragma once
#ifndef LITTLEHERO_H
#define LITTLEHERO_H
#define FIGHT 1 //ս��״̬
#define PREPARE 0 //׼��״̬
#include "cocos2d.h"
#include "Heroes.h"
#include "Map.h"
#include"Hextech.h"
#define ONLINENUM   2   //����ģʽ��ССӢ������
#define M_LEVEL 5    //���ȼ�
#define Winning_Streak_Rewards 1//��ʤ�������ܽ���
#define Gold_Per_Turn  5//ÿ�غϹ̶����
/*ƥ��ģʽ*/
#define ONLINE 1
#define LOCAL  2
/*����ͼƬ�ĳߴ�*/
#define BuyexpButtonSize cocos2d::Vec2(211, 77)
#define RefreshButtonSize cocos2d::Vec2(211, 77)
#define CloseitemSize        cocos2d::Vec2(50,50)
/*���ֱ�ǩ��ͼƬ��λ��*/
#define GoldLabelPosition cocos2d::Vec2(694,209)
#define PopulationLabelPosition cocos2d::Vec2(755,948-252)
#define MESSAGELABEL  cocos2d::Vec2(755,948-145)
<<<<<<< HEAD
#define EnditemPosition    cocos2d::Vec2(775,300)
#define DefeatPosition       cocos2d::Vec2(800,474)
/*�Ÿ�Ӣ�۵ĺ궨��*/

#define MONEY 1
#define CLEARMIND 2
#define POPULATION 3

=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
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
	friend class LHcontroler;
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
	void set_HP_Bar();//��ʾѪ��
	void add_Littlehero();//����ССӢ��
	/*
	*ССӢ�۵�Ѫ����غ���
	*/
	void deleteHp(int n) { Hp -= n; }//ССӢ�ۿ�Ѫ
	void update_Hp(int hp=0);//����Ѫ��
	void setEnemyHp(int enemyHp) { this->enemyHp = enemyHp; }
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
	int get_gold() { return Gold; }	//��ȡ�����
	void showInterest();//��ʾ��Ϣͼ��
	void update_WinOrLose(int Win,int Lose);
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
	void addhero(Hero* hero, int x) { Preparation[x - 1] = hero; }//������ӵ���սϯ
	void addhero(Hero* hero) {};//������ӵ�ս������
<<<<<<< HEAD
	void remove(Hero* hero) { hero->removeFromParent(); }//ɾ���������
	/*����˹�йصĺ���*/
	bool is_ClearMind();
=======
	void remove(Hero* hero){ hero->removeFromParent(); }//ɾ���������
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	/*
	*���ڲ���Ա�Ĳ�������
	*/
	Vector<Hero*> getEnemyFightingHeroes() { return Enemy_fightheros; }
	void setEnemyFightingHeroes(Vector<Hero*> vec) { Enemy_fightheros = vec; }
	cocos2d::Layer* get_heroslayer() { return heroslayer; }
<<<<<<< HEAD

	int getHp() { return Hp; }
	int getEnemyHp() { return enemyHp; }
	int getLevel() { return Level; }
=======
	std::string ID = "";//ССӢ�۵�ID
	int getHp() { return Hp; }
	int getLevel() { return Level; }
	int getEnemyHp() { return EnemyHp; }
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	int getNum() { return Num; }
	int getEnemyNum() { return EnemyNum; }
	void chooseEnemyNum(int Enemy_Num) { EnemyNum = Enemy_Num; }
	int getLastEnemyNum() { return LastEnemyNum; }
	bool getIsAI() { return IsAI; }
<<<<<<< HEAD
	void setHextechStatus(int status) { HextechStatus = status; }
	int getHextechStatus() { return HextechStatus; }
	/*����˹��*/
	int HextechStatus;//��ǰӢ�۵ĺ���˹״̬

	void changeHps(int change, int HpsTochange) { Hps[HpsTochange] = Hps[HpsTochange] - change > 0 ? Hps[HpsTochange] - change : 0; }
	int getHps(int which) { return Hps[which]; }
	MapData* get_MyMap() { return My_Map; }
	void set_message(std::string str) { Messagelabel->setString(str); }
	std::string getID() { return ID; }
	void setID(std::string ID) { this->ID = ID; }
	void setRoomParam(int seq, std::string room_num) { this->seq = seq, this->room_num = room_num; }
=======
	MapData* get_MyMap() { return My_Map; }
	void set_message(std::string str) { Messagelabel->setString(str); }
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	/*���ڵ�ͼ�ĺ���*/
	Vec2 getmidposition(int x, int y);//�����������귵�ظ����е�����
	Vec2 getmidposition(Vec2 location);//����һ����ά���������ؾ��������ά��������ĸ����е�����
	Vec2 getmidposition(int x);//��������꣬��ȡ��սϯ�ϸ����е������
	Vec2 getFightarrayposition(Vec2 location);//�������귵�ط��ؾ��������ά���������ս����������
	int getPreparationarrayposition(Vec2 location);//�����������귵�ط��ؾ��������ά��������ı�սϯ��������
	/*ս����***/Hero* Preparation[9] = { nullptr,nullptr,nullptr ,nullptr,nullptr,nullptr,nullptr ,nullptr,nullptr };//��սϯ
	Hero* Fightfield[4][4] = { {nullptr,nullptr,nullptr ,nullptr},{nullptr,nullptr,nullptr ,nullptr },
							   {nullptr,nullptr,nullptr ,nullptr},{nullptr,nullptr,nullptr ,nullptr } };//ս���ϵ����ӷֲ�
<<<<<<< HEAD
	int HerosType[18] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//��¼��������
	/*���Ǻ���*/
	bool FindUpgradeHero(Hero* &hero1, Hero* &hero2, Hero* &hero3);//�ҵ��������ǵ�Ӣ����
	void CheckUpgrade(Hero* hero);
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
private:
	/*ССӢ������*/
	/*ID*******/
	std::string ID = "";//ССӢ�۵�ID
	int seq;
	std::string room_num;
	/*�ȼ�����*/int Explevel[M_LEVEL] = { 0,4,10,18,30};//����������¼ÿ���ȼ��ľ���ֵ
	int Level = 1;//�ȼ�
	Label* Levellabel;//��ʾ�ȼ��ı�ǩ
	int Exp = 0;//����
	Label* Explabel;//��ʾ����ı�ǩ
	Label* PopulationLabel;//�˿ڵı�ǩ
	int MaxPeople = 5; 

	/*Ѫ��*****/int Hps[4] = { 100,100,100,100 };//Ѫ��
	int Hp = 100;
	int enemyHp = 100;
	Label* Hplabel;//��ʾѪ���ı�ǩ
	Sprite* Hpbar[4];//�ĸ�Ѫ��
	Sprite* Hpframe;//Ѫ����

	/*���*****/int Gold = 15;//���
	Label* Goldlabel;//���������ǩ
	const int WinOrLoseReword[6] = { 0,0,1,1,2,3 };

	/*״̬*****/int status = PREPARE;//ССӢ�۵�״̬
	int VICTORY = 0;//��¼��ʤ����
	int LOST = 0;  //��¼���ܴ���
	bool isDragging;//��¼�Ƿ����϶�ͼƬ
	/*ͼ����***/Sprite* YourLittleHreo;//ССӢ��
	Sprite* Movinghero;//�����ƶ���Ӣ��
	Sprite* Goldimage;//���ͼ��
	Sprite* Population;//�˿�ͼ��
	Sprite* avatarimage;//ͷ��ͼ��
	Sprite* Shopbackground;//�̵걳��
	Sprite* sellarea;//���������ͼƬ

<<<<<<< HEAD

	/*������ק��*/
	int chequers = 0;//�������ӵ�����
	Vec2 Lastposition;
	Hero* Draging_hero;

	Hero* Map[8][4];//��ͼ�ϵ�����λ��
	float MapSizeX[9] = { 382,  490.125 ,  598.25 ,  706.375, 814.5  ,922.625  , 1030.75  , 1138.875   , 1247 };
	float MapSizeY[5] = { 315,426.75,538.5,650.25,762 };
	float PreparationsSizeX[10] = { 279   ,386.88  ,  494.76  ,  602.64  , 710.52  , 818.4    ,926.28 ,   1034.16  ,  1142.04 , 1249.92 };
	float PreparationsSizeY[2] = { 215,315 };
	Vector<Hero*> Enemy_fightheros;//�з���������
	int Num = 0; //ССӢ�۱��
	int EnemyNum = 0; //���˵ı��
	int LastEnemyNum = 0; //�ϰѵ��˵ı��
	bool IsAI = 1; //�ǲ���AI

=======
	
	/*������ק��*/
	int chequers = 0;//��սϯ�����ӵ�����
	Vec2 Lastposition;
	Hero* Draging_hero;

	Hero* Map[8][4];//��ͼ�ϵ�����λ��
	float MapSizeX[9] = { 382,  490.125 ,  598.25 ,  706.375, 814.5  ,922.625  , 1030.75  , 1138.875   , 1247 };
	float MapSizeY[5] = { 315,426.75,538.5,650.25,762 };
	float PreparationsSizeX[10] = { 279   ,386.88  ,  494.76  ,  602.64  , 710.52  , 818.4    ,926.28 ,   1034.16  ,  1142.04 , 1249.92 };
	float PreparationsSizeY[2] = { 215,315 };
	Vector<Hero*> Enemy_fightheros;//�з���������
	int Num = 0; //ССӢ�۱��
	int EnemyNum = 0; //���˵ı��
	int LastEnemyNum = 0; //�ϰѵ��˵ı��
	bool IsAI = 1; //�ǲ���AI

>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	/*��Ϣ��ʾ��*/Label* Messagelabel;//��ʾ��ǩ

	cocos2d::Layer* heroslayer;//ѡ��ͼ��
	MapData* My_Map;//��Mapͼ����ССӢ���������ʼ��

	/*
	*��Ҫ�ϴ�������
	*/
	Vector<Hero*>fightheros;

};
/****************************************************************************
���ƣ�ССӢ�ۿ�������
���ܣ�����ССӢ�ۣ���һ������
�����У���ȡССӢ��ָ�������
 ****************************************************************************/
class LHcontroler : public cocos2d::Ref
{
public:
	friend Littlehero;
	/*��ʼ������*/
	void initlocal();
	void initonline();
    int get_mynumber();//��ȡ���ССӢ����controler�����λ��
	static LHcontroler* getInstance();//��ȡ����
	static void clearInstance();//���õ���
	int GetStatus();
	virtual bool init();//��ʼ��
	Littlehero* getMyLittleHero() { return heros.at(get_mynumber()); }
	bool Gameover = 0;
	void Godie(Node* layer);//�����Ľ��㶯��
	void menuCloseCallback(cocos2d::Ref* pSender);
	void Govictory(Node* layer);//Ӯ�˵Ľ��㶯��

	/*����*/
	Vector<Littlehero*> heros = {};

};
#endif // !SETTING_H 