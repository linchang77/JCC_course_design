#include "Heroes.h"
#include "Battlefield.h"
#include "GeneralCreator.h"
#include"fight.h"
#include "AudioEngine.h"
USING_NS_CC;

void Hero::FairyHeal() {}

void Hero::ArcherArrow() {}

void Hero::MummyCurse() {}

void Hero::WizardEffect() {}

void Fairy::FairyHeal()
{
    auto heal = Heal::create();    //����һ���ӵ�
    heal->chooseOwner(this);
    heal->SetStar(star);    //�˴������Ǽ�
    auto FI = fight::getInstance();
    heal->SetSpace(FI);
    heal->setPosition(this->getPositionX() + 50.0f * (2 * FaceRight - 1), this->getPositionY());
    FI->addChild(heal);
    heal->chooseTarget(enemy);
    heal->setDirection();
    heal->changeSpeed(enemy->getPosition() - heal->getPosition());
    heal->schedule(CC_SCHEDULE_SELECTOR(Heal::updateFly), 0.004f);
};

void Archer::ArcherArrow()
{
    auto arrow = Arrow::create();    //����һ���ӵ�
    arrow->chooseOwner(this);
    auto FI = fight::getInstance();
    arrow->SetSpace(FI);
    arrow->setPosition(this->getPositionX() + 50.0f * (2 * FaceRight - 1), this->getPositionY());
    FI->addChild(arrow);
    arrow->chooseTarget(enemy);
    arrow->setDirection();
    arrow->changeSpeed(enemy->getPosition() - arrow->getPosition());
    arrow->schedule(CC_SCHEDULE_SELECTOR(Bullet::updateFly), 0.002f);
};

void Mummy::MummyCurse()
{
    auto curse = Curse::create();    //����һ���ӵ�
    curse->chooseOwner(this);
    auto FI = fight::getInstance();
    curse->SetSpace(FI);
    curse->setPosition(this->getPositionX() + 50.0f * (2 * FaceRight - 1), this->getPositionY());
    FI->addChild(curse);
    curse->chooseTarget(enemy);
    curse->setDirection();
    curse->changeSpeed(enemy->getPosition() - curse->getPosition());
    curse->schedule(CC_SCHEDULE_SELECTOR(Curse::updateFly), 0.004f);
};

void Wizard::WizardEffect()
{
    auto effect = Effect::create();    //����һ���ӵ�
    effect->chooseOwner(this);
    effect->SetStar(star);    //�˴������Ǽ�
    auto FI = fight::getInstance();
    effect->setPosition(this->getPositionX() + 50.0f * (2 * FaceRight - 1), this->getPositionY());
    effect->SetSpace(FI);
    FI->addChild(effect);
    effect->chooseTarget(enemy);
    effect->setDirection();
    effect->changeSpeed(enemy->getPosition() - effect->getPosition());
    effect->schedule(CC_SCHEDULE_SELECTOR(Effect::updateFly), 0.004f);
};

HeroImages Hero::getImages()
{
	return { imageOnField, imageInStoreNormal, imageInStoreSelected };
}

int Hero::getCost()
{
    return cost;
};

int Hero::getvalue()
{
    int value = cost;
    for (int i = 1; i < star; i++)
        value *= 3;
    return value;
}

void Hero::setHeroPosition(HeroPosition NowPosition)
{
    position = NowPosition;
}

Hero* Hero::copy(Hero* templt)
{
    Hero* cpy = Hero::createExactHero(templt->id);

    cpy->getSpriteReady(templt->star);  //ʹ��ģ��Ӣ�۵ľ���ָ�봴���µľ���ָ��
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
    cpy->star = templt->star;
    cpy->FaceRight = templt->FaceRight;
    cpy->BaseFrequency = templt->BaseFrequency;
    //���������Ҫ������ݳ�Ա��һ���ǵ�������Ҳ���ϸ�ֵ��䣨����漰���࣬��ô���ȫ�±��ݣ�

    return cpy;
};

void Hero::Turnaround()
{
    this->setScaleX(-_scaleX);
    FaceRight = 1 - FaceRight;
}

void Hero::ToTurn(HeroPosition destination)
{
    if (destination.x > position.x&&FaceRight == 0)
    {
        Turnaround();
    }
    if (destination.x < position.x && FaceRight == 1)
    {
        Turnaround();
    }
}

void Hero::getSpriteReady(int star1)
{
    body = Sprite::create(imageOnField);
    if (body == nullptr)
        GCreator::problemLoading(imageOnField);
    addChild(body);
    //body->setAnchorPoint(Point(0, 0));
    
    this->setScale(0.3f);
}

void Hero::setStar(int Star)
{
    HeroType ID = id;
    star = Star;
    imageOnField = HeroTypes[ID]+"_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = HeroTypes[ID] + "card.png";
    imageInStoreSelected = "InStoreSelected.png";
    this->setScale(0.4f);
}

void Golem::getSpriteReady(int star1)
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;
   
    maxHp = 1500 * ExtraAttribute;
    realHp = 1500 * ExtraAttribute;
    maxMp = 150;
    realMp = 50;
    range = 1;
    frequency = 1;
    BaseFrequency = frequency;
    attackMp = 25;
    hurtMp = 10;
    damage = 30 * ExtraAttribute;

    this->setScale(0.4f);
}

Hero* Hero::createExactHero(HeroType type)
{
    switch (type)
    {
        case GOLEM:
            return Golem::create();
        case GOBLIN:
            return Goblin::create();
        case KING:
            return King::create();
        case PIRATE:
            return Pirate::create();
        case NINJA:
            return Ninja::create();
        case ARCHER:
            return Archer::create();
        case FAIRY:
            return Fairy::create();
        case MUMMY:
            return Mummy::create();
        case WIZARD:
            return Wizard::create();
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

void Hero::BodyInit()
{
    if (this->body == NULL)
    {
        body = Sprite::create(imageOnField);
        if (body == nullptr)
            GCreator::problemLoading(imageOnField);
        addChild(body);
    }
}

bool Golem::init()    //̹��-Demon
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 2;
    imageOnField = "Golem_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Golemcard.png";
    imageInStoreSelected = "InStoreSelected.png";
    moveSpeed = 1;
    id = GOLEM;
    return true;
};

<<<<<<< HEAD
void Goblin::getSpriteReady(int star1)
=======
void Hero::Attack() {};

void Hero::Death() {};

void Hero::Move(HeroPosition destination) {};

HeroPosition Hero::getHeroPosition()
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;

    maxHp = 500 * ExtraAttribute;
    realHp = 500 * ExtraAttribute;
    maxMp = 150;
    realMp = 50;
    range = 1;
    frequency = 1.5;
    BaseFrequency = frequency;
    attackMp = 25;
    hurtMp = 15;
    damage = 50 * ExtraAttribute;

    this->setScale(0.4f);
}

