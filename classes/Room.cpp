#include "Room.h"
#include "httpTransmission.h"
#include "GeneralCreator.h"
USING_NS_CC;
using namespace network;

Scene* Room::createScene()
{
	return Room::create();
}

bool Room::init()
{
	if (!Scene::init())
		return false;

	//���뷿���
	httpTransmission::getInstance()->joinRoom(this);

	//��Ⱦ����
	auto background = GCreator::getInstance()->createSprite("RoomBackground.png", 0.0f, 0.0f, 0.0f, 0.0f);
	background->setContentSize(Director::getInstance()->getVisibleSize());
	addChild(background, -1);

	//������ѯ������
	schedule(CC_CALLBACK_1(Room::poll, this), 0.1f, "poll");

	return true;
}

void Room::intoRoomCallback(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
	//�������ظ�����
	std::vector<char>* buffer = response->getResponseData();
	long statusCode = response->getResponseCode();
	buffer->push_back('\0');

	//������źͷ����
	auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
	mySeq = (*buffer)[0] - '0';
	room_num = buffer->data() + 2;
	littlehero->setRoomParam(mySeq, room_num);
	log("%s", buffer->data());

	//��Ⱦ��ǩ
	auto label = GCreator::getInstance()->createLabel("You've joined room " + room_num, "fonts/Marker Felt.ttf", 18.0f, Director::getInstance()->getVisibleSize().width * 0.5f, Director::getInstance()->getVisibleSize().height * 0.9f);
	label->setName("roomMain");
	addChild(label, 0);
}

void Room::poll(float dt)
{
	httpTransmission::getInstance()->seekRoom(this);
}

void Room::pollCallback(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
	//�������ظ�����
	std::vector<char>* buffer = response->getResponseData();
	long statusCode = response->getResponseCode();
	buffer->push_back('\0');

	//��ȡ����ǩ
	auto main = getChildByName("roomMain");

	//�жϷ����Ƿ�����
	if ((*buffer)[0] == '2')
	{
		log("The room is full now. Ready to start the game.");
		auto label = GCreator::getInstance()->createLabel("2 / 2 Ready to start in 1s", "fonts/Marker Felt.ttf", 16.0f, main->getPositionX(), main->getPositionY() + main->getContentSize().height);
		addChild(label);
		scheduleOnce(CC_CALLBACK_1(Room::intoBattlefieldCallback, this), 1.0f, "intoBattlefield");
		unschedule("poll");
	}
	else
	{
		log("Still need waiting!");
		auto label = GCreator::getInstance()->createLabel("1 / 2 Pending...", "fonts/Marker Felt.ttf", 16.0f, main->getPositionX(), main->getPositionY() + main->getContentSize().height);
		addChild(label);
	}
}

void Room::intoBattlefieldCallback(float dt)
{
	auto battlefield = Battlefield::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(battlefield);
}
