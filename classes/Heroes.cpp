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
    id = EXAMPLE;

    //������ܻ���ҪһЩ�������
    
    return true;
}