bool Goblin::init()
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 1;
    imageOnField = "Goblin_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Goblincard.png";
    imageInStoreSelected = "InStoreSelected.png";
    id = GOBLIN;
    moveSpeed = 1;
    return 1;
}

void King::getSpriteReady(int star1)
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;
 
    maxHp = 900 * ExtraAttribute;
    realHp = 900 * ExtraAttribute;
    maxMp = 150;
    realMp = 50;
    range = 1;
    frequency = 1.5;
    BaseFrequency = frequency;
    attackMp = 25;
    hurtMp = 15;
    damage = 60 * ExtraAttribute;

    this->setScale(0.4f);
}

bool King::init()
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 2;
    imageOnField = "King_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Kingcard.png";
    imageInStoreSelected = "InStoreSelected.png";
    id = KING;
    moveSpeed = 1;
    return 1;
}

void Pirate::getSpriteReady(int star1)
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;
    
    maxHp = 1100 * ExtraAttribute;
    realHp = 1100 * ExtraAttribute;
    maxMp = 150;
    realMp = 50;
    range = 1;
    frequency = 1.5;
    BaseFrequency = frequency;
    attackMp = 25;
    hurtMp = 15;
    damage = 90 * ExtraAttribute;
    if (star == 3)
    {
        maxHp += 4000;
        realHp = maxHp;
        damage += 200;
    }

    this->setScale(0.4f);
}

bool Pirate::init()
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 3;
    imageOnField = "Pirate_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Paritecard.png";
    imageInStoreSelected = "InStoreSelected.png";
    id = PIRATE;
    moveSpeed = 1;
    return 1;
};

void Ninja::getSpriteReady(int star1)
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;
    
    maxHp = 600 * ExtraAttribute;
    realHp = 600 * ExtraAttribute;
    maxMp = 150;
    realMp = 50;
    range = 1;
    frequency = 1.5;
    BaseFrequency = frequency;
    attackMp = 25;
    hurtMp = 20;
    damage = 70 * ExtraAttribute;
    this->setScale(0.4f);
}

bool Ninja::init()
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 2;
    imageOnField = "Ninja_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Ninjacard.png";
    imageInStoreSelected = "InStoreSelected.png";
    id = NINJA;
    moveSpeed = 1;
    return 1;
};

bool Fairy::init()
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 2;
    imageOnField = "Fairy_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Fairycard.png";
    imageInStoreSelected = "InStoreSelected.png";
    id = FAIRY;
    moveSpeed = 1;
    return 1;
}

void Fairy::getSpriteReady(int star1)
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;

    maxHp = 600 * ExtraAttribute;
    realHp = 600 * ExtraAttribute;
    maxMp = 100;
    realMp = 50;
    range = 4;
    frequency = 1;
    BaseFrequency = frequency;
    attackMp = 25;
    hurtMp = 10;
    damage = 30 * ExtraAttribute;
    this->setScale(0.4f);
};

bool Archer::init()
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 2;
    imageOnField = "Archer_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Archercard.png";
    imageInStoreSelected = "InStoreSelected.png";
    id = ARCHER;
    moveSpeed = 1;
    return 1;
};

void Archer::getSpriteReady(int star1)
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;

    maxHp = 500 * ExtraAttribute;
    realHp = 500 * ExtraAttribute;
    maxMp = 150;
    realMp = 50;
    range = 4;
    frequency = 2;
    attackMp = 25;
    hurtMp = 20;
    damage = 70 * ExtraAttribute;
    BaseFrequency = frequency;
    this->setScale(0.4f);
}

bool Mummy::init()
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 1;
    imageOnField = "Mummy_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Mummycard.png";
    imageInStoreSelected = "InStoreSelected.png";
    id = MUMMY;
    moveSpeed = 1;
    return 1;
}

void Wizard::getSpriteReady(int star1)
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;
    maxHp = 700 * ExtraAttribute;
    realHp = 700 * ExtraAttribute;
    maxMp = 75;
    realMp = 50;
    range = 4;
    frequency = 1;
    attackMp = 25;
    hurtMp = 20;
    damage = 50 * ExtraAttribute;
    if (star == 3)
    {
        maxHp += 4000;
        realHp = maxHp;
        damage += 200;
    }
    this->setScale(0.4f);
}

bool Wizard::init()
{
    if (!Hero::init())
    {
        return false;
    }
    cost = 3;
    imageOnField = "Wizard_0" + StringUtils::toString(star) + "_Idle.png";
    imageInStoreNormal = "card/Wizardcard.png";
    imageInStoreSelected = "InStoreSelected.png";
    id = WIZARD;
    moveSpeed = 1;
    return 1;
}

void Mummy::getSpriteReady(int star1)
{
    setStar(star1);
    BodyInit();
    //body->setAnchorPoint(Point(0, 0));
    float ExtraAttribute = 1;
    if (star == 2)ExtraAttribute = 1.5;
    if (star == 3)ExtraAttribute = 2.7;
    maxHp = 350 * ExtraAttribute;
    realHp = 350 * ExtraAttribute;
    maxMp = 75;
    realMp = 50;
    range = 4;
    frequency = 1;
    BaseFrequency = frequency;
    attackMp = 25;
    hurtMp = 20;
    damage = 20 * ExtraAttribute;
    this->setScale(0.4f);
}

