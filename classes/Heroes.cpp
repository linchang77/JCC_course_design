#include "Heroes.h"
USING_NS_CC;

//调试：文件打开失败时的信息输出
static void problemLoading(const std::string filename)
{
    log("打开文件%s不成功！", filename);
}

LittleHero* s_SharedLittleHero = nullptr;

LittleHero* LittleHero::getInstance()
{
    if (!s_SharedLittleHero)
    {
        s_SharedLittleHero = new (std::nothrow) LittleHero;
        CCASSERT(s_SharedLittleHero, "FATAL: Not enough memory");
        s_SharedLittleHero->body = Sprite::create("littleHero.png");
        if (s_SharedLittleHero->body == nullptr)
            problemLoading("'littleHero.png'");
        s_SharedLittleHero->grade = 1;
    }

    return s_SharedLittleHero;
}

Sprite* LittleHero::getSprite()
{
    return body;
}

int LittleHero::getGrade()
{
    return grade;
}

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

void Hero::getSpriteReady()
{
    body = Sprite::create(imageOnField);
    if (body == nullptr)
        problemLoading(imageOnField);
    addChild(body);
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

    //后面可能还需要一些别的内容
    
    return true;
}
