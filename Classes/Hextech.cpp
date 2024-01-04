#include"Hextech.h"

USING_NS_CC;

bool Hextech::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    /*�����������˹��ť*/
    auto item1 = GCreator::getInstance()->createMenuItem("Hextech/Money.png", "Hextech/Money.png", CC_CALLBACK_1(Hextech::choseCallback1, this), 335.0f, 315.0f, 0.0f, 0.0f);   //�ȷŵ����½�
    auto item2 = GCreator::getInstance()->createMenuItem("Hextech/Population.png", "Hextech/Population.png", CC_CALLBACK_1(Hextech::choseCallback2, this), 675.0f, 315.0f, 0.0f, 0.0f);   //�ȷŵ����½�
    auto item3 = GCreator::getInstance()->createMenuItem("Hextech/ClearMind.png", "Hextech/ClearMind.png", CC_CALLBACK_1(Hextech::choseCallback3, this), 1015.0f, 315.0f, 0.0f, 0.0f);   //�ȷŵ����½�

    //�˵�����
    auto menu = Menu::create(item1, item2, item3, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2,"menu");

    //��ʾ��ǩ
    auto label = GCreator::getInstance()->createLabel("Choose your Hextech runes", "fonts/Marker Felt.ttf", 32, 786.0f, 760.f);
    this->addChild(label, 2, "label");


    return true;
}
/*��ҿ��ֵĻص�����*/
void Hextech::choseCallback1(cocos2d::Ref* pSender)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    littlehero->setHextechStatus(MONEY);
    littlehero->update_gold(15);
    this->removeFromParent();//ɾ�����ͼ��
}
/*�˿ڼ�һ�Ļص�����*/
void Hextech::choseCallback2(cocos2d::Ref* pSender)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    littlehero->setHextechStatus(POPULATION);
    this->removeFromParent();//ɾ�����ͼ��
}
/*����ͷ�ԵĻص�����*/
void Hextech::choseCallback3(cocos2d::Ref* pSender)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    littlehero->setHextechStatus(CLEARMIND);
    this->removeFromParent();//ɾ�����ͼ��
}