void Hero::Death()
{
    auto startCallback = CallFunc::create([this]()
        {
            isDying = 1;    //��ʼ��������;
        });
    std::string Plist = HeroTypes[id] + "_0" + StringUtils::toString(star) + ".plist";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(Plist);    ////����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 15; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "%s_0%d_Dying (%d).png", HeroTypes[id].c_str(), star, i);
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

void Hero::Attack()
{
    auto startCallback = CallFunc::create([this]()
        {
            isAttack = true;    //��ʼ��������
        });
    std::string Plist = HeroTypes[id] + "_0" + StringUtils::toString(star) + ".plist";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(Plist);    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    int AttackingMaxSize = MaxAttack;
    if (id == ARCHER)
        AttackingMaxSize = MaxAttack_Archer;
    for (int i = 1; i <= AttackingMaxSize; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "%s_0%d_Attacking (%d).png", HeroTypes[id].c_str(), star, i);
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
            if (getRealHp() > 0)
                ChangeRealMp(realMp + attackMp);    //��������
            if (id == FAIRY)
            {
                FairyHeal();
            }
            else if (id == ARCHER)
            {
                ArcherArrow();
            }
            else if (id == MUMMY)
            {
                MummyCurse();
            }
            else if (id == WIZARD)
            {
                WizardEffect();
            }
            else
            {
                
                if (enemy != nullptr && enemy->getRealHp() > 0)
                    enemy->ChangeRealMp(enemy->getRealMp() + enemy->getHurtMp());    //�����ܻ�����*/
                if (enemy != nullptr && enemy->getRealHp() > 0)
                    enemy->ChangeRealHp(enemy->getRealHp() - damage);   //�����ܻ���Ѫ
            }
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

<<<<<<< HEAD
void Hero::Move(HeroPosition destination)
=======
void Golem::Move(HeroPosition destination)
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
{
    auto startCallback = CallFunc::create([this]()
        {
            isMove = true;    //��ʼ�ƶ�����
        });
<<<<<<< HEAD
    ToTurn(destination);
    position.x = destination.x;
    position.y = destination.y;    //��Ӣ��λ�ø���Ϊ�յ�λ��
    //float distance;    //ͨ�������ȡ�ƶ�����//LHcontroler::getInstance()->getMyLittleHero()->getmidposition(destination.x, destination.y)
    auto moveto = MoveTo::create(0.4f, LHcontroler::getInstance()->getMyLittleHero()->getmidposition(destination.x, destination.y));   //�ƶ�
    //auto moveto = MoveTo::create(2.0f, Point(-300, 0));
    this->runAction(moveto);
    std::string Plist = HeroTypes[id] + "_0" + StringUtils::toString(star) + ".plist";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(Plist);    ////����һ��Vector���͵����������������Ҫ�ľ���֡
=======
    position.x = destination.x;
    position.y = destination.y;    //��Ӣ��λ�ø���Ϊ�յ�λ��
    LHcontroler::getInstance()->getMyLittleHero()->Fightfield[destination.x][destination.y] = this;//����ССӢ�������fightfield
    //float distance;    //ͨ�������ȡ�ƶ�����//LHcontroler::getInstance()->getMyLittleHero()->getmidposition(destination.x, destination.y)

    auto moveto = MoveTo::create(4.0f, LHcontroler::getInstance()->getMyLittleHero()->getmidposition(destination.x, destination.y));   //�ƶ�
    //auto moveto = MoveTo::create(2.0f, Point(-300, 0));
    this->runAction(moveto);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_01_Walking1.plist");    ////����һ��Vector���͵����������������Ҫ�ľ���֡
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
    Vector<SpriteFrame*> frameVector;
    int Max_Walking = 0;
    if (id == FAIRY)
    {
        Max_Walking = MAXWALKING_FAIRY;
    }
    else
    {
        Max_Walking = MAXWALKING;
    }
    for (int i = 1; i <= Max_Walking; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "%s_0%d_Walking (%d).png", HeroTypes[id].c_str(), star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 0.4f / Max_Walking);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����

    auto endCallback = CallFunc::create([this]()
        {
            isMove = false;    //�����ƶ�����
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

HeroPosition Hero::getHeroPosition()
{
    return position;
};

Hero* Hero::StarUp(Hero* a, Hero* b, Hero* c)
{
    HeroType ID = a->id;
    int star1 = a->star + 1;   
    Hero* hero = Hero::createExactHero(ID);    //����һ�����Ǻ��Ӣ��
    hero->setStar(star1);
    hero->BodyInit();
    hero->SetSpace(a->hero_space);    //��ӵ�ͬһ��ͼ����
    hero->setPosition(a->getPosition());
    hero->hero_space->addChild(hero);
    //hero->setPosition(a->getPosition());
    //addhero(hero);
    auto fadeout = FadeOut::create(0.5f);    //0.5s������ʧ
    a->getBody()->runAction(fadeout);
    b->getBody()->runAction(fadeout);
    c->getBody()->runAction(fadeout);
    /*LHcontroler::getInstance()->heros.at(0)->remove(a);
    LHcontroler::getInstance()->heros.at(0)->remove(b);
    LHcontroler::getInstance()->heros.at(0)->remove(c);*/
    auto fadein = FadeIn::create(0.5f);    //0.5s�������
    hero->runAction(fadein);
    return hero;
};

bool Hero::InitHp()
{
    if (!Hero::init())
    {
        return false;
    }
    auto LH = LHcontroler::getInstance();
    hp_bar = Sprite::create("hp_bar.png");    //����Ѫ�����ȿ�
    hp_bar ->setPosition(0, 120);
    hp_bar->setScale(0.8f);
    //hp_bar->setPosition(LH->heros.at(0)->getmidposition(this->getPosition()).x, LH->heros.at(0)->getmidposition(this->getPosition()).y + 120.0f);     //���ÿ��λ��
    this->addChild(hp_bar);    //�ӵ�����ͼ������ȥ
    hp = Sprite::create("hp.png");    //����Ѫ��
    if (MyHero == 0)
    {
        hp->setColor(Color3B::BLUE);
    }
    ProgressTimer* progress = ProgressTimer::create(hp);    //����progress����
    progress->setType(ProgressTimer::Type::BAR);    //���������ͣ���״
    //progress->setPosition(LH->heros.at(0)->getmidposition(this->getPosition()).x- this->getPosition().x, LH->heros.at(0)->getmidposition(this->getPosition()).y + 120.0f - this->getPosition().y);    //������λ��
    progress->setPosition(0,120);
    progress->setScale(0.8f);
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //���ν���������ʼ�㣺��0��y������ߣ���1��y�����ұߣ���x��1�����ϱߣ���x��0�����±�
    this->addChild(progress);
    progress->setTag(Hp_Bar);    //��һ�����
    schedule(CC_SCHEDULE_SELECTOR(Hero::UpdateHp), 0.1f);  //ˢ�º�����ÿ��0.1��
    
    return true;
};

void Hero::UpdateHp(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(Hp_Bar);
    progress->setPercentage(realHp / maxHp * 100);    //�����ǰٷ�����ʾ
    if (progress->getPercentage() <= 0)
    {
        /*auto fadeout = FadeOut::create(0.5f);
        hp_bar->runAction(fadeout);
        mp_bar->runAction(fadeout);*/
        mp_bar->removeFromParent();
        hp_bar->removeFromParent();
        realMp = 0;
        this->unschedule(CC_SCHEDULE_SELECTOR(Hero::UpdateHp));
    }
};

bool Hero::InitMp()
{
    if (!init())
    {
        return false;
    }
    auto LH = LHcontroler::getInstance();
    mp_bar = Sprite::create("mp_bar.png");    //���������ȿ�
    mp_bar->setScale(0.8f);
    mp_bar->setPosition(0, 100); //���ÿ��λ��
    this->addChild(mp_bar);    //�ӵ�����ͼ������ȥ
    mp = Sprite::create("mp.png");    //��������
    auto progress = ProgressTimer::create(mp);    //����progress����
    progress->setType(ProgressTimer::Type::BAR);    //���������ͣ���״
    progress->setScale(0.8f);
    progress->setPosition(0, 100);
    //progress->setPosition(LH->heros.at(0)->getmidposition(this->getPosition()).x, LH->heros.at(0)->getmidposition(this->getPosition()).y + 100.0f);    //������λ��
    progress->setBarChangeRate(Point(1, 0));
    progress->setMidpoint(Point(0, 0.5));    //���ν���������ʼ�㣺��0��y������ߣ���1��y�����ұߣ���x��1�����ϱߣ���x��0�����±�
    progress->setTag(Mp_Bar);    //��һ�����
    this->addChild(progress);
    schedule(CC_SCHEDULE_SELECTOR(Hero::UpdateMp), 0.1f);  //ˢ�º�����ÿ��0.1��
    return true;
};

void Hero::UpdateMp(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(Mp_Bar);
    progress->setPercentage(realMp / maxMp * 100);    //�����ǰٷ�����ʾ
    if (!mp_bar)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Hero::UpdateMp));
    }
};

void Goblin::Ultimate()
{
    auto startCallback = CallFunc::create([this]()
        {
            isUltimate = 1;    //��ʼ��������
            realMp = 0;
        });

    //���ж���
    auto ultimateDelay = DelayTime::create(0.8f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    auto ultimate = Sprite::create("Goblin_Ultimate_Idle.png");
    this->setScale(getScaleX() * 1.25f, getScaleY() * 1.25f);
    ultimate->setScale(3.0f / 1.25f);
    ultimate->setPosition(200.0f, 20.0f);
    this->addChild(ultimate);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Goblin_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> ultimateFrameVector;
    for (int i = 1; i <= 9; i++)
    {
        char ultimatePngName[100] = { 0 };
        sprintf(ultimatePngName, "Goblin_Ultimate (%d).png", i);
        SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
        ultimateFrameVector.pushBack(ultimatePngNameSF);
    }
    auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 0.6f / 9);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
    auto ultimateAction = Animate::create(ultimateAnimation);
    ultimate->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, nullptr));

    //���﹥��
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Goblin_0" + StringUtils::toString(star) + ".plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 12; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Goblin_0%d_Attacking (%d).png",star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 1.2f / 12);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
            isUltimate = false;    //������������
            this->setScale(getScaleX() * 0.8f, getScaleY() * 0.8f);
            if (enemy != nullptr && enemy->getRealHp() > 0)
            {
                enemy->ChangeRealMp(enemy->getRealMp() + enemy->getHurtMp());
                enemy->ChangeRealHp(enemy->getRealHp() - damage * 4);
                if (enemy->getRealHp() <= 0)
                {
                    auto LH = LHcontroler::getInstance();
                    LH->getMyLittleHero()->update_gold(1);
                    Gold();
                }
            }

        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

void Goblin::Gold()
{
    auto goldDelay = DelayTime::create(0.25f);
    auto goldAppear = FadeIn::create(0.0f);
    auto goldDisappear = FadeOut::create(0.0f);
    auto gold = Sprite::create("Goblin_Treasure_Idle.png");
    auto coinfadein = FadeIn::create(0.5f);
    auto coin = Sprite::create("Goblin_Ultimate_Goldencoin.png");
    gold->setScale(1.5f);
    enemy->addChild(gold);
    enemy->addChild(coin);
    coin->setScale(3.0f);
    coin->setPosition(0.0f, 100.0f);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Goblin_Treasure.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> goldFrameVector;
    for (int i = 1; i <= 15; i++)
    {
        char goldPngName[100] = { 0 };
        sprintf(goldPngName, "Goblin_Treasure (%d).png", i);
        SpriteFrame* goldPngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(goldPngName);
        goldFrameVector.pushBack(goldPngNameSF);
    }
    auto goldAnimation = Animation::createWithSpriteFrames(goldFrameVector, 1.0f / 15);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    goldAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    goldAnimation->setLoops(1);    //���ö�������ִ�еĴ���
    auto goldAction = Animate::create(goldAnimation);
    gold->runAction(Sequence::create(goldDisappear, goldDelay, goldDelay, goldDelay, goldAppear, goldAction->reverse(), goldDisappear, nullptr));
    coin->runAction(Sequence::create(goldDisappear, goldDelay, goldDelay, goldDelay, goldDelay, goldAppear, coinfadein, goldDelay, goldDisappear, nullptr));
};

void Archer::Ultimate()
{
    auto startCallback = CallFunc::create([this]()
        {
            isUltimate = 1;    //��ʼ��������
            realMp = 0;
        });

    //�������
    auto ultimateDelay = DelayTime::create(0.1f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    auto scheduleDelay = DelayTime::create(1.0f);
    auto ultimate = Sprite::create("Archer_Ultimate_Idle.png");
    this->setScale(getScaleX() * 1.25f, getScaleY() * 1.25f);
    ultimate->setScale(1.8f/1.25f);
    ultimate->setPosition(0, -20.0f);
    this->addChild(ultimate);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Archer_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> ultimateFrameVector;
    for (int i = 1; i <= 11; i++)
    {
        char ultimatePngName[100] = { 0 };
        sprintf(ultimatePngName, "Archer_Ultimate (%d).png", i);
        SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
        ultimateFrameVector.pushBack(ultimatePngNameSF);
    }
    auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 1.0f / 11);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
    auto ultimateAction = Animate::create(ultimateAnimation);
    ultimate->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, nullptr));

    //�������
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Archer_0" + StringUtils::toString(star) + ".plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 15; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Archer_0%d_Attacking (%d).png",star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 1.0f/ 12);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback1 = CallFunc::create([this]()    //��������ִ�лص�
        {
            this->setScale(getScaleX() * 0.8f, getScaleY() * 0.8f);
            auto arrow = Archer_Ultimate::create();    //����һ���ӵ�
            auto FI = fight::getInstance();
            arrow->setPosition(this->getPositionX() + 50.0f * (2 * FaceRight - 1), this->getPositionY());
            arrow->SetSpace(FI);
            FI->addChild(arrow);
            arrow->chooseOwner(this);
            arrow->chooseTarget(enemy);
            arrow->setDirection();
            arrow->changeSpeed(enemy->getPosition() - arrow->getPosition());
            isUltimate = 0;
            arrow->schedule(CC_SCHEDULE_SELECTOR(Archer_Ultimate::updateFly), 0.025f);
        });
    auto endCallback2 = CallFunc::create([this]()    //��������ִ�лص�
        {
            enemy->schedule(CC_SCHEDULE_SELECTOR(Archer::Vertigo), 0.05f);
        });
    body->runAction(Sequence::create(startCallback, action, endCallback1, scheduleDelay, endCallback2, nullptr));
}

