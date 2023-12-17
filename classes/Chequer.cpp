#include"Chequer.h"

USING_NS_CC;

bool Chequer::init()
{
    if (!Node::init())
    {
        return false;
    }
    chequer_body = Sprite::create("HelloWorld.png");
    this->addChild(chequer_body);

    return true;
};

bool Chequer::initHp()
{
    if (!init())
    {
        return false;
    }
    hp_bar = Sprite::create("hp_bar.png");    //创建血条进度框
    hp_bar->setPosition(visibleSize.width / 2, visibleSize.height / 2);     //设置框的位置
    chequer_space->addChild(hp_bar);    //加到棋子图层里面去
    hp = Sprite::create("hp.png");    //创建血条
    ProgressTimer* progress = ProgressTimer::create(hp);    //创建progress对象
    progress->setType(ProgressTimer::Type::BAR);    //进度条类型：条状
    progress->setPosition(visibleSize.width / 2, visibleSize.height / 2);    //进度条位置
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //条形进度条的起始点：（0，y）最左边，（1，y）最右边，（x，1）最上边，（x，0）最下边
    chequer_space->addChild(progress);
    progress->setTag(Hp_Bar);    //做一个标记
    schedule(CC_SCHEDULE_SELECTOR(Chequer::updateHp, this), 0.1f);  //刷新函数，每隔0.1秒
    return true;
};

void Chequer::updateHp(float dt)
{
    auto progress = (ProgressTimer*)chequer_space->getChildByTag(Hp_Bar);
    progress->setPercentage((realhp -= dt) / maxhp * 100);    //这里是百分制显示
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Chequer::updateHp, this));
    }
};

bool Chequer::initMp()
{
    if (!init())
    {
        return false;
    }
    mp_bar = Sprite::create("mp_bar.png");    //创建x血条进度框
    mp_bar->setPosition(0, 0);     //设置框的位置
    chequer_space->addChild(mp_bar);    //加到棋子图层里面去
    mp = Sprite::create("mp.png");    //创建血条
    ProgressTimer* progress = ProgressTimer::create(mp);    //创建progress对象
    progress->setType(ProgressTimer::Type::BAR);    //进度条类型：条状
    progress->setPosition(0, 0);    //进度条位置
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //条形进度条的起始点：（0，y）最左边，（1，y）最右边，（x，1）最上边，（x，0）最下边
    progress->setTag(Mp_Bar);    //做一个标记
    chequer_space->addChild(progress);
    schedule(CC_SCHEDULE_SELECTOR(Chequer::updateHp, this), 0.1f);  //刷新函数，每隔0.1秒
    return true;
};

void Chequer::updateMp(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(Mp_Bar);
    progress->setPercentage(realhp / maxhp * 100);    //这里是百分制显示
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Chequer::updateMp, this));
    }
};



