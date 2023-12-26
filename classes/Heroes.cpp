#include "Heroes.h"
#include "GeneralCreator.h"
USING_NS_CC;

bool Hero::init()
{
    if (!Node::init())
        return false;

    return true;
}

HeroImages Hero::getImages()
{
	return { imageOnField, imageInStoreNormal, imageInStoreSelected };
}

int Hero::getCost()
{
	return cost;
}

HeroType Hero::getID()
{
    return id;
}

void Hero::getSpriteReady()
{
    body = Sprite::create(imageOnField);
    if (body == nullptr)
        GCreator::problemLoading(imageOnField);
    addChild(body);
}

Hero* Hero::createExactHero(HeroType type)
{
    switch (type)
    {
        case EXAMPLE:
            return Example::create();
        default:
            break;
    }

    return nullptr;
}

Hero* Hero::copy(Hero* templt)
{
    Hero* cpy = new (std::nothrow) Hero;
    CCASSERT(cpy, "FATAL: Not enough memory");
    cpy->autorelease();

    cpy->imageOnField = templt->imageOnField;
    cpy->imageInStoreNormal = templt->imageInStoreNormal;
    cpy->imageInStoreSelected = templt->imageInStoreSelected;
    cpy->cost = templt->cost;
    cpy->name = templt->name;
    //棋子类如果要添加数据成员，一定记得在这里也加上赋值语句（如果涉及到类，最好创建全新备份）

    cpy->getSpriteReady();      //完成精灵生成和设置
    cpy->setName(cpy->name);    //完成名称设置

    return cpy;
}

bool Example::init()
{
    if (!Hero::init())
        return false;

    //图像信息初始化
    imageOnField = "hero1OnField.png";
    imageInStoreNormal = "hero1InStoreNormal.png";
    imageInStoreSelected = "hero1InStoreSelected.png";

    //数据初始化
    cost = 1;
    name = "Example";
    id = EXAMPLE;

    //后面可能还需要一些别的内容
    
    return true;
}