void Archer::Vertigo(float dt)
{
    static int counter = 1;
    static float counterTime = 0;
    char vertigoName[100] = { 0 };
    sprintf(vertigoName, "Archer_Ultimate_Vertigo (%d).png", counter);
    auto vertigo = Sprite::create(vertigoName);
    this->addChild(vertigo);
    vertigo->setScale(2.0f);
    vertigo->setPosition(0.0f, 150.0f);
    auto ultimateDelay = DelayTime::create(0.08f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    vertigo->runAction(Sequence::create(ultimateDelay, ultimateDisappear, nullptr));
    if (counter == 5)
    {
        counter = 1;
    }
    else
    {
        counter++;
    }
    if (counterTime >= 2.5f)
    {
        counterTime = 0;
        ChangeIsVertigo(0);
        this->unschedule(CC_SCHEDULE_SELECTOR(Archer::Vertigo));
    }
    else
    {
        counterTime += dt;
    }
};

void Golem::Ultimate()
//�������10%maxHP+�ظ�10%maxHP
{
    auto startCallback = CallFunc::create([this]()
        {
            isUltimate = true;    //��ʼ��������
            realMp = 0;
        });

    //������Ч
    auto ultimateDelay = DelayTime::create(0.5f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    auto ultimate = Sprite::create("Golem_Ultimate_Idle.png");
    this->addChild(ultimate);
    ultimate->setPosition(200.0f, 150.0f);
    ultimate->setColor(Color3B::RED);
    ultimate->setScale(4.0f);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> ultimateFrameVector;
    for (int i = 1; i <= 6; i++)
    {
        char ultimatePngName[100] = { 0 };
        sprintf(ultimatePngName, "Golem_Ultimate (%d).png", i);
        SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
        ultimateFrameVector.pushBack(ultimatePngNameSF);
    }
    auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 0.5 / frequency / 6);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
    auto ultimateAction = Animate::create(ultimateAnimation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    ultimate->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, nullptr));

    //�����ܺ�
    auto bigGolem = Sprite::create("Golem_0" + StringUtils::toString(star) + "_Idle.png");
    this->addChild(bigGolem);
    bigGolem->setPosition(-150.0f, 150.0f);
    bigGolem->setColor(Color3B::RED);
    bigGolem->setScale(2.0f);
    bigGolem->setOpacity(128);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_0" + StringUtils::toString(star) + ".plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> bigGolemframeVector;
    for (int i = 1; i <= 12; i++)
    {
        char bigGolempngName[100] = { 0 };
        sprintf(bigGolempngName, "Golem_0%d_Attacking (%d).png", star, i);
        SpriteFrame* bigGolempngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(bigGolempngName);
        bigGolemframeVector.pushBack(bigGolempngNameSF);
    }
    auto bigGolemanimation = Animation::createWithSpriteFrames(bigGolemframeVector, 1 / frequency / 12);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    bigGolemanimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    bigGolemanimation->setLoops(1);    //���ö�������ִ�еĴ���
    auto bigGolemaction = Animate::create(bigGolemanimation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    bigGolem->runAction(Sequence::create(bigGolemaction, bigGolemaction, bigGolemaction, ultimateDisappear, nullptr));

    //��������
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_0" + StringUtils::toString(star) + ".plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 12; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Golem_0%d_Attacking (%d).png", star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 1 / frequency / 12);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
<<<<<<< HEAD
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
            isUltimate = false;    //������������
            if (enemy != nullptr && enemy->getRealHp()>0)
            {
                enemy->ChangeRealMp(enemy->getRealMp() + enemy->getHurtMp());
                enemy->ChangeRealHp(enemy->getRealHp() - maxHp * 0.04);
            }
            if (realHp > 0)
                realHp += 0.04 * maxHp;
            if (realHp > maxHp)
            {
                realHp = maxHp;
            }
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, startCallback, action, endCallback, startCallback, action, endCallback, nullptr));
}

