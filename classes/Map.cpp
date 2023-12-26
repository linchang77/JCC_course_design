#include "Map.h"
#include "cocos2d.h"
USING_NS_CC;
static int plaid_width = 100;
static int plaid_height = 80;
static float x = 1280 / 2 - plaid_width * 2.5;//���½ǲο���
static float y = 720 / 2 - plaid_height * 2.5;//���½ǲο���
bool MapData::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //������ͼ
	Background = Sprite::create("JCC.png");
    Mapline = Sprite::create("maplines.png");
    Background->setContentSize(Size(Vec2(visibleSize.width, visibleSize.height)));
    Background->setAnchorPoint(Vec2(0, 0));
    Mapline->setContentSize(Size(Vec2(visibleSize.width, visibleSize.height)));
    Mapline->setAnchorPoint(Vec2(0, 0));
    /*�տ�ʼʱMapline��ȫ͸����ֻ���϶�ʱ���ǲ�͸��*/
    Mapline->setOpacity(0);
	this->addChild(Background);
    this->addChild(Mapline);
	return true;
}
void MapData::putchequer(Node* che,int x,int y)
{
    che->setPosition(mapposition(x,y));
   // addChild(che, 0, che->name);//�����ӷŵ���������
}
Vec2 MapData::mapposition(int x, int y)
{
    float mx = this->getContentSize().width / 12;
    float my = this->getContentSize().height / 12;
    return Vec2(mx*(2*x-1), my*(2*y-1));
}
Vec2 MapData::getposition(int i, int j)
{
    return Vec2(x + (5 - i) * plaid_width, x + j * plaid_height);
}

