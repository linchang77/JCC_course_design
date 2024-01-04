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
	auto LH = LHcontroler::getInstance();
	if (LH->Gameover)
	{
		return;
	}
	if ((last_time == 0) && prepare_end == 1) //��ʼ�׶�
	{
		//�����̵갴ť
		dynamic_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentStore()->Refresh();
		Node* menu;
		if ((menu = Director::getInstance()->getRunningScene()->getChildByName("menu")) != nullptr)
			dynamic_cast<MenuItem*>(menu->getChildByName("storeItem"))->setEnabled(true);
		threeLabelsInit();  //������ǩ�ĳ�ʼ��
		this->getParent()->reorderChild(this, 2);
		Isfight_l1->update_Isfight(0);  //�޸�ս��״̬Ϊ��׼��
		prepare_end = 0;  //��ʼ׼���׶�
		last_time = MaxTime;  //��ʣ��ʱ������
		time_l1->update_time(last_time - MaxTime / 2 - 1);  //��ʱ��
	}
	
	if (last_time == MaxTime/2 + 1&&prepare_end==0)  //�����׶�
	{
		getAllHeroes();  //ʹ�õĸ����Ӹ�ֵλ�õĺ���
		
		removeAllLabels();  //���������б�ǩ������remove����

		this->getParent()->reorderChild(this, -1);  //��prepare�ӵ��ײ㡣
		auto battlefield = dynamic_cast<Battlefield*>(Director::getInstance()->getRunningScene());
		auto store = battlefield->getCurrentStore();
		auto storeItem = dynamic_cast<MenuItem*>(battlefield->getChildByName("menu")->getChildByName("storeItem"));
		if (store->getStatus())     //�ر��̵�
		{
			store->retain();
			store->removeFromParent();
			store->reverseStatus();
		}
		storeItem->setEnabled(false);	//�����̵갴ť
		if (LH->GetStatus() == ONLINE)
		{
			auto transmission = httpTransmission::getInstance();
			transmission->upload(dynamic_cast<Battlefield*>(Director::getInstance()->getRunningScene()));
		}
		//����˹ѡ��ͼ�㴦��
		Node* hextech;
		if ((hextech = Director::getInstance()->getRunningScene()->getChildByName("hextechlayer")) != nullptr)	//�����δѡ��
		{
			//����Ĭ��ѡ���Ƴ�ͼ��
			auto littlehero = LH->getMyLittleHero();
			littlehero->setHextechStatus(MONEY);
			littlehero->update_gold(15);
			littlehero->set_message("...");
			hextech->removeFromParent();
		}

		small_turn++;  //�����ִ�
		if (small_turn > 3)
			small_turn = 1,
			big_turn++;
		prepare_end = 1;  //����׼���׶�
	}
	if (timef >= 1)
	{
		timef--;
		last_time--;
		if(last_time > MaxTime/2 + 1)
		time_l1->update_time(last_time - MaxTime/2 - 1);  //��ʱ��
	}
	return;
}