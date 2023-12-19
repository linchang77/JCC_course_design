#include "Heroes.h"
#include "Map.h"
#include "Battlefield.h"

USING_NS_CC;

LittleHero* s_SharedLittleHero = nullptr;

LittleHero* LittleHero::getInstance()
{
    if (!s_SharedLittleHero)
    {
        s_SharedLittleHero = new (std::nothrow) LittleHero;
        CCASSERT(s_SharedLittleHero, "FATAL: Not enough memory");
        s_SharedLittleHero->grade = 1;
    }

    return s_SharedLittleHero;
}

int LittleHero::getGrade()
{
    return grade;
}

HeroImages Hero::getImages()
{
	return { imageOnField, imageInStoreNormal, imageInStoreSelected };
}

int Hero::getCost()
{
    return cost;
};

Hero* Hero::copy(Hero* templt)
{
    Hero* cpy = new (std::nothrow) Hero;
    CCASSERT(cpy, "FATAL: Not enough memory");
    cpy->autorelease();

    cpy->body = templt->body ? Sprite::createWithSpriteFrame(templt->body->getSpriteFrame()) : nullptr;  //使用模板英雄的精灵指针创建新的精灵指针
    cpy->imageOnField = templt->imageOnField;
    cpy->imageInStoreNormal = templt->imageInStoreNormal;
    cpy->imageInStoreSelected = templt->imageInStoreSelected;
    cpy->cost = templt->cost;
    cpy->name = templt->name;
    //棋子类如果要添加数据成员，一定记得在这里也加上赋值语句（如果涉及到类，最好创建全新备份）

    return cpy;
};

bool Hero::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    return true;
};

bool Example::init()
{
    if (!Hero::init())
    {
        return false;
    }
    hero_space = Layer::create();    //创建英雄所在层
    body = Sprite::create(imageOnField);    //创建英雄
    maxhp = 100;
    realhp = 100;
    maxmp = 100;
    realmp = 100;
    range = 3;
    frequency = 2;
    imageOnField = ".png";
    imageInStoreNormal = ".png";
    imageInStoreSelected = ".png";
    movespeed = 1;
};

HeroPosition Hero::getPosition()
{
    return { position.x,position.y };
}

bool Hero::initHp()
{
    if (!init())
    {
        return false;
    }
    hp_bar = Sprite::create(".png");    //创建血条进度框
    hp_bar->setPosition();     //设置框的位置
    hero_space->addChild(hp_bar);    //加到棋子图层里面去
    hp = Sprite::create(".png");    //创建血条
    ProgressTimer* progress = ProgressTimer::create(hp);    //创建progress对象
    progress->setType(ProgressTimer::Type::BAR);    //进度条类型：条状
    progress->setPosition();    //进度条位置
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //条形进度条的起始点：（0，y）最左边，（1，y）最右边，（x，1）最上边，（x，0）最下边
    hero_space->addChild(progress);
    progress->setTag(Hp_Bar);    //做一个标记
    schedule(CC_SCHEDULE_SELECTOR(Hero::updateHp, this), 0.1f);  //刷新函数，每隔0.1秒
    return true;
};

void Hero::updateHp(float dt)
{
    auto progress = (ProgressTimer*)hero_space->getChildByTag(Hp_Bar);
    progress->setPercentage((realhp -= dt) / maxhp * 100);    //这里是百分制显示
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Hero::updateHp, this));
    }
};

bool Hero::initMp()
{
    if (!init())
    {
        return false;
    }
    mp_bar = Sprite::create(".png");    //创建血条进度框
    mp_bar->setPosition();     //设置框的位置
    hero_space->addChild(mp_bar);    //加到棋子图层里面去
    mp = Sprite::create(".png");    //创建血条
    ProgressTimer* progress = ProgressTimer::create(mp);    //创建progress对象
    progress->setType(ProgressTimer::Type::BAR);    //进度条类型：条状
    progress->setPosition();    //进度条位置
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //条形进度条的起始点：（0，y）最左边，（1，y）最右边，（x，1）最上边，（x，0）最下边
    progress->setTag(Mp_Bar);    //做一个标记
    hero_space->addChild(progress);
    schedule(CC_SCHEDULE_SELECTOR(Hero::updateHp, this), 0.1f);  //刷新函数，每隔0.1秒
    return true;
};

void Hero::updateMp(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(Mp_Bar);
    progress->setPercentage(realhp / maxhp * 100);    //这里是百分制显示
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Hero::updateMp, this));
    }
};

void Hero::Death()
{
    auto fadeout = FadeOut::create(0.5f);    //0.5s淡出消失
    body->runAction(fadeout);
    isdead = true;    //判断为死亡
};

void Hero::Move(HeroPosition destination)
{
    ismove = true;    //判断为正在移动
    float distance;    //通过坐标获取移动距离
    auto moveto = MoveTo::create(distance / movespeed, MapData::Position(position.x, position.y));   //移动
    body->runAction(moveto);
    ismove = false;    //判断为停止移动
    position.x = destination.x;
    position.y = destination.y;    //将英雄位置更新为终点位置
};

void Example::Attack(Hero* enemy)    //未完成，碰撞还需再研究，先将就用
{
    bullet = Sprite::create();
    hero_space->addChild(bullet);
    bullet->setPosition(MapData::Position(position.x, position.y));    //子弹从攻击者位置生成
    auto moveto = MoveTo::create(1.0f, MapData::Position(enemy->getPosition().x, enemy->getPosition().y);    //子弹攻击敌人位置

    counter = 0;    //记录为攻击
}