#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 5		//ССӢ����ߵȼ�
#define NUM_HEROES 3	//Ӣ������
#define MAX_COST 3		//Ӣ�����۸�
#define Hp_Bar 1    //Ѫ�����
#define Mp_Bar 2    //�������
#define MaxAttack 12
#define MaxAttack_Archer 15
#define MAXWALKING 18
#define MAXWALKING_FAIRY 12

struct HeroImages;
enum HeroType { GOBLIN, MUMMY, GOLEM, FAIRY, KING, ARCHER, NINJA, PIRATE, WIZARD };	//Ӣ������
enum FetterType { WARRIOR, MAGE, ADT, THREECOST, MT, MONOMER, KINGDOM, LIGHTDARK };
struct HeroPosition
	//Ӣ��ս��λ������
{
	int x;    //������
	int y;    //������
};

//Ӣ����
class Hero : public cocos2d::Node
{
public:
	virtual void FairyHeal();    //FairyԶ�̹���
	virtual void ArcherArrow();    //ArcherԶ�̹���
	virtual void MummyCurse();    //MummyԶ�̹���
	virtual void WizardEffect();    //WizardԶ�̹���
	virtual bool init();    //��ʼ��Ӣ��
	HeroType getID() const { return id; }    //��ȡID
	virtual void getSpriteReady(int star1 = 1);					//���ɾ���
	static Hero* createExactHero(HeroType type);	//�����ض������Ӣ��
	void BodyInit();   //����body
	void ToTurn(HeroPosition destination);    //�ж�תͷ����
	void Turnaround();     //תͷ����
	void SetSpace(cocos2d::Layer* space)
	{
		hero_space = space;
	}
	bool InitHp();    //��ʼ��Ѫ��
	void UpdateHp(float delta);    //Ѫ��ˢ��
	bool InitMp();    //��ʼ������
	void UpdateMp(float delta);    //����ˢ��
	virtual void Death();    //��������
	virtual void Attack();    //��������
	virtual void Move(HeroPosition destination);    //�ƶ�����
	virtual void Ultimate() {} //���ж���
	Hero* StarUp(Hero* a, Hero* b, Hero* c);    //���Ƕ���
	HeroPosition getHeroPosition();    //��ȡӢ��λ��λ��
	void setHeroPosition(HeroPosition NowPosition);
	HeroImages getImages();							//��ȡӢ��ͼ����Ϣ
	int getCost();									//��ȡ�۸�
	int getvalue();                                 //��ȡ��ֵ
	float getMaxHp() const { return maxHp; }    //��ȡӢ�����Ѫ��
	float getRealHp() const { return realHp; }    //��ȡʵʱѪ��
	float getMaxMp() const { return maxMp; }    //��ȡӢ���������
	float getRealMp() const { return realMp; }    //��ȡʵʱ����
	float getHurtMp() const { return hurtMp; }    //������˻�����
	float getAttackMp() const { return attackMp; }    //��ȡ����������
	int getRange() const { return range; }    //��ȡ��������
	int getDamage()const { return damage; }    //��ȡ�����˺�
	float getFrequency() const { return frequency; }    //��ȡ����Ƶ��
	float getAttackCounter() const { return attackCounter; }    //��ȡ�����жϹ����ļ�����
	void ChangeAttackCounter(float ATK) { attackCounter = ATK; }    //�ı��жϹ����ļ�����
	Hero* getEnemy() const { return enemy; }    //��ȡ���ڹ����ĵ���
	cocos2d::Sprite* getBody() const { return body; }    //��ȡӢ�۾���
	static Hero* copy(Hero* templt);    //����
	void ChangeRealHp(float a) { realHp = a > maxHp ? maxHp : a; }    //�ı�ʵʱѪ��
	void ChangeRealMp(float a) { realMp = a > maxMp ? maxMp : a; }    //�ı�ʵʱ����
	void ChangeMaxHp(float a) { maxHp = a; }      //�ı��������
	void ChangeDamage(float a) { damage = a; }    //�ı乥��
	void ChangeFrequency(float a) { frequency = a; }      //�ı乥��
	float getBaseFrequency() { return BaseFrequency; }
	void ChangeBaseFrequency(float a) { BaseFrequency = a; }
	bool IsAttack() const { return isAttack; }    //�ж��Ƿ��ڹ���
	bool IsMove() const { return isMove; }    //�ж��Ƿ����ƶ�
	bool IsDead() const { return isDead; }    //�ж��Ƿ�����
	bool IsDying() const { return isDying; }    //�ж��Ƿ���������
	bool IsUltimate() { return isUltimate; }   //���ڷŴ���
	bool IsVertigo() { return isVertigo; }    //����ѣ��
	void ChangeIsVertigo(bool v) { isVertigo = v; }    //�ı�ѣ��״̬
	void ChangeDead() { isDead = 0; }     //������״̬��Ϊ���
	void ChooseEnemy(Hero* a) { enemy = a; }    //ѡ�񹥻���Ŀ��
	void ChangeFaceRight(bool Face1) { FaceRight = Face1; }   //�ı䳯��
	bool getFaceRight() { return FaceRight; }   //��ȡ����
	void setStar(int Star);  //����ͬʱ�ı�ͼƬ
	int getStar() { return star; }  //��ȡ�Ǽ�
	bool getMyHero() { return MyHero; }   
	void setMyHero(bool a) { MyHero = a; }
	int getKingBuff(int i) { return kingBuff[i]; }
	void ChangeKingBuff(int i, int a) { kingBuff[i] = a; }
	CREATE_FUNC(Hero);
protected:
	std::string HeroTypes[9] = {"Goblin","Mummy","Golem","Fairy","King","Archer","Ninja","Pirate","Wizard"};  //Ӣ������
	const int HeroCosts[9] = { 2,2,1,3,1,2,3,2,2 };
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
	float damage;    //�����˺�
	float frequency;    //����Ƶ��
	float BaseFrequency;   //��������Ƶ��
	float moveSpeed;    //�ƶ��ٶ�
	bool isAttack = 0;    //�ж��Ƿ��ڹ�����Heroes�ڳ���ֻ��������״̬���������ƶ���������
	bool isMove = 0;    //�ж��Ƿ����ƶ�
	bool isDead = 0;    //�ж��Ƿ�����
	bool isDying = 0;    //�ж��Ƿ���������
	bool isUltimate = 0;  //�ж��Ƿ����ڷŴ���
	bool FaceRight = 1;   //�ж��泯�ķ����ǲ����ұ�
	float attackCounter = 0;    //�����жϹ����ļ�����
	bool MyHero = 1;    //�Ƿ����ҵ�����
	int kingBuff[3] = { 0,0,0 };   //�������ټӳ�
	int star = 1;          //Ӣ���Ǽ�
	bool isVertigo = 0;    //����ѣ��
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
	bool init()override;
	void getSpriteReady(int star1 = 1) override;
	void Ultimate()override;
	CREATE_FUNC(Golem);
protected:
};

