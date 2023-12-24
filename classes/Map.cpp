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
bool MapData::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void MapData::onTouchEnded(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    auto s = this->getChildByName("littlehero1");//��ȡССӢ�۵Ľ��ָ��
    s->stopAllActions();
   
    float o = location.x - s->getPosition().x;
    float a = location.y - s->getPosition().y;
    float at = (float)CC_RADIANS_TO_DEGREES(atanf(o / a));
     s->runAction(MoveTo::create(1, Vec2(location.x, location.y)));
    if (a < 0)
    {
        if (o < 0)
            at = 180 + fabs(at);
        else
            at = 180 - fabs(at);
    }
    //s->runAction(RotateTo::create(1, at));
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

