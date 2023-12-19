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

    cpy->body = templt->body ? Sprite::createWithSpriteFrame(templt->body->getSpriteFrame()) : nullptr;  //ʹ��ģ��Ӣ�۵ľ���ָ�봴���µľ���ָ��
    cpy->imageOnField = templt->imageOnField;
    cpy->imageInStoreNormal = templt->imageInStoreNormal;
    cpy->imageInStoreSelected = templt->imageInStoreSelected;
    cpy->cost = templt->cost;
    cpy->name = templt->name;
    //���������Ҫ������ݳ�Ա��һ���ǵ�������Ҳ���ϸ�ֵ��䣨����漰���࣬��ô���ȫ�±��ݣ�

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
    hero_space = Layer::create();    //����Ӣ�����ڲ�
    body = Sprite::create(imageOnField);    //����Ӣ��
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
    hp_bar = Sprite::create(".png");    //����Ѫ�����ȿ�
    hp_bar->setPosition();     //���ÿ��λ��
    hero_space->addChild(hp_bar);    //�ӵ�����ͼ������ȥ
    hp = Sprite::create(".png");    //����Ѫ��
    ProgressTimer* progress = ProgressTimer::create(hp);    //����progress����
    progress->setType(ProgressTimer::Type::BAR);    //���������ͣ���״
    progress->setPosition();    //������λ��
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //���ν���������ʼ�㣺��0��y������ߣ���1��y�����ұߣ���x��1�����ϱߣ���x��0�����±�
    hero_space->addChild(progress);
    progress->setTag(Hp_Bar);    //��һ�����
    schedule(CC_SCHEDULE_SELECTOR(Hero::updateHp, this), 0.1f);  //ˢ�º�����ÿ��0.1��
    return true;
};

void Hero::updateHp(float dt)
{
    auto progress = (ProgressTimer*)hero_space->getChildByTag(Hp_Bar);
    progress->setPercentage((realhp -= dt) / maxhp * 100);    //�����ǰٷ�����ʾ
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
    mp_bar = Sprite::create(".png");    //����Ѫ�����ȿ�
    mp_bar->setPosition();     //���ÿ��λ��
    hero_space->addChild(mp_bar);    //�ӵ�����ͼ������ȥ
    mp = Sprite::create(".png");    //����Ѫ��
    ProgressTimer* progress = ProgressTimer::create(mp);    //����progress����
    progress->setType(ProgressTimer::Type::BAR);    //���������ͣ���״
    progress->setPosition();    //������λ��
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //���ν���������ʼ�㣺��0��y������ߣ���1��y�����ұߣ���x��1�����ϱߣ���x��0�����±�
    progress->setTag(Mp_Bar);    //��һ�����
    hero_space->addChild(progress);
    schedule(CC_SCHEDULE_SELECTOR(Hero::updateHp, this), 0.1f);  //ˢ�º�����ÿ��0.1��
    return true;
};

void Hero::updateMp(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(Mp_Bar);
    progress->setPercentage(realhp / maxhp * 100);    //�����ǰٷ�����ʾ
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Hero::updateMp, this));
    }
};

void Hero::Death()
{
    auto fadeout = FadeOut::create(0.5f);    //0.5s������ʧ
    body->runAction(fadeout);
    isdead = true;    //�ж�Ϊ����
};

void Hero::Move(HeroPosition destination)
{
    ismove = true;    //�ж�Ϊ�����ƶ�
    float distance;    //ͨ�������ȡ�ƶ�����
    auto moveto = MoveTo::create(distance / movespeed, MapData::Position(position.x, position.y));   //�ƶ�
    body->runAction(moveto);
    ismove = false;    //�ж�Ϊֹͣ�ƶ�
    position.x = destination.x;
    position.y = destination.y;    //��Ӣ��λ�ø���Ϊ�յ�λ��
};

void Example::Attack(Hero* enemy)    //δ��ɣ���ײ�������о����Ƚ�����
{
    bullet = Sprite::create();
    hero_space->addChild(bullet);
    bullet->setPosition(MapData::Position(position.x, position.y));    //�ӵ��ӹ�����λ������
    auto moveto = MoveTo::create(1.0f, MapData::Position(enemy->getPosition().x, enemy->getPosition().y);    //�ӵ���������λ��

    counter = 0;    //��¼Ϊ����
}