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
            problemLoading("littleHero.png");
        s_SharedLittleHero->grade = 1;
    }

    return s_SharedLittleHero;
}

int LittleHero::getGrade() const
{
    return grade;
}

HeroImages Hero::getImages() const
{
	return { imageOnField, imageInStoreNormal, imageInStoreSelected };
}

int Hero::getCost() const
{
	return cost;
}

Hero* Hero::copy(Hero* templt)
{
    Hero* cpy = new (std::nothrow) Hero;
    CCASSERT(cpy, "FATAL: Not enough memory");

    cpy->body = templt->body ? Sprite::createWithSpriteFrame(templt->body->getSpriteFrame()) : nullptr;  //使用模板英雄的精灵指针创建新的精灵指针
    cpy->imageOnField = templt->imageOnField;
    cpy->imageInStoreNormal = templt->imageInStoreNormal;
    cpy->imageInStoreSelected = templt->imageInStoreSelected;
    cpy->cost = templt->cost;
    cpy->name = templt->name;
    //棋子类如果要添加数据成员，一定记得在这里也加上赋值语句（如果涉及到类，最好创建全新备份）

    return cpy;
}

bool Example::init()
{
    if (!Node::init())
        return false;

    //图像信息初始化
    imageOnField = "hero1OnField.png";
    imageInStoreNormal = "hero1InStoreNormal.png";
    imageInStoreSelected = "hero1InStoreSelected.png";

    //数据初始化
    cost = 1;
    name = "Example";

    //创建精灵指针
    body = Sprite::create(imageOnField);
    if (body == nullptr)
        problemLoading(imageOnField);

    //后面可能还需要一些别的内容
    
    return true;
}
