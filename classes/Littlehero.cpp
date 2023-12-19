#include "Map.h"
#include "cocos2d.h"
#include"Heroes.h"
#include"Littlehero.h"
#define LHNUM 6
USING_NS_CC;
static void problemLoading(const std::string filename)
{
    log("打开文件%s不成功！", filename);
}
static LHcontroler* s_Sharedcontroler = nullptr;
static int mynumber=0;
int LHcontroler::get_mynumber()
{
    return mynumber;
}
LHcontroler* LHcontroler::getInstance()
{
    if (!s_Sharedcontroler)
    {
        s_Sharedcontroler = new (std::nothrow) LHcontroler;
       // CCASSERT(s_SharedModeSelector, "FATAL: Not enough memory");
        s_Sharedcontroler->init();
    }
    return s_Sharedcontroler;
}
//小小英雄的初始化
bool Littlehero::init()
{
    return true;
}
//控制器的初始化
bool LHcontroler::init()
{
    //生成
    for (int i = 0; i < LHNUM; i++)
    {
        heros.pushBack(Littlehero::create());
        heros.at(i)->ID = "Gamer"+StringUtils::toString( i);
    }
    heros.at(LHcontroler::get_mynumber())->init_layer();//初始化图层
    return true;
}
void Littlehero::init_layer()
{
    heroslayer = Layer::create();//创建图层
    set_threelabel();
    set_IDs();
    //set_avatar();
}
void Littlehero::set_threelabel()
{
    Hplabel = Label::createWithTTF(  "Your Hp:"+StringUtils::toString(Hp), "fonts/Marker Felt.ttf", 24);
    Explabel = Label::createWithTTF("Your Hp:" + StringUtils::toString(Exp), "fonts/Marker Felt.ttf", 24);
    Levellabel = Label::createWithTTF("Your level:" + StringUtils::toString(level), "fonts/Marker Felt.ttf", 24);
    Hplabel->setAnchorPoint(Vec2(0, 1));
    Explabel->setAnchorPoint(Vec2(0, 1));
    Levellabel->setAnchorPoint(Vec2(0, 1));
    Hplabel->setPosition(Vec2(5, visibleSize.height));
    Explabel->setPosition(Vec2(5, visibleSize.height - Explabel->getContentSize().height));
    Levellabel->setPosition(Vec2(5, visibleSize.height - 2 * Explabel->getContentSize().height));
    heroslayer->addChild(Hplabel, 0, "Hplabel");
    heroslayer->addChild(Explabel, 0, "Hplabel");
    heroslayer->addChild(Levellabel, 0, "Levellabel"); 
}
void Littlehero::set_IDs()
{
    auto heros = LHcontroler::getInstance()->heros;
    for (int i = 0; i < LHNUM; i++)
    {
        auto IDlabel = Label::createWithTTF(heros.at(i)->ID, "fonts/Marker Felt.ttf", 24);
        IDlabel->setAnchorPoint(Vec2(1, 1));
        IDlabel->setPosition(Vec2(visibleSize.width, visibleSize.height - 60-i*110));
        heroslayer->addChild(IDlabel, 0, "IDlabel"+ heros.at(i)->ID);
    }
}
void Littlehero::set_HP_Bar()//显示血条
{

}
void Littlehero::set_avatar()//显示头像
{

}