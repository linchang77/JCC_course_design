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
	time_label* time_l1; //ʱ���ǩ
	Isfight_label* Isfight_l1; //�Ƿ�ս���׶α�ǩ
	turn_label* turn_l1; //�ִα�ǩ
public:
	CREATE_FUNC(prepare);
	virtual bool init();  
	void removeAllLabels();
	static prepare* getInstance();
	virtual void prepare_base(float dt);  //��������׼���׶κ���
	void threeLabelsInit();  //��ʼ����ǩ
	void getAllHeroes();  //���ɾ��
	void clearInstance();  //�������
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