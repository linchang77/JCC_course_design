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
void time_label::update_time(int x)
{
	num = x;
	Showtime->setString(StringUtils::toString(num));
	return;
}


bool fight::init()
{
	if (!Layer::init())
	{
		return false;
	}
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
			}
		}
	}
	is_my_hero = 0;
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
	{
		return 1;
	}
	return 0;
}
int fight::solve_distance(Hero *Hero1,Hero *Hero2)
{
	HeroPosition h1, h2;
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
	if (x < 8 && x >= 0 && y < 4 && y >= 0)
		return 1;
	return 0;
}

HeroPosition fight::bfs()
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
					continue;
				HeroPosition h0;
				h0.x = tmp->place.x + i;
				h0.y = tmp->place.y + j;
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
	}
	HeroPosition h0;
	h0.x = h0.y = -1;
	return h0;
}

bool fight::Find_way(Hero* Hero1,Hero* Hero2)
{
	start = Hero1->getPosition();
	end = Hero2->getPosition();
	HeroPosition h0 = bfs();
	if (h0.x == h0.y && h0.x == -1)
	{}//故意留空，不是写错
	else
	{
		/*
		if(!Hero1->getIsattack())
		Hero1->Move(h0);
		
		return 1;
	}
	return 0;
}
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