void Fairy::Ultimate()
//Ⱥ���Ѫ40% MaxHp
{
    auto startCallback = CallFunc::create([this]()
        {
            realMp = 0;
            isUltimate = true;    //��ʼ��������
        });

    auto ultimateDelay = DelayTime::create(0.4f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);

    //������Ч
    auto FI = fight::getInstance();
    Vector<Hero*> Heros_To_Heal;
    Heros_To_Heal = MyHero ? FI->getMyHeroUse() : FI->getEnemyHeroUse();
    for (auto &thishero : Heros_To_Heal)
    {
        auto ultimate = Sprite::create("Fairy_Ultimate_Idle.png");
        ultimate->setScale(2.0f);
        thishero->addChild(ultimate);
        ultimate->setPosition(0, -120.0f);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Fairy_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
        Vector<SpriteFrame*> ultimateFrameVector;
        for (int i = 1; i <= 16; i++)
        {
            char ultimatePngName[100] = { 0 };
            sprintf(ultimatePngName, "Fairy_Ultimate (%d).png", i);
            SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
            ultimateFrameVector.pushBack(ultimatePngNameSF);
        }
        auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 2 / frequency / 16);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
        ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
        ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
        auto ultimateAction = Animate::create(ultimateAnimation);
        ultimate->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, nullptr));
    }
   
    //������Ч
    auto heal = Sprite::create("Heal_0" + StringUtils::toString(star) + ".png");
    this->addChild(heal);
    heal->setScale(3.0f);
    heal->setPosition(90.0f, 60.0f);
    auto healFadein = FadeIn::create(0.3f);
    heal->runAction(Sequence::create(ultimateDisappear, ultimateDelay, healFadein, ultimateDelay, ultimateDisappear, nullptr));

    //Ӣ�۶���
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Fairy_0" + StringUtils::toString(star) + "_Heal.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 18; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Fairy_0%d_Heal (%d).png",star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 1.0f/ 18);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
            auto FI = fight::getInstance();
            Vector<Hero*> Heros_To_Heal;
            Heros_To_Heal = MyHero ? FI->getMyHeroUse() : FI->getEnemyHeroUse();
            for (int i = 0; i < Heros_To_Heal.size(); i++)
            {
                auto thishero = Heros_To_Heal.at(i);
                if (thishero->getRealHp()>0)
                    thishero->ChangeRealHp(thishero->getRealHp() + 0.4f * getMaxHp());
            }
            isUltimate = false;    //������������
        });

    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

