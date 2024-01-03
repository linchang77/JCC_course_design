#include"fight.h"
<<<<<<< HEAD
#include"Battlefield.h"
=======

>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
Isfight_label* Isfight_label::getInstance()
{
	if (!Isfight_l)
	{
		Isfight_l = new (std::nothrow)Isfight_label;
		Isfight_l->init();
	}
	return Isfight_l;
}
bool Isfight_label::init()
{
	if (!Label::init())
	{
		return 0;
	}
	float size = SIZE_THREE;
	float set_x = 800;
	float set_y = 848;
	ShowIsfight = Label::createWithTTF("Preparation Stage", "fonts/arial.ttf", size);
	ShowIsfight->setPosition(Vec2(set_x, set_y));
<<<<<<< HEAD
	ShowIsfight->setTag(3);
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	this->addChild(ShowIsfight);
	return 1;
}
void Isfight_label::update_Isfight(int x)
{
	if (x == 0)
	{
		ShowIsfight->setString("Preparation Stage");
	}
	else
	{
		ShowIsfight->setString("Fighting Stage");
	}
}
<<<<<<< HEAD
void Isfight_label::clearInstance()
{
	if (Isfight_l)
		delete Isfight_l;
	Isfight_l = nullptr;
}
=======

>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c

turn_label* turn_label::getInstance()
{
	if (!turn_l)
	{
		turn_l = new (std::nothrow)turn_label;
		turn_l->init();
	}
	return turn_l;
}
bool turn_label::init()
{
	if (!Label::init())
	{
		return 0;
	}
	float size = SIZE_THREE;
	float set_x = 400;
	float set_y = 848;
	char ch1[10];
	itoa(small_turn, ch1, 10);
	char ch2[10];
	itoa(big_turn, ch2, 10);
	const char* cat = "-";
	strcat(ch1, cat);
	strcat(ch1, ch2);
	// 创建一个标签
	Showturn = Label::createWithTTF(ch1, "fonts/arial.ttf", size);

	// 设置标签的位置
	Showturn->setPosition(Vec2(set_x, set_y));

	// 使用setTag为标签设置标识符
	Showturn->setTag(2);

	// 将标签添加到场景中
	this->addChild(Showturn);
	return 1;
}
<<<<<<< HEAD
void turn_label::clearInstance()
{
	if (turn_l)
		delete turn_l;
	turn_l = nullptr;
}
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
void turn_label::update_turns(int bigt,int smallt)
{
	big_turn = bigt;
	small_turn = smallt;
	char ch1[10];
	itoa(small_turn, ch1, 10);
	char ch2[10];
	itoa(big_turn, ch2, 10);
	const char* cat = "-";
	strcat(ch1, cat);
	strcat(ch1, ch2);
	Showturn->setString(ch1);
}


time_label* time_label::getInstance()
{
	if (!time_l)
	{
		time_l = new (std::nothrow)time_label;
		time_l->init();
	}
	return time_l;
}
bool time_label::init()
{
	if (!Label::init())
	{
		return 0;
	}
	float size = SIZE_THREE;
	float set_x = 1200, set_y = 848;
	// 创建一个标签
	Showtime = Label::createWithTTF(StringUtils::toString(num), "fonts/arial.ttf", size);

	// 设置标签的位置
	Showtime->setPosition(Vec2(set_x, set_y));

	// 使用setTag为标签设置标识符
	Showtime->setTag(1);

	// 将标签添加到场景中
	this->addChild(Showtime);
	return 1;
}
<<<<<<< HEAD
void time_label::clearInstance()
{
	if (time_l)
		delete time_l;
	time_l = nullptr;
}
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
void time_label::update_time(int x)
{
	num = x;
	Showtime->setString(StringUtils::toString(num));
	return;
}

<<<<<<< HEAD
void fight::Map1init()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Map1[i][j] = 0;
		}
	}
	for (auto& thishero : My_Hero_use)
	{
		HeroPosition h1;
		h1 = thishero->getHeroPosition();
		Map1[h1.x][h1.y] = 1;
	}
	for (auto& thishero : Enemy_Hero_use)
	{
		HeroPosition h1;
		h1 = thishero->getHeroPosition();
		Map1[h1.x][h1.y] = 1;
	}
}
=======

>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
bool fight::init()
{
	if (!Layer::init())
	{
		return false;
	}
<<<<<<< HEAD
	
	schedule(CC_SCHEDULE_SELECTOR(fight::Fight_base));
	return true;
}
fight* fight::getInstance()
{
	if (!Fight_layer)
	{
		Fight_layer = new(std::nothrow)fight;
		Fight_layer->init();
	}
	return Fight_layer;
}
fight* fight::clearInstance()
{
	if (Fight_layer)
	{
		delete Fight_layer;
		Fight_layer = NULL;
	}
	return nullptr;
}
bool fight::isfunction(Hero* thishero)
{//判断是否在做动作。
	if (thishero->IsVertigo())
		return 1;
	if (thishero->IsDying())
		return 1;
	if (thishero->IsMove())
		return 1;
	if (thishero->IsAttack())
		return 1;
	if (thishero->IsUltimate())
		return 1;
	return 0;
}

