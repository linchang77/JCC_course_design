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

    cpy->getSpriteReady();  //使用模板英雄的精灵指针创建新的精灵指针
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
    //棋子类如果要添加数据成员，一定记得在这里也加上赋值语句（如果涉及到类，最好创建全新备份）

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

bool Golem::init()    //坦克-Demon
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
    auto fadeout = FadeOut::create(0.5f);    //0.5s淡出消失
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
    schedule(CC_SCHEDULE_SELECTOR(Hero::UpdateHp, this), 0.1f);  //刷新函数，每隔0.1秒
    return true;
};

void Hero::UpdateHp(float dt)
{
    auto progress = (ProgressTimer*)hero_space->getChildByTag(Hp_Bar);
    progress->setPercentage(realHp / maxHp * 100);    //这里是百分制显示
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
    schedule(CC_SCHEDULE_SELECTOR(Hero::UpdateHp, this), 0.1f);  //刷新函数，每隔0.1秒
    return true;
};

void Hero::UpdateMp(float dt)
{
    auto progress = (ProgressTimer*)this->getChildByTag(Mp_Bar);
    progress->setPercentage(realMp / maxMp * 100);    //这里是百分制显示
    if (progress->getPercentage() < 0)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(Hero::UpdateMp, this));
    }
};*/

void Golem::Death()
{
    auto startCallback = CallFunc::create([this]()
        {
            isDying = 1;    //开始死亡动作;
        });
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_01_Dying.plist");    ////创建一个Vector类型的数据用来存放所需要的精灵帧
    Vector<SpriteFrame*> frameVector;
    for (int i = 0; i < 15; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Golem_01_Dying_0%d.png", i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 0.05f);    //第二个参数是动画执行的持续时间
    animation->setRestoreOriginalFrame(false);    //设置动画执行完时是否回到原始状态
    animation->setLoops(1);    //设置动画反复执行的次数
    auto action = Animate::create(animation);    //用动画缓存初始化Animation实例，用Animate实例来播放序列帧动画
    auto fadeout = FadeOut::create(0.5f);    //0.5s淡出消失
    auto endCallback = CallFunc::create([this]()
        {
            isDying = false;    //结束死亡动作
            isDead = true;    //判断为死亡
        });
    body->runAction(Sequence::create(startCallback, action, fadeout, endCallback, nullptr));
};

void Golem::Attack()
{
    auto startCallback = CallFunc::create([this]()
        {
            isAttack = true;    //开始攻击动作
        });
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_01_Attacking.plist");    ////创建一个Vector类型的数据用来存放所需要的精灵帧
    Vector<SpriteFrame*> frameVector;
    for (int i = 0; i < 12; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Golem_01_Attacking_0%d.png", i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 1 / frequency / 12);    //第二个参数是动画执行的持续时间
    animation->setRestoreOriginalFrame(false);    //设置动画执行完时是否回到原始状态
    animation->setLoops(1);    //设置动画反复执行的次数
    auto action = Animate::create(animation);    //用动画缓存初始化Animation实例，用Animate实例来播放序列帧动画
    auto endCallback = CallFunc::create([this]()    //攻击动作执行回调
        {
            isAttack = false;    //结束攻击动作
            /*realMp += attackMp;    //攻击回蓝
            enemy->ChangeRealMp(enemy->getRealMp() + enemy->getHurtMp());    //敌人受击回蓝*/
            if (enemy != NULL)
                enemy->ChangeRealHp(enemy->getRealHp() - damage);   //敌人受击掉血
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};

void Golem::Move(HeroPosition destination)
{
    auto startCallback = CallFunc::create([this]()
        {
            isMove = true;    //开始移动动作
        });
    position.x = destination.x;
    position.y = destination.y;    //将英雄位置更新为终点位置
    //float distance;    //通过坐标获取移动距离//LHcontroler::getInstance()->getMyLittleHero()->getmidposition(destination.x, destination.y)
    auto moveto = MoveTo::create(0.4f, LHcontroler::getInstance()->getMyLittleHero()->getmidposition(destination.x, destination.y));   //移动
    //auto moveto = MoveTo::create(2.0f, Point(-300, 0));
    this->runAction(moveto);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Golem_01_Walking1.plist");    ////创建一个Vector类型的数据用来存放所需要的精灵帧
    Vector<SpriteFrame*> frameVector;
    for (int i = 0; i < 18; i++)
    {
        char pngName[100] = { 0 };
        sprintf(pngName, "Golem_01_Walking_0%d.png", i);
        SpriteFrame* pngNameSF = SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
        frameVector.pushBack(pngNameSF);
    }
    auto animation = Animation::createWithSpriteFrames(frameVector, 0.4f / 18);    //第二个参数是动画执行的持续时间
    animation->setRestoreOriginalFrame(false);    //设置动画执行完时是否回到原始状态
    animation->setLoops(1);    //设置动画反复执行的次数
    auto action = Animate::create(animation);    //用动画缓存初始化Animation实例，用Animate实例来播放序列帧动画

    auto endCallback = CallFunc::create([this]()
        {
            isMove = false;    //结束移动动作
            // Attack();
            
           
        });
    body->runAction(Sequence::create(startCallback, action, endCallback, nullptr));
};