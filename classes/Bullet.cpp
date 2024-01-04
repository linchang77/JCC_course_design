#include "Heroes.h"


USING_NS_CC;

void Bullet::SetStar(int s) {}

bool Bullet::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
};

void Bullet::updateFly(float dt)
{
    this->setPosition(this->getPosition() + speed * 0.005f);
    if (((this->getPosition().x - target->getPosition().x) * (this->getPosition().x - target->getPosition().x) + (this->getPosition().y - target->getPosition().y) * (this->getPosition().y - target->getPosition().y)) < 2000.0f)
    {
        //扣血在这里
        if (target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeRealMp(target->getRealMp() + target->getHurtMp());    //敌人受击回蓝
        }
        if (owner != nullptr && target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeRealHp(target->getRealHp() - owner->getDamage());   //敌人受击掉血
        }
        body->removeFromParent();
        this->unschedule(CC_SCHEDULE_SELECTOR(Bullet::updateFly));
    }
};

void Bullet::setDirection()
{
    Vec2 a(target->getPosition().x - this->getPosition().x, target->getPosition().y - this->getPosition().y);
    float angle = a.getAngle();
    float deg = CC_RADIANS_TO_DEGREES(angle);
    this->setRotation(this->getRotation() - deg);
};

bool Arrow::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    body = Sprite::create("Arrow.png");
    this->addChild(body);
    this->setScale(0.5f);
    return true;
};

bool Archer_Ultimate::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    return true;
};

void Archer_Ultimate::updateFly(float dt)
{
    auto ultimateDelay = DelayTime::create(0.05f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    this->setPosition(this->getPosition() + speed * 0.025f);
    if (((this->getPosition().x - target->getPosition().x) * (this->getPosition().x - target->getPosition().x) + (this->getPosition().y - target->getPosition().y) * (this->getPosition().y - target->getPosition().y)) < 2000.0f)
    {
        //扣血在这里
        
        if (target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeIsVertigo(1);
            target->ChangeRealMp(target->getRealMp() + target->getHurtMp());    //敌人受击回蓝*/
        }
        if (owner && target != nullptr && target->getRealHp() > 0)
            target->ChangeRealHp(target->getRealHp() - owner->getDamage() * 3);   //敌人受击掉血
        body->removeFromParent();
        this->unschedule(CC_SCHEDULE_SELECTOR(Archer_Ultimate::updateFly));
    }
    static int counter = 0;
    char arrowName[100] = { 0 };
    sprintf(arrowName, "Archer_Ultimate_Arrow (%d).png", counter / 3 + 1);    //用counter调整动画效果
    body = Sprite::create(arrowName);
    this->addChild(body);
    body->setScale(0.5f);
    body->runAction(Sequence::create(ultimateDelay, ultimateDisappear, nullptr));
    if (counter == 8)
    {
        counter = 0;
    }
    else
    {
        counter++;
    }
};

bool Effect::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    return true;
};

void Effect::SetStar(int s)
{
    star = s;
    body = Sprite::create("Effect_0" + StringUtils::toString(star) + ".png");
    this->addChild(body);
}

void Effect::updateFly(float dt)
{
    
    if (((this->getPosition().x - target->getPosition().x) * (this->getPosition().x - target->getPosition().x) + (this->getPosition().y - target->getPosition().y) * (this->getPosition().y - target->getPosition().y)) < 2000.0f)
    {
        //扣血在这里
        if (target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeRealMp(target->getRealMp() + target->getHurtMp());    //敌人受击回蓝*/
        }
        if (owner != nullptr && target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeRealHp(target->getRealHp() - owner->getDamage());   //敌人受击掉血
        }
        body->removeFromParent();
        this->unschedule(CC_SCHEDULE_SELECTOR(Effect::updateFly));
    }
    this->setPosition(this->getPosition() + speed * 0.005f);
    float deg = 2.0f;
    this->setRotation(this->getRotation() - deg);
};

bool Curse::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    body = Sprite::create("Curse.png");
    this->addChild(body);
    this->setScale(0.25f);
    return true;
};

void Curse::updateFly(float dt)
{
    if (((this->getPosition().x - target->getPosition().x) * (this->getPosition().x - target->getPosition().x) + (this->getPosition().y - target->getPosition().y) * (this->getPosition().y - target->getPosition().y)) < 2000.0f)
    {
        //扣血在这里
        if (target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeRealMp(target->getRealMp() + target->getHurtMp());    //敌人受击回蓝*/
        }
        if (owner != nullptr && target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeRealHp(target->getRealHp() - owner->getDamage());   //敌人受击掉血
        }
        body->removeFromParent();
        this->unschedule(CC_SCHEDULE_SELECTOR(Curse::updateFly));
    }
    this->setPosition(this->getPosition() + speed * 0.005f);
    float deg = 2.0f;
    this->setRotation(this->getRotation() - deg);
};

bool Heal::init()
{
    if (!Bullet::init())
    {
        return false;
    }
    return true;
};

void Heal::SetStar(int s)
{
    star = s;
    body = Sprite::create("Heal_0" + StringUtils::toString(star) + ".png");
    this->addChild(body);
};

void Heal::updateFly(float dt)
{
    if (((this->getPosition().x - target->getPosition().x) * (this->getPosition().x - target->getPosition().x) + (this->getPosition().y - target->getPosition().y) * (this->getPosition().y - target->getPosition().y)) < 2000.0f)
    {
        //扣血在这里
        if (target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeRealMp(target->getRealMp() + target->getHurtMp());    //敌人受击回蓝*/
        }
        if (owner != nullptr && target != nullptr && target->getRealHp() > 0)
        {
            target->ChangeRealHp(target->getRealHp() - owner->getDamage());   //敌人受击掉血
        }
        body->removeFromParent();
        this->unschedule(CC_SCHEDULE_SELECTOR(Heal::updateFly));
    }
    this->setPosition(this->getPosition() + speed * 0.005f);
    float deg = 2.0f;
    this->setRotation(this->getRotation() - deg);
};