void Mummy::Ultimate()
{
    auto startCallback = CallFunc::create([this]()
        {
            realMp = 0;
            isUltimate = 1;    //��ʼ��������
        });

    //���ж���
    auto ultimateDelay = DelayTime::create(1.0f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    auto ultimate = Sprite::create("Mummy_Ultimate_Idle.png");
    this->setScale(getScaleX() * 1.25f, getScaleY() * 1.25f);
    ultimate->setScale(1.2f / getScaleY());
    enemy->addChild(ultimate);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Mummy_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> ultimateFrameVector;
    for (int i = 1; i <= 19; i++)
    {
        char ultimatePngName[100] = { 0 };
        sprintf(ultimatePngName, "Mummy_Ultimate (%d).png", i);
        SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
        ultimateFrameVector.pushBack(ultimatePngNameSF);
    }
    auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 2.0f / 19);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
    auto ultimateAction = Animate::create(ultimateAnimation);
    ultimate->runAction(Sequence::create(ultimateAction,ultimateDisappear, nullptr));

    //���﹥������
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Mummy_0" + StringUtils::toString(star) + "_Taunt.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 18; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Mummy_0%d_Taunt (%d).png",star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 2.0f / 18);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
            isUltimate = 0;        //������������
            this->setScale(getScaleX() * 1/1.25f, getScaleY() * 1/1.25f);
            if (enemy != nullptr)
            {
                enemy->ChangeRealMp(enemy->getRealMp() + enemy->getHurtMp());
                enemy->ChangeRealHp(enemy->getRealHp() - damage * 15);
            }
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

void Wizard::Ultimate()
{
    auto startCallback = CallFunc::create([this]()
        {
            realMp = 0;
            isUltimate = 1;    //��ʼ��������
        });
    auto ultimateDelay = DelayTime::create(1.0f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    auto FI = fight::getInstance();
    auto Heros_To_Attack = MyHero?FI->getEnemyHeroUse():FI->getMyHeroUse();
    int ex = enemy->getHeroPosition().x, ey = enemy->getHeroPosition().y;
    this->setScale(getScaleX() * 1.25f, getScaleY() * 1.25f);
    for (auto thishero : Heros_To_Attack)
    {
        int thisx = thishero->getHeroPosition().x, thisy = thishero->getHeroPosition().y;
        int ultimateRange = 1;
        if (star == 3)
            ultimateRange = 6;
        if (abs(ex - thisx) + abs(ey - thisy) > ultimateRange &&!(abs(ex-thisx)==1&&abs(ey-thisy)==1))
        {
            continue;
        }
        Lock.pushBack(thishero);
        auto ultimate = Sprite::create("Wizard_Ultimate_Idle.png");
        ultimate->setScale(0.4f/getScaleY());
        thishero->addChild(ultimate);
        ultimate->setPosition(0, 40.0f);

        //������Ч����
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Wizard_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
        Vector<SpriteFrame*> ultimateFrameVector;
        for (int i = 1; i <= 29; i++)
        {
            char ultimatePngName[100] = { 0 };
            sprintf(ultimatePngName, "Wizard_Ultimate (%d).png", i);
            SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
            ultimateFrameVector.pushBack(ultimatePngNameSF);
        }
        auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 2.0f / 29);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
        ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
        ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
        auto ultimateAction = Animate::create(ultimateAnimation);
        ultimate->runAction(Sequence::create(ultimateAction, ultimateDisappear, nullptr));
    }

    //���ﶯ������
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Wizard_0" + StringUtils::toString(star) + "_Taunt.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 18; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Wizard_0%d_Taunt (%d).png",star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 2.0f / 18);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
           
            this->setScale(getScaleX() * 0.8f, getScaleY() * 0.8f);
            for (auto thishero : Lock)
            {
                if (thishero!=NULL&&thishero->getRealHp() > 0)
                {
                    thishero->ChangeRealMp(thishero->getRealMp() + thishero->getHurtMp());
                    thishero->ChangeRealHp(thishero->getRealHp() - damage * 8);
                }
            }
            isUltimate = 0;
            Lock.clear();
                  //������������
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

void Ninja::Ultimate()
{
    auto startCallback = CallFunc::create([this]()
        {
            realMp = 0;
            isUltimate = 1;    //��ʼ��������
        });
    auto ultimateDelay = DelayTime::create(1.0f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    auto FI = fight::getInstance();
    auto Heros_To_Attack = MyHero ? FI->getEnemyHeroUse() : FI->getMyHeroUse();
    for (auto thishero : Heros_To_Attack)
    {
        int thisx = thishero->getHeroPosition().x, thisy = thishero->getHeroPosition().y;
        if (Target == NULL)
        {
            Target = thishero;
        }
        else
        {
            if (Target->getMaxHp() > thishero->getMaxHp() && thishero->getRealHp()>0)
                Target = thishero;
        }
    }

    //ԭ����ʧ����
    auto disappear = Sprite::create("Ninja_Disappear_Idle.png");
    this->addChild(disappear);
    disappear->setScale(3.0f);
    disappear->setColor(Color3B::MAGENTA);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Ninja_Disappear.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> disappearFrameVector;
    for (int i = 1; i <= 10; i++)
    {
        char disappearPngName[100] = { 0 };
        sprintf(disappearPngName, "Ninja_Disappear (%d).png", i);
        SpriteFrame* disappearPngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(disappearPngName);
        disappearFrameVector.pushBack(disappearPngNameSF);
    }
    auto disappearAnimation = Animation::createWithSpriteFrames(disappearFrameVector, 1.5 / frequency / 10);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    disappearAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    disappearAnimation->setLoops(1);    //���ö�������ִ�еĴ���
    auto disappearAction = Animate::create(disappearAnimation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����0
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
            if (Target != NULL && Target->getRealHp() > 0)
            {
                Target->ChangeRealMp(Target->getRealMp() + Target->getHurtMp());
                Target->ChangeRealHp(Target->getRealHp() - damage * 6);
            }
            Target = NULL;
            isUltimate = false;    //������������
        });
    body->runAction(Sequence::create(startCallback, ultimateDisappear, ultimateDelay, ultimateDelay, ultimateDelay, ultimateAppear,endCallback, nullptr));
    disappear->runAction(Sequence::create(disappearAction, ultimateDisappear, ultimateDelay, ultimateAppear, disappearAction->reverse(), ultimateDisappear, nullptr));

    //���й�������
    auto ultimate = Sprite::create("Ninja_Ultimate_Idle.png");
    Target->addChild(ultimate);
    ultimate->setScale(-5.0f,5.0f);
    ultimate->setPosition(-140.0f,140.0f );
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Ninja_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> ultimateFrameVector;
    for (int i = 1; i <= 21; i++)
    {
        char ultimatePngName[100] = { 0 };
        sprintf(ultimatePngName, "Ninja_Ultimate (%d).png", i);
        SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
        ultimateFrameVector.pushBack(ultimatePngNameSF);
    }
    auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 1.5 / frequency / 21);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
    auto ultimateAction = Animate::create(ultimateAnimation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    ultimate->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, nullptr));
};

