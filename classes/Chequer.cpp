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
    hp_bar = Sprite::create("hp_bar.png");    //����Ѫ�����ȿ�
    hp_bar->setPosition(visibleSize.width / 2, visibleSize.height / 2);     //���ÿ��λ��
    chequer_space->addChild(hp_bar);    //�ӵ�����ͼ������ȥ
    hp = Sprite::create("hp.png");    //����Ѫ��
    ProgressTimer* progress = ProgressTimer::create(hp);    //����progress����
    progress->setType(ProgressTimer::Type::BAR);    //���������ͣ���״
    progress->setPosition(visibleSize.width / 2, visibleSize.height / 2);    //������λ��
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //���ν���������ʼ�㣺��0��y������ߣ���1��y�����ұߣ���x��1�����ϱߣ���x��0�����±�
    chequer_space->addChild(progress);
    progress->setTag(Hp_Bar);    //��һ�����
    schedule(CC_SCHEDULE_SELECTOR(Chequer::updateHp, this), 0.1f);  //ˢ�º�����ÿ��0.1��
    return true;
};

void Chequer::updateHp(float dt)
{
    auto progress = (ProgressTimer*)chequer_space->getChildByTag(Hp_Bar);
    progress->setPercentage((realhp -= dt) / maxhp * 100);    //�����ǰٷ�����ʾ
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
    mp_bar = Sprite::create("mp_bar.png");    //����xѪ�����ȿ�
    mp_bar->setPosition(0, 0);     //���ÿ��λ��
    chequer_space->addChild(mp_bar);    //�ӵ�����ͼ������ȥ
    mp = Sprite::create("mp.png");    //����Ѫ��
    ProgressTimer* progress = ProgressTimer::create(mp);    //����progress����
    progress->setType(ProgressTimer::Type::BAR);    //���������ͣ���״
    progress->setPosition(0, 0);    //������λ��
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //���ν���������ʼ�㣺��0��y������ߣ���1��y�����ұߣ���x��1�����ϱߣ���x��0�����±�
    progress->setTag(Mp_Bar);    //��һ�����
    chequer_space->addChild(progress);
    schedule(CC_SCHEDULE_SELECTOR(Chequer::updateHp, this), 0.1f);  //ˢ�º�����ÿ��0.1��
    return true;
};

void Chequer::updateMp(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(Mp_Bar);
    progress->setPercentage(realhp / maxhp * 100);    //�����ǰٷ�����ʾ
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Chequer::updateMp, this));
    }
};



