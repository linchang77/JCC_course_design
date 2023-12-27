#ifndef PREPARE_H
#define PREPARE_H
#include "cocos2d.h"
#include"CCVector.h"
#include "Heroes.h"
#include"Map.h"
#include"fight.h"
USING_NS_CC;
class prepare:public Layer
{
private:
	int big_turn = 1;
	int small_turn = 1;
	int last_time = MaxTime;
	Vector<Hero*> heros;
	float timef = 0;
	int prepare_end = 0;
	time_label* time_l1;
	Isfight_label* Isfight_l1;
	turn_label* turn_l1;
public:
	CREATE_FUNC(prepare);
	virtual bool init();
	static prepare* getInstance();
	virtual void prepare_base(float dt);
};
static prepare* prepare1=NULL;
#endif