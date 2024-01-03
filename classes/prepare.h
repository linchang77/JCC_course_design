#ifndef PREPARE_H
#define PREPARE_H
#include "cocos2d.h"
#include"CCVector.h"
#include "Heroes.h"
#include"Map.h"
<<<<<<< HEAD
#include"httpTransmission.h"
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
#include"fight.h"
USING_NS_CC;
class prepare:public Layer
{
private:
	int big_turn = 1;
	int small_turn = 1;
<<<<<<< HEAD
	int last_time = 0;
	float timef = 0;
	bool prepare_end = 1;
	time_label* time_l1; //时间标签
	Isfight_label* Isfight_l1; //是否战斗阶段标签
	turn_label* turn_l1; //轮次标签
public:
	CREATE_FUNC(prepare);
	virtual bool init();  
	void removeAllLabels();
	static prepare* getInstance();
	virtual void prepare_base(float dt);  //调度器，准备阶段核心
	void threeLabelsInit();  //初始化标签
	void getAllHeroes();  //最后删除
	void clearInstance();  //清除单例
};

=======
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
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
static prepare* prepare1=NULL;
#endif