void Pirate::Ultimate()
{
    auto startCallback = CallFunc::create([this]()
        {
            realMp = 0;
            isUltimate = 1;    //��ʼ��������
        });

    //���ж���
    auto ultimateDelay = DelayTime::create(0.5f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    auto FI = fight::getInstance();
    auto Heros_To_Attack = MyHero ? FI->getEnemyHeroUse() : FI->getMyHeroUse();
    this->setScale(getScaleX() * 1.25f, getScaleY() * 1.25f);
    int Heros_Size = Heros_To_Attack.size();
    int Heros_Can_Locked_Size = 0;
    for (auto thishero : Heros_To_Attack)
    {
        if (thishero->getRealHp() <= 0)
            continue;
        Heros_Can_Locked_Size++;
    }
    int coin = random(0, Heros_Size - 1);
    bool HasLocked[8] = { 0 };
    int MaxLock = 2;
    if (star == 3)
        MaxLock = 8;
    while (Lock.size() < MaxLock && Lock.size() < Heros_Can_Locked_Size)
    {
        coin = random(0, Heros_Size - 1);
        if (HasLocked[coin])
            continue;
        if (Heros_To_Attack.at(coin)->getRealHp() <= 0)
            continue;
        HasLocked[coin] = 1;
        Lock.pushBack(Heros_To_Attack.at(coin));
    }
    for (auto thishero : Lock)
    {
        auto ultimate = Sprite::create("Pirate_Ultimate_Idle.png");
        float Positionx = -280.0f * 2, Positiony = 380.0f * 2;
        if (thishero->getFaceRight() != MyHero)
        {
            Positionx = 280.0f * 2;
        }
        auto boom = Sprite::create("Pirate_Ultimate_boom.png");
        boom->setScale(1.5f);
        auto moveto = MoveBy::create(0.7f, Vec2(-Positionx, -Positiony));
        boom->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateDelay, ultimateAppear, moveto, ultimateDisappear, nullptr));
        boom->setPosition(Positionx, Positiony);
        thishero->addChild(boom);
        ultimate->setScale(3.0f);
        thishero->addChild(ultimate);

        //ǰ��ը�����У���׼��

        auto aim = Sprite::create("Pirate_Aim_Idle.png");
        aim->setScale(2.0f);
        thishero->addChild(aim);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Pirate_Aim.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
        Vector<SpriteFrame*> aimFrameVector;
        for (int i = 1; i <= 5; i++)
        {
            char aimPngName[100] = { 0 };
            sprintf(aimPngName, "Pirate_Aim (%d).png", i);
            SpriteFrame* aimPngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(aimPngName);
            aimFrameVector.pushBack(aimPngNameSF);
        }
        auto aimAnimation = Animation::createWithSpriteFrames(aimFrameVector, 0.5f / 5);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
        aimAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
        aimAnimation->setLoops(1);    //���ö�������ִ�еĴ���
        auto aimAction = Animate::create(aimAnimation);
        aim->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateAppear, aimAction, ultimateDelay, ultimateDisappear, nullptr));
        
        //ը����ը
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Pirate_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
        Vector<SpriteFrame*> ultimateFrameVector;
        for (int i = 1; i <= 8; i++)
        {
            char ultimatePngName[100] = { 0 };
            sprintf(ultimatePngName, "Pirate_Ultimate (%d).png", i);
            SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
            ultimateFrameVector.pushBack(ultimatePngNameSF);
        }
        auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 2.0f / 3.0f / 8);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
        ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
        ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
        auto ultimateAction = Animate::create(ultimateAnimation);
        ultimate->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateDelay, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, nullptr));
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Pirate_0" + StringUtils::toString(star) + ".plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 12; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Pirate_0%d_Attacking (%d).png",star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 4.0f / 3.0f / 12);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
            isUltimate = false;    //������������
            this->setScale(getScaleX() * 0.8f, getScaleY() * 0.8f);
            for (auto thishero : Lock)
            {
                if (thishero != nullptr && thishero->getRealHp() > 0)
                {
                    thishero->ChangeRealMp(thishero->getRealMp() + thishero->getHurtMp());
                    thishero->ChangeRealHp(thishero->getRealHp() - damage * 4);
                }
            }
            
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

