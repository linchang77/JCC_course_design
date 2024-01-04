#ifndef PREPARE_H
#define PREPARE_H
#include "cocos2d.h"
#include"CCVector.h"
#include "Heroes.h"
#include"Map.h"
#include"httpTransmission.h"
#include"fight.h"
USING_NS_CC;
class prepare:public Layer
{
private:
	int big_turn = 1;
	int small_turn = 1;
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

static prepare* prepare1=NULL;
#endif