#ifndef HEROES_H
#define HEROES_H

#include "cocos2d.h"

#define MAX_GRADE 5		//小小英雄最高等级
#define NUM_HEROES 3	//英雄数量
#define MAX_COST 3		//英雄最大价格
#define Hp_Bar 1    //血条标记
#define Mp_Bar 2    //蓝条标记
#define MaxAttack 12
#define MaxAttack_Archer 15
#define MAXWALKING 18
#define MAXWALKING_FAIRY 12

struct HeroImages;
enum HeroType { GOBLIN, MUMMY, GOLEM, FAIRY, KING, ARCHER, NINJA, PIRATE, WIZARD };	//英雄种类
enum FetterType { WARRIOR, MAGE, ADT, THREECOST, MT, MONOMER, KINGDOM, LIGHTDARK };
struct HeroPosition
	//英雄战斗位置坐标
{
	int x;    //横坐标
	int y;    //纵坐标
};

//英雄类
class Hero : public cocos2d::Node
{
public:
	virtual void FairyHeal();    //Fairy远程攻击
	virtual void ArcherArrow();    //Archer远程攻击
	virtual void MummyCurse();    //Mummy远程攻击
	virtual void WizardEffect();    //Wizard远程攻击
	virtual bool init();    //初始化英雄
	HeroType getID() const { return id; }    //获取ID
	virtual void getSpriteReady(int star1 = 1);					//生成精灵
	static Hero* createExactHero(HeroType type);	//创建特定种类的英雄
	void BodyInit();   //创建body
	void ToTurn(HeroPosition destination);    //判断转头函数
	void Turnaround();     //转头函数
	void SetSpace(cocos2d::Layer* space)
	{
		hero_space = space;
	}
	bool InitHp();    //初始化血条
	void UpdateHp(float delta);    //血条刷新
	bool InitMp();    //初始化蓝条
	void UpdateMp(float delta);    //蓝条刷新
	virtual void Death();    //死亡动画
	virtual void Attack();    //攻击动画
	virtual void Move(HeroPosition destination);    //移动动画
	virtual void Ultimate() {} //大招动画
	Hero* StarUp(Hero* a, Hero* b, Hero* c);    //升星动画
	HeroPosition getHeroPosition();    //获取英雄位置位置
	void setHeroPosition(HeroPosition NowPosition);
	HeroImages getImages();							//获取英雄图像信息
	int getCost();									//获取价格
	int getvalue();                                 //获取价值
	float getMaxHp() const { return maxHp; }    //获取英雄最大血量
	float getRealHp() const { return realHp; }    //获取实时血量
	float getMaxMp() const { return maxMp; }    //获取英雄最大蓝量
	float getRealMp() const { return realMp; }    //获取实时蓝量
	float getHurtMp() const { return hurtMp; }    //获得受伤回蓝量
	float getAttackMp() const { return attackMp; }    //获取攻击回蓝量
	int getRange() const { return range; }    //获取攻击距离
	int getDamage()const { return damage; }    //获取攻击伤害
	float getFrequency() const { return frequency; }    //获取攻击频率
	float getAttackCounter() const { return attackCounter; }    //获取用于判断攻击的计数器
	void ChangeAttackCounter(float ATK) { attackCounter = ATK; }    //改变判断攻击的计数器
	Hero* getEnemy() const { return enemy; }    //获取正在攻击的敌人
	cocos2d::Sprite* getBody() const { return body; }    //获取英雄精灵
	static Hero* copy(Hero* templt);    //拷贝
	void ChangeRealHp(float a) { realHp = a > maxHp ? maxHp : a; }    //改变实时血量
	void ChangeRealMp(float a) { realMp = a > maxMp ? maxMp : a; }    //改变实时蓝量
	void ChangeMaxHp(float a) { maxHp = a; }      //改变最大生命
	void ChangeDamage(float a) { damage = a; }    //改变攻击
	void ChangeFrequency(float a) { frequency = a; }      //改变攻速
	float getBaseFrequency() { return BaseFrequency; }
	void ChangeBaseFrequency(float a) { BaseFrequency = a; }
	bool IsAttack() const { return isAttack; }    //判断是否在攻击
	bool IsMove() const { return isMove; }    //判断是否在移动
	bool IsDead() const { return isDead; }    //判断是否死亡
	bool IsDying() const { return isDying; }    //判断是否正在死亡
	bool IsUltimate() { return isUltimate; }   //正在放大招
	bool IsVertigo() { return isVertigo; }    //正在眩晕
	void ChangeIsVertigo(bool v) { isVertigo = v; }    //改变眩晕状态
	void ChangeDead() { isDead = 0; }     //将死亡状态置为存活
	void ChooseEnemy(Hero* a) { enemy = a; }    //选择攻击的目标
	void ChangeFaceRight(bool Face1) { FaceRight = Face1; }   //改变朝向
	bool getFaceRight() { return FaceRight; }   //获取朝向
	void setStar(int Star);  //升星同时改变图片
	int getStar() { return star; }  //获取星级
	bool getMyHero() { return MyHero; }   
	void setMyHero(bool a) { MyHero = a; }
	int getKingBuff(int i) { return kingBuff[i]; }
	void ChangeKingBuff(int i, int a) { kingBuff[i] = a; }
	CREATE_FUNC(Hero);
protected:
	std::string HeroTypes[9] = {"Goblin","Mummy","Golem","Fairy","King","Archer","Ninja","Pirate","Wizard"};  //英雄类型
	const int HeroCosts[9] = { 2,2,1,3,1,2,3,2,2 };
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成样例）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
	int cost;							//价格
	HeroPosition position;    //英雄战斗位置坐标（英雄进入战场后赋值）
	cocos2d::Layer* hero_space;    //棋子所在的空间层
	cocos2d::Sprite* body;    //棋子
	cocos2d::Sprite* hp_bar;    //血条框
	cocos2d::Sprite* hp;    //血条
	cocos2d::Sprite* mp_bar;    //蓝条框
	cocos2d::Sprite* mp;    //蓝条
	float maxHp;    //最大血量
	float realHp;    //实时血量
	float maxMp;    //最大蓝量
	float realMp;    //实时蓝量
	float attackMp;    //攻击回蓝量
	float hurtMp;    //受伤回蓝量
	int range;    //攻击距离
	float damage;    //攻击伤害
	float frequency;    //攻击频率
	float BaseFrequency;   //基础攻击频率
	float moveSpeed;    //移动速度
	bool isAttack = 0;    //判断是否在攻击（Heroes在场上只具有三种状态，攻击，移动，死亡）
	bool isMove = 0;    //判断是否在移动
	bool isDead = 0;    //判断是否死亡
	bool isDying = 0;    //判断是否正在死亡
	bool isUltimate = 0;  //判断是否正在放大招
	bool FaceRight = 1;   //判断面朝的方向是不是右边
	float attackCounter = 0;    //用于判断攻击的计数器
	bool MyHero = 1;    //是否是我的棋子
	int kingBuff[3] = { 0,0,0 };   //国王攻速加成
	int star = 1;          //英雄星级
	bool isVertigo = 0;    //正在眩晕
	Hero* enemy = nullptr;    //攻击的目标
	HeroType id;						//ID（种类标志）
};

//英雄图像信息
struct HeroImages
{
	std::string imageOnField;			//战场形象（多个，暂时只开一个，后面可能要改成序列）
	std::string imageInStoreNormal;		//商店形象（正常）
	std::string imageInStoreSelected;	//商店形象（被选中）
};

class Golem :public Hero
	//坦克-Golem
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

//子弹类
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
	virtual void SetStar(int s);    //根据星级进行初始化
	CREATE_FUNC(Bullet);
protected:
	cocos2d::Sprite* body;    //子弹模型
	cocos2d::Layer* bullet_space;    //子弹所在空间层
	cocos2d::Vec2 speed;    //飞行速度
	int star;    //星级
	Hero* target;     //目标
	Hero* owner;    //子弹主人
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
