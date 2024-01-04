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

static prepare* prepare1=NULL;
#endif