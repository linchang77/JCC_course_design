#include "Map.h"
#include "cocos2d.h"
USING_NS_CC;
static int plaid_width = 100;
static int plaid_height = 80;
static float x = 1280 / 2 - plaid_width * 2.5;//左下角参考点
static float y = 720 / 2 - plaid_height * 2.5;//左下角参考点
bool MapData::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //产生地图
	background = Sprite::create("JCC.png");
    background->setContentSize(Size(Vec2(visibleSize.width, visibleSize.height)));
    background->setAnchorPoint(Vec2(0, 0));
	this->addChild(background);
    //产生监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MapData::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MapData::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//将监听器加入到场景图优先级中，使其能够接收触摸事件。
    //加入小小英雄
    auto Gros = Sprite::create("littlehero1.png");
    Gros->runAction(JumpTo::create(4, Vec2(300, 48), 100, 4));
    this->addChild(Gros, 0, "littlehero1");
	return true;
}
bool MapData::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void MapData::onTouchEnded(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    auto s = this->getChildByName("littlehero1");//获取小小英雄的结点指针
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
   // addChild(che, 0, che->name);//将棋子放到格子里面
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

