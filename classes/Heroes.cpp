#include "Heroes.h"
#include "Battlefield.h"
#include "GeneralCreator.h"

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

void Hero::setHeroPosition(HeroPosition NowPosition)
{
    position = NowPosition;
}

Hero* Hero::copy(Hero* templt)
{
    Hero* cpy = Hero::createExactHero(templt->id);

    cpy->getSpriteReady();  //ʹ��ģ��Ӣ�۵ľ���ָ�봴���µľ���ָ��
    cpy->imageOnField = templt->imageOnField;
    cpy->imageInStoreNormal = templt->imageInStoreNormal;
    cpy->imageInStoreSelected = templt->imageInStoreSelected;
    cpy->cost = templt->cost;
    cpy->position = templt->position;
    cpy->hero_space = templt->hero_space;
    cpy->hp_bar = templt->hp_bar ? Sprite::createWithSpriteFrame(templt->hp_bar->getSpriteFrame()) : nullptr;
    cpy->hp = templt->hp ? Sprite::createWithSpriteFrame(templt->hp->getSpriteFrame()) : nullptr;
    cpy->mp_bar = templt->mp_bar ? Sprite::createWithSpriteFrame(templt->mp_bar->getSpriteFrame()) : nullptr;
    cpy->mp = templt->mp ? Sprite::createWithSpriteFrame(templt->mp->getSpriteFrame()) : nullptr;
    cpy->maxHp = templt->maxHp;
    cpy->realHp = templt->realHp;
    cpy->maxMp = templt->maxMp;
    cpy->realMp = templt->realMp;
    cpy->attackMp = templt->attackMp;
    cpy->hurtMp = templt->hurtMp;
    cpy->range = templt->range;
    cpy->damage = templt->damage;
    cpy->frequency = templt->frequency;
    cpy->moveSpeed = templt->moveSpeed;
    cpy->isAttack = templt->isAttack;
    cpy->isMove = templt->isMove;
    cpy->isDying = templt->isDying;
    cpy->isDead = templt->isDead;
    cpy->attackCounter = templt->attackCounter;
    cpy->enemy = templt->enemy;
    cpy->id = templt->id;
    //���������Ҫ������ݳ�Ա��һ���ǵ�������Ҳ���ϸ�ֵ��䣨����漰���࣬��ô���ȫ�±��ݣ�

    return cpy;
};

void Hero::getSpriteReady()
{
    body = Sprite::create(imageOnField);
    if (body == nullptr)
        GCreator::problemLoading(imageOnField);
    addChild(body);
    //body->setAnchorPoint(Point(0, 0));
    body->setScale(0.3f);
}

Hero* Hero::createExactHero(HeroType type)
{
    switch (type)
    {
        case GOLEM:
            return Golem::create();
        default:
            break;
    }

    return nullptr;
};

bool Hero::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
};

bool Golem::init()    //̹��-Demon
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 1;
    maxHp = 200;
    realHp = 200;
    maxMp = 100;
    realMp = 100;
    range = 1;
    frequency = 2;
    attackMp = 10;
    hurtMp = 20;
    damage = 25;
    imageOnField = "Golem_01_Idle.png";
    imageInStoreNormal = "Golem_01_Idle.png";
    imageInStoreSelected = "Golem_01_Idle.png";
    moveSpeed = 1;
    id = GOLEM;
    return true;
};

void Hero::Attack() {};

void Hero::Death() {};

void Hero::Move(HeroPosition destination) {};

HeroPosition Hero::getHeroPosition()
{
    return position;
};

void Hero::StarUp(Hero* a, Hero* b, Hero* c)
{
    auto fadeout = FadeOut::create(0.5f);    //0.5s������ʧ
    a->getBody()->runAction(fadeout);
    b->getBody()->runAction(fadeout);
    c->getBody()->runAction(fadeout);
    /*LHcontroler::getInstance()->heros.at(0)->Remove(a);
    LHcontroler::getInstance()->heros.at(0)->Remove(b);
    LHcontroler::getInstance()->heros.at(0)->Remove(c);*/

}

/*bool Hero::InitHp()
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
    schedule(CC_SCHEDULE_SELECTOR(Hero::UpdateHp, this), 0.1f);  //ˢ�º�����ÿ��0.1��
    return true;
};

void Hero::UpdateHp(float dt)
{
    auto progress = (ProgressTimer*)hero_space->getChildByTag(Hp_Bar);
    progress->setPercentage(realHp / maxHp * 100);    //�����ǰٷ�����ʾ
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Hero::UpdateHp, this));
    }
};

bool Hero::InitMp()
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
    schedule(CC_SCHEDULE_SELECTOR(Hero::UpdateHp, this), 0.1f);  //ˢ�º�����ÿ��0.1��
    return true;
};

void Hero::UpdateMp(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(Mp_Bar);
    progress->setPercentage(realMp / maxMp * 100);    //�����ǰٷ�����ʾ
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Hero::UpdateMp, this));
    }
};*/

void Golem::Death()
{
    auto startCallback = CallFunc::create([this]()
        {
            isDying = 1;    //��ʼ��������;
        });
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_01_Dying.plist");    ////����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 0; i < 15; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Golem_01_Dying_0%d.png", i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 0.05f);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto fadeout = FadeOut::create(0.5f);    //0.5s������ʧ
    auto endCallback = CallFunc::create([this]()
        {
            isDying = false;    //������������
            isDead = true;    //�ж�Ϊ����
        });
    body->runAction(Sequence::create(startCallback, action, fadeout, endCallback, nullptr));
};

void Golem::Attack()
{
    auto startCallback = CallFunc::create([this]()
        {
            isAttack = true;    //��ʼ��������
        });
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_01_Attacking.plist");    ////����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 0; i < 12; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Golem_01_Attacking_0%d.png", i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 1 / frequency / 12);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
            isAttack = false;    //������������
            /*realMp += attackMp;    //��������
            enemy->ChangeRealMp(enemy->getRealMp() + enemy->getHurtMp());    //�����ܻ�����*/
            if (enemy != NULL)
                enemy->ChangeRealHp(enemy->getRealHp() - damage);   //�����ܻ���Ѫ
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

void Golem::Move(HeroPosition destination)
{
    auto startCallback = CallFunc::create([this]()
        {
            isMove = true;    //��ʼ�ƶ�����
        });
    position.x = destination.x;
    position.y = destination.y;    //��Ӣ��λ�ø���Ϊ�յ�λ��
    //float distance;    //ͨ�������ȡ�ƶ�����//LHcontroler::getInstance()->getMyLittleHero()->getmidposition(destination.x, destination.y)
    auto moveto = MoveTo::create(0.4f, LHcontroler::getInstance()->getMyLittleHero()->getmidposition(destination.x, destination.y));   //�ƶ�
    //auto moveto = MoveTo::create(2.0f, Point(-300, 0));
    this->runAction(moveto);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_01_Walking1.plist");    ////����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 0; i < 18; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Golem_01_Walking_0%d.png", i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 0.4f / 18);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����

    auto endCallback = CallFunc::create([this]()
        {
            isMove = false;    //�����ƶ�����
            // Attack();
            
           
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};