void King::Ultimate()
{
    auto startCallback = CallFunc::create([this]()
        {
            realMp = 0;
            isUltimate = 1;    //��ʼ����
        });

    //���ж���
    auto ultimateDelay = DelayTime::create(0.8f);
    auto ultimateAppear = FadeIn::create(0.0f);
    auto ultimateDisappear = FadeOut::create(0.0f);
    //this->setScale(getScaleX() * 1.25f, getScaleY() * 1.25f);
    auto FI = fight::getInstance();
    auto Heros_To_Buff = MyHero ? FI->getMyHeroUse() : FI->getEnemyHeroUse();
    for (auto thishero : Heros_To_Buff)
    {
        auto ultimate = Sprite::create("King_Ultimate_Idle.png");
        ultimate->setScale(2.0f);
        thishero->addChild(ultimate);

        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("King_Ultimate.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
        Vector<SpriteFrame*> ultimateFrameVector;
        for (int i = 1; i <= 14; i++)
        {
            char ultimatePngName[100] = { 0 };
            sprintf(ultimatePngName, "King_Ultimate (%d).png", i);
            SpriteFrame* ultimatePngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(ultimatePngName);
            ultimateFrameVector.pushBack(ultimatePngNameSF);
        }
        auto ultimateAnimation = Animation::createWithSpriteFrames(ultimateFrameVector, 0.8f / 14);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
        ultimateAnimation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
        ultimateAnimation->setLoops(1);    //���ö�������ִ�еĴ���
        auto ultimateAction = Animate::create(ultimateAnimation);
        ultimate->runAction(Sequence::create(ultimateDisappear, ultimateDelay, ultimateAppear, ultimateAction, ultimateDisappear, nullptr));
    }

    //���ﶯ��
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("King_0" + StringUtils::toString(star) + "_Taunt.plist");    //����һ��Vector���͵����������������Ҫ�ľ���֡
    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 18; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "King_0%d_Taunt (%d).png",star, i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 1.0f / 18);    //�ڶ��������Ƕ���ִ�еĳ���ʱ��
    animation->setRestoreOriginalFrame(false);    //���ö���ִ����ʱ�Ƿ�ص�ԭʼ״̬
    animation->setLoops(1);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����
    auto endCallback = CallFunc::create([this]()    //��������ִ�лص�
        {
            isUltimate = false;    //��������
            auto FI = fight::getInstance();
            auto Heros_To_Buff = MyHero ? FI->getMyHeroUse() : FI->getEnemyHeroUse();
            for (auto &thishero : Heros_To_Buff)
            { 
                for (int i = 0; i < 3; i++)
                {
                    if (i < star - 1)
                        thishero->ChangeKingBuff(star - 1, 0);
                    if (i > star - 1 && thishero->getKingBuff(i))
                        return;
                }
                thishero->ChangeKingBuff(star - 1, thishero->getKingBuff(star-1) + 1);
            }
            schedule(CC_SCHEDULE_SELECTOR(King::KingBuff), 0.08f, kRepeatForever, 0.1f);
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

void King::KingBuff(float dt)
{
    bool ok = 1;
    static int check = 0;
    for (int i = 0; i < 3; i++)
    {
        if (kingBuff[i] >= 1)
        {
            check = i;
        }
    }
    static int counter = 1;
    static float counterTime = 0;
    auto FI = fight::getInstance();
    auto Heros_To_Buff = MyHero ? FI->getMyHeroUse() : FI->getEnemyHeroUse();
    
    for (auto &thishero : Heros_To_Buff)
    {
        char buffName[100] = { 0 };
        sprintf(buffName, "King_Buff (%d).png", counter);
        auto buff = Sprite::create(buffName);
        thishero->addChild(buff);
        buff->setScale(2.0f);
        auto ultimateDelay = DelayTime::create(0.08f);
        auto ultimateDisappear = FadeOut::create(0.0f);
        buff->runAction(Sequence::create(ultimateDelay, ultimateDisappear, nullptr));
    }
    if (counter == 8)
    {
        counter = 1;
    }
    else
    {
        counter++;
    }
    counterTime += dt;
=======
    animation->setLoops(4);    //���ö�������ִ�еĴ���
    auto action = Animate::create(animation);    //�ö��������ʼ��Animationʵ������Animateʵ������������֡����

    auto endCallback = CallFunc::create([this]()
        {
            isMove = false;    //�����ƶ�����
            // Attack();
            
           
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));

>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
};