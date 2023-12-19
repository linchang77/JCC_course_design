#include "Heroes.h"
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
    hero_space = Layer::create();    //����Ӣ�����ڲ�
    body = Sprite::create(imageOnField);    //����Ӣ��

    return true;
};

bool Example::init()
{
    
}