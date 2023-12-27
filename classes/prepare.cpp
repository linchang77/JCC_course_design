#include"prepare.h"

bool prepare::init()
{
	if (!Layer::init())
	{
		return 0;
	}
	
	time_l1=time_label::getInstance();
	time_l1->update_time(last_time-MaxTime/2);
	this->addChild(time_l1);
    
	turn_l1 = turn_label::getInstance();
	turn_l1->update_turns(small_turn, big_turn);
	this->addChild(turn_l1);

	Isfight_l1=Isfight_label::getInstance();
	Isfight_l1->update_Isfight(0);
	this->addChild(Isfight_l1);
	
	schedule(CC_SCHEDULE_SELECTOR(prepare::prepare_base));
	return true;
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
void prepare::prepare_base(float dt)
{
	timef += dt;
	if (last_time == 0)
	{
		Isfight_l1->update_Isfight(0);
		prepare_end = 0;
		last_time = MaxTime;
		time_l1->update_time(last_time - MaxTime / 2);
	}
	if (last_time == MaxTime/2&&prepare_end!=0)
	{
		small_turn++;
		if (small_turn > 7)
			small_turn = 1,
			big_turn++;
		if (big_turn == 1 && small_turn > 3)
			small_turn = 1,
			big_turn++;
		prepare_end = 1;
	}
	if (timef >= 1)
	{
		timef--;
		last_time--;
		if(last_time > MaxTime/2)
		time_l1->update_time(last_time - MaxTime/2);
	}
	return;
}