class Goblin :public Hero
{
public:
	bool init()override;
	void getSpriteReady(int star1=1) override;
	void Ultimate()override;
	void Gold();
	CREATE_FUNC(Goblin);
};

class King :public Hero
{
public:
	bool init()override;
	void getSpriteReady(int star1=1) override;
	void Ultimate()override;
	void KingBuff(float dt);
	CREATE_FUNC(King);
};

class Pirate :public Hero
{
public:
	bool init()override;
	void getSpriteReady(int star1=1) override;
	void Ultimate()override;
	cocos2d::Vector<Hero*>Lock;
	CREATE_FUNC(Pirate);
};

class Ninja :public Hero
{
public:
	bool init()override;
	void getSpriteReady(int star1=1) override;
	Hero* Target=NULL;
	void Ultimate()override;
	CREATE_FUNC(Ninja);
};

class Fairy :public Hero
{
public:
	bool init()override;
	void getSpriteReady(int star1 = 1) override;
	void Ultimate()override;
	cocos2d::Vector<Hero*>Lock;
	void FairyHeal() override;
	CREATE_FUNC(Fairy);
};

class Archer :public Hero
{
public:
	bool init() override;
	void getSpriteReady(int star1 = 1) override;
	void ArcherArrow() override;
	void Ultimate()override;
	void Vertigo(float dt);
	CREATE_FUNC(Archer);
};
class Mummy :public Hero
{
public:
	bool init()override;
	void getSpriteReady(int star1 = 1) override;
	void Ultimate() override;
	void MummyCurse() override;
	CREATE_FUNC(Mummy);
};
class Wizard :public Hero
{
public:
	bool init()override;
	void getSpriteReady(int star1 = 1) override;
	void Ultimate() override;
	void WizardEffect() override;
	cocos2d::Vector<Hero*>Lock;
	CREATE_FUNC(Wizard);
};

//�ӵ���
class Bullet :public cocos2d::Node
{
public:
	virtual bool init();
	void SetSpace(cocos2d::Layer* space)
	{
		bullet_space = space;
	}
	cocos2d::Sprite* getBody() { return body; }
	void setDirection();
	virtual void updateFly(float dt);
	void chooseTarget(Hero* t) { target = t; }
	void chooseOwner(Hero* o) { owner = o; }
	void changeSpeed(cocos2d::Vec2 sp) { speed = sp; }
	virtual void SetStar(int s);    //�����Ǽ����г�ʼ��
	CREATE_FUNC(Bullet);
protected:
	cocos2d::Sprite* body;    //�ӵ�ģ��
	cocos2d::Layer* bullet_space;    //�ӵ����ڿռ��
	cocos2d::Vec2 speed;    //�����ٶ�
	int star;    //�Ǽ�
	Hero* target;     //Ŀ��
	Hero* owner;    //�ӵ�����
};

class Arrow :public::Bullet
{
public:
	bool init() override;
	CREATE_FUNC(Arrow);
};

class Archer_Ultimate :public::Bullet
{
public:
	bool init() override;
	void updateFly(float dt) override;
	CREATE_FUNC(Archer_Ultimate);
};


class Effect :public::Bullet
{
public:
	bool init() override;
	void updateFly(float dt) override;
	void SetStar(int s) override;
	CREATE_FUNC(Effect);
};

class Curse :public::Bullet
{
public:
	bool init() override;
	void updateFly(float dt) override;
	CREATE_FUNC(Curse);
};

class Heal :public::Bullet
{
public:
	bool init() override;
	void updateFly(float dt) override;
	void SetStar(int s) override;
	CREATE_FUNC(Heal);
};

#endif // !HEROES_H
