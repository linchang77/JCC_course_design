#pragma once

#ifndef HEROES_H
#define HEROES_H
#include "cocos2d.h"

#define MAX_GRADE 9		//ССӢ����ߵȼ�
#define NUM_HEROES 3	//Ӣ������
#define MAX_COST 5		//Ӣ�����۸�
#define Hp_Bar 1    //Ѫ�����
#define Mp_Bar 2    //�������

//ССӢ��
class LittleHero : public cocos2d::Sprite
{
public:
	//������
	static LittleHero* getInstance();

	//���صȼ�
	int getGrade();

private:
	int grade;			//�ȼ�
};

struct HeroImages;
enum HeroType { GOLEM };	//Ӣ������

struct HeroPosition
	//Ӣ��ս��λ������
{
	int x;    //������
	int y;    //������
};

//Ӣ��
class Hero : public cocos2d::Node
{
public:
	virtual bool init();    //��ʼ��Ӣ��
	HeroType getID() const { return id; }    //��ȡID
	virtual void getSpriteReady();					//���ɾ���
	static Hero* createExactHero(HeroType type);	//�����ض������Ӣ��
	void SetSpace(cocos2d::Layer* space)
	{
		hero_space = space;
	};
	bool InitHp();    //��ʼ��Ѫ��
	void UpdateHp(float delta);    //Ѫ��ˢ��
	bool InitMp();    //��ʼ������
	void UpdateMp(float delta);    //����ˢ��
	virtual void Death();    //��������
	virtual void Attack();    //��������
	virtual void Move(HeroPosition destination);    //�ƶ�����
	void StarUp(Hero* a, Hero* b, Hero* c);    //���Ƕ���
	//virtual void Ultimate();    //���ж���
	HeroPosition getHeroPosition();    //��ȡӢ��λ��λ��
	void setHeroPosition(HeroPosition NowPosition);
	HeroImages getImages();							//��ȡӢ��ͼ����Ϣ
	int getCost();									//��ȡ�۸�
	float getMaxHp() const { return maxHp; }    //��ȡӢ�����Ѫ��
	float getRealHp() const { return realHp; }    //��ȡʵʱѪ��
	float getMaxMp() const { return maxMp; }    //��ȡӢ���������
	float getRealMp() const { return realMp; }    //��ȡʵʱ����
	float getHurtMp() const { return hurtMp; }    //������˻�����
	int getRange() const { return range; }    //��ȡ��������
	float getFrequency() const { return frequency; }    //��ȡ����Ƶ��
	float getAttackCounter() const { return attackCounter; }    //��ȡ�����жϹ����ļ�����
	void ChangeAttackCounter(float ATK) { attackCounter = ATK; }    //�ı��жϹ����ļ�����
	Hero* getEnemy() const { return enemy; }    //��ȡ���ڹ����ĵ���
	cocos2d::Sprite* getBody() const { return body; }    //��ȡӢ�۾���
	static Hero* copy(Hero* templt);    //����
	void ChangeRealHp(float a) { realHp = a; }    //�ı�ʵʱѪ��
	void ChangeRealMp(float a) { realMp = a; }    //�ı�ʵʱ����
	bool IsAttack() const { return isAttack; }    //�ж��Ƿ��ڹ���
	bool IsMove() const { return isMove; }    //�ж��Ƿ����ƶ�
	bool IsDead() const { return isDead; }    //�ж��Ƿ�����
	bool IsDying() const { return isDying; }    //�ж��Ƿ���������
	void ChangeDead() { isDead = 0; }     //������״̬��Ϊ���
	void ChooseEnemy(Hero* a) { enemy = a; }    //ѡ�񹥻���Ŀ��
	void ChangeFaceRight(bool Face1) { FaceRight = Face1; }   //�ı䳯��
	bool getFaceRight() { return FaceRight; }   //��ȡ����
	CREATE_FUNC(Hero);
protected:
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ�������
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
	int cost;							//�۸�
	HeroPosition position;    //Ӣ��ս��λ�����꣨Ӣ�۽���ս����ֵ��
	cocos2d::Layer* hero_space;    //�������ڵĿռ��
	cocos2d::Sprite* body;    //����
	cocos2d::Sprite* hp_bar;    //Ѫ����
	cocos2d::Sprite* hp;    //Ѫ��
	cocos2d::Sprite* mp_bar;    //������
	cocos2d::Sprite* mp;    //����
	float maxHp;    //���Ѫ��
	float realHp;    //ʵʱѪ��
	float maxMp;    //�������
	float realMp;    //ʵʱ����
	float attackMp;    //����������
	float hurtMp;    //���˻�����
	int range;    //��������
	int damage;    //�����˺�
	float frequency;    //����Ƶ��
	float moveSpeed;    //�ƶ��ٶ�
	bool isAttack = 0;    //�ж��Ƿ��ڹ�����Heroes�ڳ���ֻ��������״̬���������ƶ���������
	bool isMove = 0;    //�ж��Ƿ����ƶ�
	bool isDead = 0;    //�ж��Ƿ�����
	bool isDying = 0;    //�ж��Ƿ���������
	bool FaceRight = 1;   //�ж��泯�ķ����ǲ����ұ�
	float attackCounter = 0;    //�����жϹ����ļ�����
	Hero* enemy = nullptr;    //������Ŀ��
	HeroType id;						//ID�������־��
};

//Ӣ��ͼ����Ϣ
struct HeroImages
{
	std::string imageOnField;			//ս�����󣨶������ʱֻ��һ�����������Ҫ�ĳ����У�
	std::string imageInStoreNormal;		//�̵�����������
	std::string imageInStoreSelected;	//�̵����󣨱�ѡ�У�
};

class Golem :public Hero
	//̹��-Golem
{
public:
	bool init() override;
	void Attack() override;
	void Death() override;
	void Move(HeroPosition destination) override;
	CREATE_FUNC(Golem);
protected:
};
#endif // !HEROES_H
