#include"prepare.h"

bool prepare::init()
{
	if (!Layer::init())
	{
		return 0;
	}
	
	schedule(CC_SCHEDULE_SELECTOR(prepare::prepare_base));
	return true;
}
void prepare::threeLabelsInit()
{
	time_l1 = time_label::getInstance();
	time_l1->update_time(last_time - MaxTime / 2);
	this->addChild(time_l1);

	turn_l1 = turn_label::getInstance();
	turn_l1->update_turns(small_turn, big_turn);
	this->addChild(turn_l1);

	Isfight_l1 = Isfight_label::getInstance();
	Isfight_l1->update_Isfight(0);
	this->addChild(Isfight_l1);
}
prepare* prepare::getInstance()
{
	if (!prepare1)
	{
		prepare1 = new (std::nothrow)prepare;
		prepare1->init();
	}
	return prepare1;
}
void prepare::clearInstance()
{
	if (prepare1)
	{
		delete prepare1;
	}
	prepare1 = NULL;
}
void prepare::getAllHeroes()
{
	auto LH = LHcontroler::getInstance();
	auto myLittleHero = LH->getMyLittleHero();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			auto thishero = myLittleHero->Fightfield[i][j];
			if (thishero != nullptr)
			{
				HeroPosition h1;
				h1.x = i; 
				h1.y = j;
				thishero->setHeroPosition(h1);
			}
		}
	}
}
void prepare::removeAllLabels()
{
	time_l1->removeFromParent();
	turn_l1->removeFromParent();
	Isfight_l1->removeFromParent();
	time_l1->clearInstance();
	turn_l1->clearInstance();
	Isfight_l1->clearInstance();
}
void prepare::prepare_base(float dt)
{
	timef += dt;
	if ((last_time == 0) && prepare_end == 1) //开始阶段
	{ 
		threeLabelsInit();  //三个标签的初始化

		this->getParent()->reorderChild(this, 2);

		Isfight_l1->update_Isfight(0);  //修改战斗状态为：准备
		prepare_end = 0;  //开始准备阶段
		last_time = MaxTime;  //将剩余时间拉满
		time_l1->update_time(last_time - MaxTime / 2 - 1);  //计时器
	}
	
	if (last_time == MaxTime/2 + 1&&prepare_end==0)  //结束阶段
	{
		getAllHeroes();  //暂时使用的给棋子赋值位置的函数，最后删掉
		
		removeAllLabels();  //将它与所有标签的连接remove掉。

		this->getParent()->reorderChild(this, -1);  //将prepare扔到底层。
		
		small_turn++;  //计算轮次
		if (small_turn > 3)
			small_turn = 1,
			big_turn++;
		prepare_end = 1;  //结束准备阶段
	}
	if (timef >= 1)
	{
		timef--;
		last_time--;
		if(last_time > MaxTime/2 + 1)
		time_l1->update_time(last_time - MaxTime/2 - 1);  //计时器
	}
	return;
}