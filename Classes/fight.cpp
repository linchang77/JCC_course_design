#include"fight.h"

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
	ShowIsfight->setTag(3);
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
void Isfight_label::clearInstance()
{
	if (Isfight_l)
		delete Isfight_l;
	Isfight_l = nullptr;
}

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
void turn_label::clearInstance()
{
	if (turn_l)
		delete turn_l;
	turn_l = nullptr;
}
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
void time_label::clearInstance()
{
	if (time_l)
		delete time_l;
	time_l = nullptr;
}
void time_label::update_time(int x)
{
	num = x;
	Showtime->setString(StringUtils::toString(num));
	return;
}

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
bool fight::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	schedule(CC_SCHEDULE_SELECTOR(fight::Fight_base));
	return true;
}

bool fight::isfunction(Hero* e)
{
	if (e->IsDying())
		return 1;
	if (e->IsMove())
		return 1;
	if (e->IsAttack())
		return 1;
	return 0;
}

void fight::threeLabelsInit()
{
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
	if (My_Hero_use.empty())
	{
		int SIZE = Enemy_Hero_use.size();
		int hp_change = big_turn * SIZE * 2;
		MyLittleHero->update_Hp(hp_change);
	}
	MyLittleHero->update_gold();
}
void fight::Fight_base(float dt)
{
	is_my_hero = 1;
	timef += dt;
	if (last_time == 1 && is_Fight == 1)
	{
		giveLittleHeroDamage();
		this->removeAllChildren();
		makeallVectorEmpty();
		removeAllLabels();
		small_turn++;
		if (small_turn > 3)
			small_turn = 1,
			big_turn++;	
		last_time=MaxTime + 1;
		is_Fight = 0;
	}
	if (timef >= 1)
	{
		timef--;
		last_time--;
	}
	if (last_time > MaxTime/2)
	{
		return;
	}
	else if(last_time == MaxTime/2 && is_Fight==0)
	{
		is_Fight = 1;
		threeLabelsInit();
		MatchAI();
		pullHeros();
		putHeros();
		Map1init();
	}
	
	time_l1->update_time(last_time);
	int SIZE = My_Hero_use.size();
	solveAllDead();
	
	for (auto &thisHero : My_Hero_use)
	{
		if (thisHero->getAttackCounter() < 1.0f / (thisHero->getFrequency()))
			thisHero->ChangeAttackCounter(thisHero->getAttackCounter() + dt);
		if (isfunction(thisHero))
			continue;//正在执行动画，不可进行其它操作。
		if (thisHero->getRealHp() <= 0 && !thisHero->IsDead())
		{//发现没血，开始执行死亡动画
			thisHero->Death();
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
			if (thisHero->getAttackCounter()>=1.0f/(thisHero->getFrequency()))
			{
				thisHero->Attack();
				thisHero->ChangeAttackCounter(thisHero->getAttackCounter() - 1.0f / (thisHero->getFrequency()));
			}
		}
	}
	is_my_hero = 0;
	for (auto& thisHero : Enemy_Hero_use)
	{
		if (thisHero->getAttackCounter() < 1.0f / (thisHero->getFrequency()))
			thisHero->ChangeAttackCounter(thisHero->getAttackCounter() + dt);
		if (isfunction(thisHero))
			continue;//正在执行动画，不可进行其它操作。
		if (thisHero->getRealHp() <= 0 && !thisHero->IsDead())
		{//发现没血，开始执行死亡动画
			thisHero->Death();
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
	for (int i = 0; i < 3; i++)
	{
		x1=random(4, 7);
		y1=random(0, 3);
		auto LH = LHcontroler::getInstance();
		enemyP.x = x1;
		enemyP.y = y1;
		if (Map1[x1][y1] == 0)
		{
			auto newHero = Golem::create();
			newHero->setHeroPosition(enemyP);
			newHero->getSpriteReady();
			newHero->setPosition(LH->heros.at(0)->getmidposition(enemyP.x, enemyP.y));
			newHero->setScale(-1, 1);
			newHero->ChangeFaceRight(0);
			this->addChild(newHero);
			Enemy_Hero_use.pushBack(newHero);
			Map1[x1][y1] = 1;
		}
		else
			i--;
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
			auto fieldhero = littlehero1->Fightfield[i][j];
			if (fieldhero != nullptr)
			{
				auto herocopy = Hero::copy(fieldhero);
				Vec2 heroposition = littlehero1->getmidposition(herocopy->getHeroPosition().x, herocopy->getHeroPosition().y);
				herocopy->setPosition(heroposition);
				this->addChild(herocopy);
				My_Hero_use.pushBack(herocopy);
			}
		}
	}
	return;
}
void fight::somebodydead(Hero* e1,bool isMy)
{//一个人死后要干的事情：先释放当前位置的格子，然后再将所有锁定该角色的人锁定目标清除，最后从容器中移除该角色。
	HeroPosition h1 = e1->getHeroPosition();
	Map1[h1.x][h1.y] = 0;
	if (isMy == 1)
	{
		for (auto& thishero : Enemy_Hero_use)
		{
			if (thishero->getEnemy() == e1)
			{
				thishero->ChooseEnemy(NULL);
			}
		}
		My_Hero_use.erase(My_Hero_use.find(e1));
	}
	if (isMy == 0)
	{
		for (auto& thishero : My_Hero_use)
		{
			if (thishero->getEnemy() == e1)
			{
				thishero->ChooseEnemy(NULL);
			}
		}
		Enemy_Hero_use.erase(Enemy_Hero_use.find(e1));
	}
}
bool fight::Hasenemy(Hero *Hero1,Hero*Hero2)
{
	if (solve_distance(Hero1, Hero2) <= Hero1->getRange())
	{
		return 1;
	}
	return 0;
}
int fight::solve_distance(Hero *Hero1,Hero *Hero2)
{
	HeroPosition h1, h2;
	h1 = Hero1->getHeroPosition();
	h2 = Hero2->getHeroPosition();
	return abs(h1.x - h2.x) + abs(h1.y - h2.y);
}
bool fight::isFace(Hero *Hero1,Hero* Hero2)
{
	if (Hero1->getHeroPosition().y == Hero2->getHeroPosition().y)
		return 1;
	else
		return 0;
}
bool fight::Findenemy(Hero *Hero1)
{
	int min_distance = 100;
	Hero* enemy_hero=NULL;
	if (is_my_hero == 1)
		for (auto& thishero : Enemy_Hero_use)
		{
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
	else
		for (auto& thishero : My_Hero_use)
		{
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
			Toturn(Hero1,enemy_hero);
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
			Toturn(Hero1, enemy_hero);
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
{
	if (x < 8 && x >= 0 && y < 4 && y >= 0)
		return 1;
	return 0;
}
bool fight::isFace(HeroPosition HPT1, HeroPosition HPT2)
{
	if (HPT1.y == HPT2.y)
		return 1;
	else return 0;
}
void fight::Toturn(Hero* Hero1, Hero* Hero2)
{
	if (Hero1->getHeroPosition().x > Hero2->getHeroPosition().x && Hero1->getFaceRight() == 1)
	{
		Hero1->ChangeFaceRight(0);
		Hero1->setScale(-1, 1);
	}
	if (Hero1->getHeroPosition().x < Hero2->getHeroPosition().x && Hero1->getFaceRight() == 0)
	{
		Hero1->ChangeFaceRight(1);
		Hero1->setScale(1, 1);
	}
}
HeroPosition fight::bfs(Hero *WantFind)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			vis[i][j] = 0;
			if (Map1[i][j] == 1)
				vis[i][j] = 1;
		}
	}
	que.pushBack(new way_Node(start,NULL));
	while (!que.empty())
	{
		way_Node* tmp = que.front();
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (abs(i) + abs(j) != 1)
					continue;
				HeroPosition h0;
				h0.x = tmp->place.x + i;
				h0.y = tmp->place.y + j;
				if (!trueposition(h0.x,h0.y))
					continue;
				if (vis[h0.x][h0.y])
					continue;
				vis[h0.x][h0.y] = 1;
				que.pushBack(new way_Node(h0, tmp));
				if (is_my_hero == 1)
				{//我方攻击判定（包括近战和远程）
					for (auto& thishero : Enemy_Hero_use)
					{
						HeroPosition EnemyPosition=thishero->getHeroPosition();
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
				if (is_my_hero == 0)
				{//敌方攻击判定（近战远程）
					for (auto& thishero : My_Hero_use)
					{
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
		que.erase(0);
	}
	HeroPosition h0;
	h0.x = h0.y = -1;
	return h0;
}

bool fight::Find_way(Hero* Hero1)
{
	start = Hero1->getHeroPosition();
	HeroPosition h0 = bfs(Hero1);
	
	if (h0.x == h0.y && h0.x == -1)
	{}//故意留空，不是写错
	else
	{
		if (!isfunction(Hero1))
		{
			Map1[start.x][start.y] = 0;
			Map1[h0.x][h0.y] = 1;
			Hero1->Move(h0);
		}
		return 1;
	}
	return 0;
}

void fight::Match()
{
	auto LH = LHcontroler::getInstance();
	int LH_size = LH->heros.size();
	int hero1_num, hero2_num;
	for (int i = 1; i <= LH_size / 2 - 1; i++)
	{
		hero1_num = -1; hero2_num = -1;
		while (1)
		{
			hero2_num = random(0, LH_size - 1);
			hero1_num = random(0, LH_size - 1);
			if (hero1_num == hero2_num)
				continue;
			if (LH->heros.at(hero1_num)->getEnemyNum()>=0)
				continue;
			if (LH->heros.at(hero2_num)->getEnemyNum()>=0)
				continue;
			if (LH_size>=3 && LH->heros.at(hero1_num)->getLastEnemyNum()==hero2_num)
				continue;
			LH->heros.at(hero1_num)->chooseEnemyNum(hero2_num);
			LH->heros.at(hero2_num)->chooseEnemyNum(hero1_num);
		}
	}
	hero1_num = hero2_num = -1;
	for (auto &e : LH->heros)
	{
		if (e->getEnemyNum()==-1 && hero1_num == -1)
			hero1_num = e->getNum();
		else if (e->getEnemyNum()==-1)
			hero2_num = e->getNum();
	}
	if (hero1_num!=-1 && hero2_num == -1)
	{
		for (int i = 0; i < LH_size; i++)
		{
			if (hero1_num == i)
				continue;
			if (LH->heros.at(hero1_num)->getLastEnemyNum() == i)
				continue;
			LH->heros.at(hero1_num)->chooseEnemyNum(i);
		}
	}
}
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
		if (LH_size >= 3 && enemy_num == LH->heros.at(my_number)->getLastEnemyNum())
			continue;
		LH->heros.at(my_number)->chooseEnemyNum(enemy_num);
		break;
	}
}