#include "Heroes.h"
USING_NS_CC;

//���ԣ��ļ���ʧ��ʱ����Ϣ���
static void problemLoading(const std::string filename)
{
    log("���ļ�%s���ɹ���", filename);
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
    //���������Ҫ������ݳ�Ա��һ���ǵ�������Ҳ���ϸ�ֵ��䣨����漰���࣬��ô���ȫ�±��ݣ�

    cpy->getSpriteReady();      //��ɾ������ɺ�����
    cpy->setName(cpy->name);    //�����������

    return cpy;
}

bool Example::init()
{
    if (!Hero::init())
        return false;

    //ͼ����Ϣ��ʼ��
    imageOnField = "hero1OnField.png";
    imageInStoreNormal = "hero1InStoreNormal.png";
    imageInStoreSelected = "hero1InStoreSelected.png";

    //���ݳ�ʼ��
    cost = 1;
    name = "Example";

    //������ܻ���ҪһЩ�������
    
    return true;
}
