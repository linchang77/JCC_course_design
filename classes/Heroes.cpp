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