void fight::threeLabelsInit()
{  //三个标签（单例）的创建
	time_l1 = time_label::getInstance();
	time_l1->update_time(last_time - MaxTime / 2);
	this->addChild(time_l1);

	turn_l1 = turn_label::getInstance();
	turn_l1->update_turns(small_turn, big_turn);
	this->addChild(turn_l1);

	Isfight_l1 = Isfight_label::getInstance();
	Isfight_l1->update_Isfight(1);
	this->addChild(Isfight_l1);
}
void fight::removeAllLabels()
{
	time_l1->clearInstance();
	turn_l1->clearInstance();
	Isfight_l1->clearInstance();
}
void fight::makeallVectorEmpty()
{
	My_Hero_use.clear();
	Enemy_Hero_use.clear();
	Fetter_Labels.clear();
	Fetters.clear();
}
void fight::solveAllDead()
{
	for (auto& thishero : My_Hero_use)
	{
		if (thishero->IsDead())
		{
			somebodydead(thishero,is_my_hero);
			solveAllDead();
			return;
		}
	}
	is_my_hero = 0;
	for (auto& thishero : Enemy_Hero_use)
	{
		if (thishero->IsDead())
		{
			somebodydead(thishero, is_my_hero);
			solveAllDead();
			return;
		}
	}
	is_my_hero = 1;
	return;
}
void fight::giveLittleHeroDamage()
{
	auto LH = LHcontroler::getInstance();
	auto MyLittleHero = LH->getMyLittleHero();
	int SIZE = Enemy_Hero_use.size();
	int SIZE1 = My_Hero_use.size();
	int hp_change = big_turn * SIZE * DAMAGE;
	int enemy_hp_change = big_turn * SIZE1 * DAMAGE;
	if (hp_change != 0)
		MyLittleHero->update_WinOrLose(0, 1);
	else
		MyLittleHero->update_WinOrLose(1, 0);
	
	if (LH->GetStatus() == LOCAL)
	{
		MyLittleHero->changeHps(hp_change, MyLittleHero->getNum());
		MyLittleHero->changeHps(enemy_hp_change, MyLittleHero->getEnemyNum());
		for (int i = 0; i < LH->heros.size(); i++)
		{
			if (LH->heros.at(i) != MyLittleHero && i != MyLittleHero->getEnemyNum() && MyLittleHero->getHps(i)>0)
			{
				MyLittleHero->changeHps(big_turn * DAMAGE * 2, i);
			}
		}
	}
	if (LH->GetStatus() == ONLINE)
	{
		MyLittleHero->setEnemyHp(MyLittleHero->getEnemyHp() - enemy_hp_change);
	}
	MyLittleHero->Update_exp(2);
	MyLittleHero->update_Hp(hp_change);
	MyLittleHero->update_gold();
}
bool fight::endCheck()
{
	auto LH = LHcontroler::getInstance();
	auto MyLittleHero = LH->getMyLittleHero();
	if (MyLittleHero->getHp() <= 0)
	{
		LH->Godie(this);

		return true;
	}
	if (LH->GetStatus() == LOCAL)
	{
		for (int i = 1; i < LH->heros.size(); i++)
		{
			if (MyLittleHero->getHps(i) > 0)
				return false;
		}
	}
	if (LH->GetStatus() == ONLINE)
	{
		if (MyLittleHero->getEnemyHp() > 0)
			return false;
	}
	LH->Govictory(this);
	return 1;
}
//GOLEM, FAIRY, MUMMY, WIZARD, GOBLIN, KING, PIRATE, ARCHER, NINJA
//WARRIOR, MAGE, ADT, THREECOST, MT, MONOMER, , LIGHTDARK 
void fight::ChangeType(bool My1,int Type[],bool HasHero[])
{
	Vector<Hero*> IsMy_Hero;
	if(My1==1)
		IsMy_Hero = My_Hero_use;
	else
		IsMy_Hero = Enemy_Hero_use;
	for (auto& thishero : IsMy_Hero)
	{
		if (HasHero[thishero->getID()])
			continue;
		if (thishero->getID() == GOLEM)
		{
			HasHero[GOLEM] = 1;
			Type[MT]++;
			Type[ADT]++;
		}
		if (thishero->getID() == FAIRY)
		{
			HasHero[FAIRY] = 1;
			Type[KINGDOM]++;
			Type[LIGHTDARK]++;
		}
		if (thishero->getID() == MUMMY)
		{
			HasHero[MUMMY] = 1;
			Type[MAGE]++;
			Type[MONOMER]++;
		}
		if (thishero->getID() == WIZARD)
		{
			HasHero[WIZARD] = 1;
			Type[MAGE]++;
			Type[THREECOST]++;
		}
		if (thishero->getID() == GOBLIN)
		{
			HasHero[GOBLIN] = 1;
			Type[MONOMER]++;
			Type[WARRIOR]++;
		}
		if (thishero->getID() == KING)
		{
			HasHero[KING] = 1;
			Type[KINGDOM]++;
			Type[WARRIOR]++;
		}
		if (thishero->getID() == PIRATE)
		{
			HasHero[PIRATE] = 1;
			Type[THREECOST]++;
			Type[WARRIOR]++;
		}
		if (thishero->getID() == ARCHER)
		{
			HasHero[ARCHER] = 1;
			Type[ADT]++;
			Type[MONOMER]++;
		}
		if (thishero->getID() == NINJA)
		{
			HasHero[NINJA] = 1;
			Type[LIGHTDARK]++;
			Type[MONOMER]++;
		}
	}
}
void fight::FetterInit(int Type[])
{
	if (Type[WARRIOR])
	{
		auto Fetter = Sprite::create("Warrior.png");
		auto FetterLabel = Label::createWithTTF("[Warrior 2/3] : " + StringUtils::toString(Type[WARRIOR]), "fonts/arial.ttf", Fettersize);
		Fetters.pushBack(Fetter);
		Fetter_Labels.pushBack(FetterLabel);
	}
	if (Type[MAGE])
	{
		auto Fetter = Sprite::create("Mage.png");
		auto FetterLabel = Label::createWithTTF("[Mage 2] : " + StringUtils::toString(Type[MAGE]), "fonts/arial.ttf", Fettersize);
		Fetters.pushBack(Fetter);
		Fetter_Labels.pushBack(FetterLabel);
	}
	if (Type[ADT])
	{
		auto Fetter = Sprite::create("AD&T.png");
		auto FetterLabel = Label::createWithTTF("[AD&T 2] : " + StringUtils::toString(Type[ADT]), "fonts/arial.ttf", Fettersize);
		Fetters.pushBack(Fetter);
		Fetter_Labels.pushBack(FetterLabel);
	}
	if (Type[THREECOST])
	{
		auto Fetter = Sprite::create("Threecost.png");
		auto FetterLabel = Label::createWithTTF("[Three Cost 2] : " + StringUtils::toString(Type[THREECOST]), "fonts/arial.ttf", Fettersize);
		Fetters.pushBack(Fetter);
		Fetter_Labels.pushBack(FetterLabel);
	}
	if (Type[MT])
	{
		auto Fetter = Sprite::create("MT.png");
		auto FetterLabel = Label::createWithTTF("[Tank 1] : " + StringUtils::toString(Type[MT]), "fonts/arial.ttf", Fettersize);
		Fetters.pushBack(Fetter);
		Fetter_Labels.pushBack(FetterLabel);
	}
	if (Type[MONOMER])
	{
		auto Fetter = Sprite::create("Monomer.png");
		auto FetterLabel = Label::createWithTTF("[Conqueror 2/3/4] : " + StringUtils::toString(Type[MONOMER]), "fonts/arial.ttf", Fettersize);
		Fetters.pushBack(Fetter);
		Fetter_Labels.pushBack(FetterLabel);
	}
	if (Type[KINGDOM])
	{
		auto Fetter = Sprite::create("Kingdom.png");
		auto FetterLabel = Label::createWithTTF("[Kingdom 2] : " + StringUtils::toString(Type[KINGDOM]), "fonts/arial.ttf", Fettersize);
		Fetters.pushBack(Fetter);
		Fetter_Labels.pushBack(FetterLabel);
	}
	if (Type[LIGHTDARK])
	{
		auto Fetter = Sprite::create("Light&Dark.png");
		auto FetterLabel = Label::createWithTTF("[Light&Dark 2] : " + StringUtils::toString(Type[LIGHTDARK]), "fonts/arial.ttf", Fettersize);
		Fetters.pushBack(Fetter);
		Fetter_Labels.pushBack(FetterLabel);
	}
	
}
void fight::addFetters()
{
	int SIZE = Fetters.size();
	for (int i = 0; i < SIZE; i++)
	{
		this->addChild(Fetters.at(i));
		this->addChild(Fetter_Labels.at(i));
		Fetters.at(i)->setScale(1.2f);
		Fetter_Labels.at(i)->setScale(1.2);
		Fetters.at(i)->setPosition(FetterPlace + FetterDistance * i);
		Fetter_Labels.at(i)->setPosition(FetterLabelPlace + FetterDistance * i);
	}
}
void fight::giveAttribute(int Type[], bool My1)
{
	Vector<Hero*> IsMy_Hero;
	if (My1 == 1)
		IsMy_Hero = My_Hero_use;
	else
		IsMy_Hero = Enemy_Hero_use;
	for (auto& thishero : IsMy_Hero)
	{
		float ExtraAttack = 1, ExtraHp = 1, ExtraFrequency = 1;
		if (Type[KINGDOM] >= 2)
			ExtraFrequency += 0.1;
		if (thishero->getID() == GOLEM)
		{
			ExtraHp += 0.1;
			if (Type[ADT] >= 2)
				ExtraHp += 0.15;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
		if (thishero->getID() == FAIRY)
		{
			if (Type[LIGHTDARK] >= 2)
				ExtraHp += 0.15;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
		if (thishero->getID() == MUMMY)
		{
			if (Type[MAGE] >= 2)
				ExtraAttack += 0.15;
			if (Type[MONOMER] >= 2)
				ExtraAttack += 0.15;
			if (Type[MONOMER] >= 3)
				ExtraAttack += 0.05;
			if (Type[MONOMER] >= 4)
				ExtraAttack += 0.05;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
		if (thishero->getID() == WIZARD)
		{
			if (Type[MAGE] >= 2)
				ExtraAttack += 0.15;
			if (Type[THREECOST] >= 2)
				ExtraFrequency += 0.1;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
		if (thishero->getID() == GOBLIN)
		{
			if (Type[WARRIOR] >= 2)
				ExtraAttack += 0.10,
				ExtraHp += 0.10;
			if (Type[WARRIOR] >= 3)
				ExtraAttack += 0.05,
				ExtraHp += 0.05;
			if (Type[MONOMER] >= 2)
				ExtraAttack += 0.15;
			if (Type[MONOMER] >= 3)
				ExtraAttack += 0.05;
			if (Type[MONOMER] >= 4)
				ExtraAttack += 0.05;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
		if (thishero->getID() == KING)
		{
			if (Type[WARRIOR] >= 2)
				ExtraAttack += 0.10,
				ExtraHp += 0.10;
			if (Type[WARRIOR] >= 3)
				ExtraAttack += 0.05,
				ExtraHp += 0.05;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
		if (thishero->getID() == PIRATE)
		{
			if (Type[WARRIOR] >= 2)
				ExtraAttack += 0.10,
				ExtraHp += 0.10;
			if (Type[WARRIOR] >= 3)
				ExtraAttack += 0.05,
				ExtraHp += 0.05;
			if (Type[THREECOST] >= 2)
				ExtraFrequency += 0.1;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
		if (thishero->getID() == ARCHER)
		{
			if (Type[ADT] >= 2)
				ExtraAttack += 0.15;
			if (Type[MONOMER] >= 2)
				ExtraAttack += 0.15;
			if (Type[MONOMER] >= 3)
				ExtraAttack += 0.05;
			if (Type[MONOMER] >= 4)
				ExtraAttack += 0.05;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
		if (thishero->getID() == NINJA)
		{
			if (Type[WARRIOR] >= 2)
				ExtraAttack += 0.15;
			if (Type[MONOMER] >= 2)
				ExtraAttack += 0.15;
			if (Type[MONOMER] >= 3)
				ExtraAttack += 0.05;
			if (Type[MONOMER] >= 4)
				ExtraAttack += 0.05;
			thishero->ChangeMaxHp(thishero->getMaxHp() * ExtraHp);
			thishero->ChangeRealHp(thishero->getMaxHp());
			thishero->ChangeDamage(thishero->getDamage() * ExtraAttack);
			thishero->ChangeFrequency(thishero->getFrequency() * ExtraFrequency);
			thishero->ChangeBaseFrequency(thishero->getFrequency());
		}
	}
}
void fight::FindType()
{
	int Type[8] = { 0 };
	bool HasHero[9] = { 0 };
	ChangeType(1, Type, HasHero);
	//WARRIOR, MAGE, ADT, THREECOST, MT, MONOMER, , LIGHTDARK 
	FetterInit(Type);
	addFetters();
	giveAttribute(Type, 1);
	for (int i = 0; i < 8; i++)
		Type[i] = 0;
	for (int i = 0; i < 9; i++)
		HasHero[i] = 0;

	ChangeType(0, Type, HasHero);
	giveAttribute(Type, 0);
}

void fight::Fight_base(float dt)
{
	if (isAllend == 1)
		return;//如果战斗结束了（赢或输），就不再进行战斗
	is_my_hero = 1;
	timef += dt;
	if (last_time == 1 && is_Fight == 1)
	{//战斗结束。
		giveLittleHeroDamage();  //处理小小英雄伤害，处理回合结束的金币经验
		if (endCheck()) 
			isAllend = 1;//确认结束
		if (isAllend == 1)
			return;
		this->removeAllChildren();  //移除所有子节点的连接
		makeallVectorEmpty();  //Vector全部清空
		removeAllLabels();  //移除三个标签（时间轮次战斗阶段）
		small_turn++;
		if (small_turn > 3)
			small_turn = 1,
			big_turn++;	
		last_time=MaxTime + 1;  //重置时间
		is_Fight = 0;
	}
	if (timef >= 1)
	{  //计时模块
		timef--;
		last_time--;
	}
	if (last_time > MaxTime/2)
	{  //在准备阶段时不进行战斗
		return;
	}
	else if (last_time == MaxTime / 2 && is_Fight == 0)
	{//战斗开始
		auto LH = LHcontroler::getInstance();
		is_Fight = 1;  //记录正在战斗
		threeLabelsInit();  //三个标签初始化
		if (LH->GetStatus() == LOCAL)
			MatchAI();  //自动匹配AI（在联机时无效）
		if (isAllend == 1)
			return;
		pullHeros();  //将你和对手的棋子放入棋盘中

		if (LH->GetStatus() == LOCAL)
			putHeros();  //练习模式的对手棋子由这里放置
		FindType();   //查找羁绊，并给棋子加成
		Map1init();   //初始化地图
	}
	
	time_l1->update_time(last_time-1);  //更新时间显示
	int SIZE = My_Hero_use.size();  
	solveAllDead();  //处理所有棋子死亡问题
	is_my_hero = 1;
	for (auto &thisHero : My_Hero_use)
	{//处理我方棋子的操作
		for (int i = 0; i < 3; i++)
		{  //特殊处理国王Buff问题
			if (thisHero->getKingBuff(i))
				thisHero->ChangeFrequency(thisHero->getBaseFrequency() + (i + 1) * KINGBUFF);
		}
		if (thisHero->getAttackCounter() < 1.0f / (thisHero->getFrequency()))
			thisHero->ChangeAttackCounter(thisHero->getAttackCounter() + dt);   //攻击计时器，达到可攻击时间后即可攻击
		if (isfunction(thisHero))
			continue;//正在执行动画，不可进行其它操作。
		if (thisHero->getRealHp() <= 0 && !thisHero->IsDead())
		{//发现没血，开始执行死亡动画
			thisHero->Death();
			Map1[thisHero->getHeroPosition().x][thisHero->getHeroPosition().y] = 0;
			continue;
		}
		if (thisHero->getEnemy())
		{//有目标可能已丢失，需要再次判断
			if (!Hasenemy(thisHero, thisHero->getEnemy()))
			{
				thisHero->ChooseEnemy(NULL);
			}
		}
		if (!thisHero->getEnemy())
		{//如果没有敌人，寻找敌人
			Findenemy(thisHero);
		}
		if (thisHero->getEnemy())
		{ //如果找到了目前可以攻击到的敌人
			if (thisHero->getMaxMp()==thisHero->getRealMp())
			{ //如果能放大招优先放大招
				thisHero->Ultimate();
				continue;
			}
			if (thisHero->getAttackCounter()>=1.0f/(thisHero->getFrequency()))
			{  //对目标发起攻击
				thisHero->Attack();
				thisHero->ChangeAttackCounter(thisHero->getAttackCounter() - 1.0f / (thisHero->getFrequency())); //重置攻击计时器。
=======
	for (auto& e : My_Hero_use)
	{
		/*
		HeroPosition h1;
		h1 = e->getPosition();
		Map1[h1.x][h1.y] = 1;
		*/
	}
	for (auto& e : Enemy_Hero_use)
	{
		/*
		HeroPosition h1;
		h1 = e->getPosition();
		Map1[h1.x][h1.y] = 1;
		*/
	}
	time_l1 = time_label::getInstance();
	turn_l1 = turn_label::getInstance();
	Isfight_l1 = Isfight_label::getInstance();
	schedule(CC_SCHEDULE_SELECTOR(fight::Fight_base));
	return true;
}
/*
bool fight::isfunction(Hero* e)
{
	if (e->getIsdying())
		return 1;
	if (e->getIsmove())
		return 1;
	if (e->getIsattack())
		return 1;
	return 0;
}
*/

void fight::Fight_base(float dt)
{
	is_my_hero = 1;
	timef += dt;
	if (last_time == 0)
	{
		small_turn++;
		if (small_turn > 7)
			small_turn = 1,
			big_turn++;
		if (big_turn == 1 && small_turn > 3)
			small_turn = 1,
			big_turn++;	
		last_time=MaxTime;
		turn_l1->update_turns(small_turn,big_turn);
	}
	if (timef >= 1)
	{
		timef--;
		last_time--;
		if(last_time > 0&&last_time<=MaxTime/2)
		time_l1->update_time(last_time);
	}
	if (last_time > MaxTime/2)
	{
		return;
	}
	else if(last_time == MaxTime/2)
	{
		Isfight_l1->update_Isfight(1);
	}
	return;
	/*
	for (auto& e : My_Hero_use)
	{
		if (e->getAttackCounter() < 1.0f / (e->getFrequency()))
			e->changeAttackCounter(e->getAttackCounter() + dt);
		if (isfunction(e))
			continue;//正在执行动画，不可进行其它操作。
		if (e->getRealHp() <= 0 && !e->getIsdead())
		{//发现没血，开始执行死亡动画
			e->Death();
			continue;
		}
		if (e->getIsdead())
		{//死亡动画执行完毕，死透了。
			somebodydead(e, is_my_hero);
		}
		if (e->getEnemy())
		{//有目标可能已丢失，需要再次判断
			if (!Hasenemy(e,e->getEnemy()))
			{
				e->chooseEnemy(NULL);
			}
		}
		if (!e->getEnemy())
		{
			Findenemy(e);
		}
		if (e->getEnemy())
		{
			if (e->getAttackCounter()>=1.0f/(e->getFrequency()))
			{
				e->Attack(e->getEnemy());
				e->changeAttackCounter(e->getAttackCounter() - 1.0f / (e->getFrequency()));
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
			}
		}
	}
	is_my_hero = 0;
<<<<<<< HEAD
	for (auto& thisHero : Enemy_Hero_use)
	{//代码同上，处理敌人的操作
		for (int i = 0; i < 3; i++)
		{  
			if (thisHero->getKingBuff(i))
				thisHero->ChangeFrequency(thisHero->getBaseFrequency() + (i + 1) * KINGBUFF);
		}
		if (thisHero->getAttackCounter() < 1.0f / (thisHero->getFrequency()))
			thisHero->ChangeAttackCounter(thisHero->getAttackCounter() + dt);
		if (isfunction(thisHero))
			continue;//正在执行动画，不可进行其它操作。
		if (thisHero->getRealHp() <= 0 && !thisHero->IsDead())
		{//发现没血，开始执行死亡动画
			thisHero->Death();
			Map1[thisHero->getHeroPosition().x][thisHero->getHeroPosition().y] = 0;
			continue;
		}
		
		if (thisHero->getEnemy())
		{//有目标可能已丢失，需要再次判断
			if (!Hasenemy(thisHero, thisHero->getEnemy()))
			{
				thisHero->ChooseEnemy(NULL);
			}
		}
		if (!thisHero->getEnemy())
		{
			Findenemy(thisHero);
		}
		if (thisHero->getEnemy())
		{
			if (thisHero->getRealMp() == thisHero->getMaxMp())
			{
				thisHero->Ultimate();
				continue;
			}
			if (thisHero->getAttackCounter() >= 1.0f / (thisHero->getFrequency()))
			{
				thisHero->Attack();
				thisHero->ChangeAttackCounter(thisHero->getAttackCounter() - 1.0f / (thisHero->getFrequency()));
			}
		}
	}
};

void fight::putHeros()
{
	HeroPosition enemyP;
	int x1, y1;
	int Maxsize = 2 + big_turn;
	int cost = 10*big_turn + 4 * small_turn ;  //对面的金币数（除去D牌、买经验操作，可用金币数）
	int count = 0;  //计算当前上场的人数
	if (Maxsize > 5)
		Maxsize = 5;  //对面的最大人口数
	while(count<Maxsize&&cost>0)
	{
		x1=random(4, 7);
		y1=random(0, 3);
		auto LH = LHcontroler::getInstance();
		enemyP.x = x1;
		enemyP.y = y1;
		int TheID = 0;
		if (Maxsize < 4)
			TheID = random(0, 6);  //在对面没升级到4时，不会D出3费卡
		else
			TheID = random(0, 8);  //4级后可能D出三费
		HeroType Type1 = static_cast<HeroType>(TheID);
		int Star1 = 1, MaxStar1 = 1;
		if (Map1[x1][y1] == 0)
		{
			auto newHero = Hero::createExactHero(Type1); //对面买的英雄
			int cost1 = newHero->getCost() * 2 - 1;
			while (MaxStar1 <= 3 && cost1 * 3 <= cost)
				MaxStar1++,
				cost1*=3;
			Star1 = random(1, MaxStar1);  //英雄星级
			cost1 = newHero->getCost() * 2 - 1; //购买花费
			MaxStar1 = Star1;
			while (MaxStar1 > 1)
			{
				cost1 *= 3;
				MaxStar1--;
			}  //购买的花销计算
			cost -= cost1;  //对面可能有存钱操作，故不一定会花完
			newHero->setHeroPosition(enemyP);
			newHero->setPosition(LH->heros.at(0)->getmidposition(enemyP.x, enemyP.y));
			newHero->setMyHero(false);
			newHero->InitHp();
			newHero->InitMp();
			newHero->setStar(Star1);
			newHero->getSpriteReady(newHero->getStar());
			newHero->Turnaround();  
			newHero->ChangeFaceRight(0);  //反向（对面棋子）
			this->addChild(newHero);//创造一个棋子的全过程
			Enemy_Hero_use.pushBack(newHero);  //对面将该棋子放到场上
			Map1[x1][y1] = 1;
			count++;
		}
	}
}
void fight::pullHeros()
{
	auto LH = LHcontroler::getInstance();
	Littlehero *littlehero1=LH->getMyLittleHero();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			auto fieldhero = littlehero1->Fightfield[i][j];  //访问我的战场
			if (fieldhero != nullptr)
			{
				auto herocopy = Hero::copy(fieldhero);  //制造我方棋子的复制
				Vec2 heroposition = littlehero1->getmidposition(herocopy->getHeroPosition().x, herocopy->getHeroPosition().y);
				herocopy->setPosition(heroposition);
				herocopy->InitHp();
				herocopy->InitMp();
				herocopy->getSpriteReady(herocopy->getStar());
				this->addChild(herocopy); //加入图层渲染
				My_Hero_use.pushBack(herocopy);  //加入我方英雄Vector中
			}
		}
	}
	if (LH->GetStatus() == ONLINE)  
	{
		for (auto &thishero : littlehero1->getEnemyFightingHeroes())
		{//在联机模式下，调取对方棋子并且加入敌方英雄Vector中。
			if (thishero != nullptr)
			{
				auto herocopy = Hero::copy(thishero);
				Vec2 heroposition = littlehero1->getmidposition(herocopy->getHeroPosition().x, herocopy->getHeroPosition().y);
				herocopy->setPosition(heroposition);
				herocopy->setMyHero(false);
				herocopy->InitHp();
				herocopy->InitMp();
				herocopy->getSpriteReady(herocopy->getStar());
				
				this->addChild(herocopy);
				Enemy_Hero_use.pushBack(herocopy);
			}
		}
	}
	return;
}

void fight::somebodydead(Hero* Hero1,bool isMy)
{//一个人死后要干的事情：先释放当前位置的格子，然后再将所有锁定该角色的人锁定目标清除，最后从容器中移除该角色。
	HeroPosition h1 = Hero1->getHeroPosition();
	if (isMy == 1)
	{
		for (auto& thishero : Enemy_Hero_use)
		{
			if (thishero->getEnemy() == Hero1)
			{
				thishero->ChooseEnemy(NULL);
			}
		}
		Hero1->ChangeIsVertigo(0);
		My_Hero_use.erase(My_Hero_use.find(Hero1));
	}
	if (isMy == 0)
	{
		for (auto& thishero : My_Hero_use)
		{
			if (thishero->getEnemy() == Hero1)
			{
				thishero->ChooseEnemy(NULL);
			}
		}
		Hero1->ChangeIsVertigo(0);
		Enemy_Hero_use.erase(Enemy_Hero_use.find(Hero1));
	}
}
bool fight::Hasenemy(Hero *Hero1,Hero*Hero2)
{//是否有可攻击敌人
	if (solve_distance(Hero1, Hero2) <= Hero1->getRange() && Hero2->getRealHp() > 0)
=======
	for (auto& e : Enemy_Hero_use)
	{
		if (e->getAttackCounter() < 1.0f / (e->getFrequency()))
			e->ChangeAttackCounter(e->getAttackCounter() + dt);
		if (isfunction(e))
			continue;//正在执行动画，不可进行其它操作。
		if (e->getRealHp() <= 0 && !e->getIsDead())
		{//发现没血，开始执行死亡动画
			e->Death();
			continue;
		}
		if (e->getIsDead())
		{//死亡动画执行完毕，死透了。
			somebodydead(e, is_my_hero);
		}
		if (e->getEnemy())
		{//有目标可能已丢失，需要再次判断
			if (!Hasenemy(e, e->getEnemy()))
			{
				e->ChooseEnemy(NULL);
			}
		}
		if (!e->getEnemy())
		{
			Findenemy(e);
		}
		if (e->getEnemy())
		{
			if (e->getAttackCounter() >= 1.0f / (e->getFrequency()))
			{
				e->Attack(e->getEnemy());
				e->ChangeAttackCounter(e->getAttackCounter() - 1.0f / (e->getFrequency()));
			}
		}
	}*/
};

/*
void fight::somebodydead(Hero* e1,bool isMy)
{//一个人死后要干的事情：先释放当前位置的格子，然后再将所有锁定该角色的人锁定目标清除，最后从容器中移除该角色。
	HeroPosition h1 = e1->getPosition();
	Map1[h1.x][h1.y] = 0;
	if (isMy == 1)
	{
		for (auto& e : Enemy_Hero_use)
		{
			if (e->getEnemy() == e1)
			{
				e->ChooseEnemy(NULL);
			}
		}
		My_Hero_use.erase(My_Hero_use.find(e1));
	}
	if (isMy == 0)
	{
		for (auto& e : My_Hero_use)
		{
			if (e->getEnemy() == e1)
			{
				e->ChooseEnemy(NULL);
			}
		}
		Enemy_Hero_use.erase(Enemy_Hero_use.find(e1));
	}
}
bool fight::Hasenemy(Hero *Hero1,Hero*Hero2)
{
	if (solve_distance(Hero1, Hero2) <= Hero1->getRange())
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	{
		return 1;
	}
	return 0;
}
int fight::solve_distance(Hero *Hero1,Hero *Hero2)
{
	HeroPosition h1, h2;
<<<<<<< HEAD
	h1 = Hero1->getHeroPosition();
	h2 = Hero2->getHeroPosition();
	return abs(h1.x - h2.x) + abs(h1.y - h2.y);  //得出距离
}
bool fight::isFace(Hero *Hero1,Hero* Hero2)
{//两个人是否面对？
	if (Hero1->getHeroPosition().y == Hero2->getHeroPosition().y)
		return 1;
	else
		return 0;
}
bool fight::Findenemy(Hero *Hero1)
{ //找敌人
	int min_distance = 100;
	Hero* enemy_hero=NULL;
	if (is_my_hero == 1)  //我方和敌方分开判断
		for (auto& thishero : Enemy_Hero_use)
		{
			if (thishero->getRealHp() <= 0)
				continue;
			int len = solve_distance(Hero1, thishero);
			if (min_distance >= len)
			{
				if (isFace(Hero1, thishero))
				{
					min_distance = len;
					enemy_hero = thishero;
				}  //优先锁定面前的敌人
				else if (min_distance > len)
				{
					min_distance = len;
					enemy_hero = thishero;
				}
			}
		}
	else
		for (auto& thishero : My_Hero_use)
		{
			if (thishero->getRealHp() <= 0)
				continue;
			int len = solve_distance(Hero1, thishero);
			if (min_distance >= len)
			{
				if (isFace(Hero1, thishero))
				{
					min_distance = len;
					enemy_hero = thishero;
				}
				else if (min_distance > len)
				{
					min_distance = len;
					enemy_hero = thishero;
				}
			}
		}
	if (!enemy_hero)
		return 0;
	if (Hero1->getRange() > 1) //远程目标判定（怎么都能打到）
		if (min_distance <= Hero1->getRange())
		{//如果敌人离你最短的距离小于你的射程，锁定目标
			Hero1->ToTurn(enemy_hero->getHeroPosition());
			Hero1->ChooseEnemy(enemy_hero);
			return 1;
		}
		else
		{//如果敌人离你距离大于射程，就开始找路，找到路就开始move，此时getEnemy不会被设置为1，且ismove变为1。
			Find_way(Hero1);
		}
	else  //近战只能在前后打
	{
		if (min_distance <= Hero1->getRange() && isFace(Hero1,enemy_hero))
		{//如果敌人离你最短的距离小于你的射程同时面向敌方，锁定目标
			Hero1->ToTurn(enemy_hero->getHeroPosition());
			Hero1->ChooseEnemy(enemy_hero);
			return 1;
		}
		else
		{//如果敌人离你距离大于射程，就开始找路，找到路就开始move，此时getEnemy不会被设置为1，且ismove变为1。
			Find_way(Hero1);
		}
	}
	return 0;
}
bool fight::trueposition(int x,int y)
{  //位置是否正确？
=======
	h1 = Hero1->getPosition();
	h2 = Hero2->getPosition();
	return abs(h1.x - h2.x) + abs(h1.y - h2.y);
}
bool fight::Findenemy(Hero *Hero1)
{
	int min_distance = 15;
	Hero* enemy_hero=NULL;
	for (auto& e : Enemy_Hero_use)
	{
		int len = solve_distance(Hero1, e);
		if (min_distance < len)
		{
			min_distance = len;
			enemy_hero = e;
		}
	}
	if (min_distance <= Hero1->getRange())
	{//如果敌人离你最短的距离小于你的射程，锁定目标
		Hero1->ChooseEnemy(enemy_hero);
		return 1;
	}
	else
	{//如果敌人离你距离大于射程，就开始找路，找到路就开始move，此时getEnemy不会被设置为1，且ismove变为1。
		Find_way(Hero1, enemy_hero);
	}
	return 0;
}
bool fight::trueposition(int x,int y)
{
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	if (x < 8 && x >= 0 && y < 4 && y >= 0)
		return 1;
	return 0;
}
<<<<<<< HEAD
bool fight::isFace(HeroPosition HPT1, HeroPosition HPT2)
{//是否面对？（两个位置）
	if (HPT1.y == HPT2.y)
		return 1;
	else return 0;
}
HeroPosition fight::bfs(Hero *WantFind)
=======

HeroPosition fight::bfs()
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			vis[i][j] = 0;
			if (Map1[i][j] == 1)
				vis[i][j] = 1;
		}
<<<<<<< HEAD
	}//初始化vis数组
	que.pushBack(new way_Node(start,NULL));
	//通过Vector模拟队列实现bfs查找最短路径
	while (!que.empty())
	{
		way_Node* tmp = que.front();   //查看队头
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{//下一步会到哪里
				if (abs(i) + abs(j) != 1)
=======
	}
	que.pushBack(way_Node(start,NULL));
	while (!que.empty())
	{
		way_Node* tmp = new way_Node(que.front());
		que.popBack();
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (abs(i) + abs(j) > 1)
					continue;
				if (i == j && i == 0)
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
					continue;
				HeroPosition h0;
				h0.x = tmp->place.x + i;
				h0.y = tmp->place.y + j;
<<<<<<< HEAD
				if (!trueposition(h0.x, h0.y))
					continue;  //位置不对
				if (vis[h0.x][h0.y])
					continue;  //已经走过
				vis[h0.x][h0.y] = 1;  
				que.pushBack(new way_Node(h0, tmp));  //这个位置入队
				if (is_my_hero == 1)
				{//我方攻击判定（包括近战和远程）
					for (auto& thishero : Enemy_Hero_use)
					{//看敌人哪个好打
						if (thishero->getRealHp() <= 0)
							continue;  //没血不打
						HeroPosition EnemyPosition = thishero->getHeroPosition();
						if (WantFind->getRange() == 1)
						{  //近战判定（需要保证在左右两边）
							if (abs(h0.x - EnemyPosition.x) + abs(h0.y - EnemyPosition.y) == WantFind->getRange() && isFace(thishero->getHeroPosition(), h0))
							{ //判断该位置是否能打到目标
								if (!tmp->pre)
								{  //如果没有上一步就直接走到h0
									que.clear();
									return h0;
								}
								while ((tmp->pre->place.x != start.x || tmp->pre->place.y != start.y))
								{   //找到最开始的下一步位置 
									tmp = tmp->pre;
								}
								que.clear();
								return tmp->place;
							}
						}
						else
						{
							if (abs(h0.x - EnemyPosition.x) + abs(h0.y - EnemyPosition.y) <= WantFind->getRange())
							{  //同上
								if (!tmp->pre)
								{
									que.clear();
									return h0;
								}
								while ((tmp->pre->place.x != start.x || tmp->pre->place.y != start.y))
								{
									tmp = tmp->pre;
								}
								que.clear();
								return tmp->place;
							}
						}
					}
				}
				if (is_my_hero == 0)
				{//敌方攻击判定（近战远程）
					for (auto& thishero : My_Hero_use)
					{ //同上
						if (thishero->getRealHp() <= 0)
							continue;
						HeroPosition EnemyPosition = thishero->getHeroPosition();
						if (WantFind->getRange() == 1)
						{
							if (abs(h0.x - EnemyPosition.x) + abs(h0.y - EnemyPosition.y) == WantFind->getRange() && isFace(thishero->getHeroPosition(), h0))
							{
								if (!tmp->pre)
								{
									que.clear();
									return h0;
								}
								while ((tmp->pre->place.x != start.x || tmp->pre->place.y != start.y))
								{
									tmp = tmp->pre;
								}
								que.clear();
								return tmp->place;
							}
						}
						else
						{
							if (abs(h0.x - EnemyPosition.x) + abs(h0.y - EnemyPosition.y) <= WantFind->getRange())
							{
								if (!tmp->pre)
								{
									que.clear();
									return h0;
								}
								while ((tmp->pre->place.x != start.x || tmp->pre->place.y != start.y))
								{
									tmp = tmp->pre;
								}
								que.clear();
								return tmp->place;
							}
						}
					}
				}
			}
		}
		que.erase(0);  //最后把队列头弹出
=======
				if (h0.x == end.x && h0.y == end.y)
				{
					while (tmp->pre->place.x != start.x || tmp->pre->place.y!=start.y)
					{
						tmp = tmp->pre;
					}
					return tmp->place;
				}
				vis[h0.x][h0.y] = 1;
				que.pushBack(way_Node(h0, tmp));
			}
		}
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	}
	HeroPosition h0;
	h0.x = h0.y = -1;
	return h0;
}

<<<<<<< HEAD
bool fight::Find_way(Hero* Hero1)
{
	start = Hero1->getHeroPosition();
	HeroPosition h0 = bfs(Hero1);  //通过bfs求取下一步要到的位置。
	
=======
bool fight::Find_way(Hero* Hero1,Hero* Hero2)
{
	start = Hero1->getPosition();
	end = Hero2->getPosition();
	HeroPosition h0 = bfs();
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
	if (h0.x == h0.y && h0.x == -1)
	{}//故意留空，不是写错
	else
	{
<<<<<<< HEAD
		if (!isfunction(Hero1))
		{  //如果棋子不在做动作就移动到h0位置
			Map1[start.x][start.y] = 0;
			Map1[h0.x][h0.y] = 1;
			Hero1->Move(h0);
		}
=======
		/*
		if(!Hero1->getIsattack())
		Hero1->Move(h0);
		
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
		return 1;
	}
	return 0;
}
<<<<<<< HEAD

void fight::MatchAI()
{
	auto LH = LHcontroler::getInstance();
	int LH_size = LH->heros.size();
	int my_number = LH->get_mynumber();
	int enemy_num = -1;
	while (1)
	{
		enemy_num = random(0, LH_size - 1);
		if (enemy_num == my_number)
			continue;
		if (LH->getMyLittleHero()->getHps(enemy_num) <= 0)
			continue;
		if (Has_Match_AI[enemy_num])
			continue;
		LH->heros.at(my_number)->chooseEnemyNum(enemy_num);
		Has_Match_AI[enemy_num] = 1;
		break;
	}
	bool AI_Filled = 1;
	for (int i = 0; i < 4; i++)
	{
		if (i == my_number)
			continue;
		if (Has_Match_AI[i] == 0 && LH->getMyLittleHero()->getHps(i) > 0)
			AI_Filled = 0;
	}
	if (AI_Filled)
	{
		for (int i = 0; i < 4; i++)
			Has_Match_AI[i] = 0;
	}
}
=======
void fight::add_ai()
{

	return;
}
*/
/*void fight::Match()
{
	auto LH = LHcontroler::getInstance();
	int LH_size = LH->heros.size();
	for (int i = 1; i <= LH_size / 2 - 1; i++)
	{
		int hero1_num=-1, hero2_num=-1;
		while (1)
		{
			hero2_num = random(0, LH_size - 1);
			hero1_num = random(0, LH_size - 1);
			if (hero1_num == hero2_num)
				continue;
			if (LH->heros.at(hero1_num)->getEnemyNum())
				continue;
			if (LH->heros.at(hero2_num)->getEnemyNum())
				continue;
			if (LH->heros.at(hero1_num)->getLastEnemyNum()==hero2_num)
				continue;

		}
	}
	for (int i = 0; i < LH_size; i++)
	{

	}
}*/
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
