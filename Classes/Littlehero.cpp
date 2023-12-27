#include "Map.h"
#include "cocos2d.h"
#include"Heroes.h"
#include"Littlehero.h"
#include "GeneralCreator.h"
#define LHNUM 6      //最大小小英雄数量
#define M_LEVEL 6    //最大等级
#define Winning_Streak_Rewards 1//连胜或者连败奖励
#define Gold_Per_Turn  5//每回合固定金币
USING_NS_CC;
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
void LHcontroler::clearInstance()
{
    if (s_Sharedcontroler)
        delete s_Sharedcontroler;
    s_Sharedcontroler = nullptr;
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
    heros.at(LHcontroler::get_mynumber())->init_layer();//初始化图层此玩家的选手图层
    heros.at(LHcontroler::get_mynumber())->init_MyMap();
    return true;
}
void Littlehero::init_layer()
{
    heroslayer = Layer::create();//创建图层
    //放置购买经验的按钮
    set_ExpButton();
    //放置金币标签,和图标
    set_Gold(); 
    //放置消息提示类
    set_Messagelabel();
    //放置人口的图标
    set_PopulationLabel();
    //显示血条
    set_HP_Bar();
    //放置三个标签
    set_threelabel();
    //在右侧显示选手ID
    set_IDs();
    //在右侧显示选手头像
    set_avatar();
    //加入小小英雄
    add_Littlehero();
    /*创建监听器*/
    initMouseListeners();
}
void Littlehero::init_MyMap()
{
    My_Map = MapData::create();
    My_Map->retain();
    return;
}
/*下面是初始化选手图层相关的函数*/
/*————————————————————————————————————*/
/*设置经验等级血量ID头像标签的函数*/
void Littlehero::set_threelabel()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Hplabel = Label::createWithTTF(  "Your Hp:"+StringUtils::toString(Hp), "fonts/Marker Felt.ttf", 24);
    Explabel = Label::createWithTTF("Your Exp:" + StringUtils::toString(Exp) + "/" + StringUtils::toString(Level== M_LEVEL ? 0:Explevel[Level]), "fonts/Marker Felt.ttf", 24);
    Levellabel = Label::createWithTTF("Your Level:" + StringUtils::toString(Level), "fonts/Marker Felt.ttf", 24);
    Hplabel->setAnchorPoint(Vec2(0, 1));
    Explabel->setAnchorPoint(Vec2(0, 1));
    Levellabel->setAnchorPoint(Vec2(0, 1));
    Hplabel->setPosition(Vec2(5, visibleSize.height));
    Explabel->setPosition(Vec2(5, visibleSize.height - Hplabel->getContentSize().height));
    Levellabel->setPosition(Vec2(5, visibleSize.height - 2 * Explabel->getContentSize().height));
    heroslayer->addChild(Hplabel, 0, "Hplabel");
    heroslayer->addChild(Explabel, 0, "Hplabel");
    heroslayer->addChild(Levellabel, 0, "Levellabel"); 
}
void Littlehero::add_Littlehero()//加入小小英雄
{
    YourLittleHreo = Sprite::create("littlehero1.png");
    YourLittleHreo->setPosition(Vec2(280, 960 - 560));
    YourLittleHreo->setAnchorPoint(Vec2(0.5, 0.5));
    heroslayer->addChild(YourLittleHreo, 0, "littlehero");
}
void Littlehero::set_ExpButton()//放置购买经验的按钮
{
    //放置增加经验的按钮
    auto BuyexpItem = GCreator::getInstance()->createMenuItem("herolayer/BuylvlButton.png", "herolayer/BuylvlButton.png", CC_CALLBACK_0(Littlehero::Buy_exp, this), 48, 948 - 926, 0, 0);
    BuyexpItem->setScale(BuyexpButtonSize.x / BuyexpItem->getContentSize().width);
    auto menu = Menu::create(BuyexpItem, NULL);
    menu->setPosition(Vec2::ZERO);
    heroslayer->addChild(menu, 1, "Buyexpitem");
}
void Littlehero::set_Gold()   //放置金币标签,和图标
{
    Goldlabel = Label::createWithTTF(StringUtils::toString(Gold), "fonts/Marker Felt.ttf", 24);
    Goldimage = GCreator::getInstance()->createSprite("herolayer/gold.png", 0, 0, 0, 0);
    Goldimage->setContentSize(Size(1600.0f, 948.0f));
    Goldlabel->setAnchorPoint(Vec2(0, 1));
    Goldlabel->setPosition(GoldLabelPosition);
    heroslayer->addChild(Goldlabel, 0, "Goldlabel");
    heroslayer->addChild(Goldimage, 0, "Goldimage");
}
void Littlehero::set_PopulationLabel()//放置人口的图标
{
    /*设置人口标签和图标*/

    auto PopulationLabel = Label::createWithTTF(StringUtils::toString(chequers) + "/" + StringUtils::toString(Level), "fonts/Marker Felt.ttf", 48);
    Population = GCreator::getInstance()->createSprite("herolayer/Population.png", 0, 0, 0, 0);
    Population->setContentSize(Size(1600.0f, 948.0f));
    Population->setOpacity(0);
    PopulationLabel->setOpacity(0);
    PopulationLabel->setPosition(PopulationLabelPosition);
    heroslayer->addChild(Population, 1, "Goldimage");
    heroslayer->addChild(PopulationLabel, 1, "PopulationLabel");
}
void Littlehero::set_IDs()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto heros = LHcontroler::getInstance()->heros;
    for (int i = 0; i < M_LEVEL; i++)
    {
        auto IDlabel = Label::createWithTTF(heros.at(i)->ID, "fonts/Marker Felt.ttf", 24);
        IDlabel->setAnchorPoint(Vec2(1, 1));
        IDlabel->setPosition(Vec2(visibleSize.width, visibleSize.height - 60-i*110));
        heroslayer->addChild(IDlabel, 0, "IDlabel"+ heros.at(i)->ID);
    }
}
void Littlehero::set_avatar()//显示头像
{
    avatarimage = GCreator::getInstance()->createSprite("herolayer/Avatar.png", 0, 0, 0, 0);
    avatarimage->setContentSize(Size(1600.0f, 948.f));
    heroslayer->addChild(avatarimage, 0, "avatarimage");
}
//显示消息提示标签
void Littlehero::set_Messagelabel()
{
    Messagelabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    Messagelabel->setPosition(MESSAGELABEL);
    heroslayer->addChild(Messagelabel, 0, "Messagelabel");
}
void Littlehero::set_HP_Bar()//显示血条
{

}
/*————————————————————————————————————*/
/*下面是更新数据相关的函数*/
/*————————————————————————————————————*/
void Littlehero::update_Hp(int hp)
{
    Hp -= hp;
    Hplabel->setString(StringUtils::toString(Hp));
}
void Littlehero::Buy_exp()
{
    Exp = Exp + 4;
    //判断是否要升级
    Checklevel();
    //更新标签
    Explabel->setString("Your Exp:" + StringUtils::toString(Exp) + "/" + StringUtils::toString(Level == M_LEVEL ? 0 : Explevel[Level]));
    Levellabel->setString("Your Level:" + StringUtils::toString(Level));
    update_gold();
}
void Littlehero::Update_exp(int exp)
{
    if (Level == M_LEVEL)
        return;
    Exp += exp;
}
void Littlehero::Checklevel()
{
    while (Level <=5&&Exp - Explevel[Level] >= 0)
    {
        Exp -= Explevel[Level];
        Level++;
    }
    if (Level == M_LEVEL)
        Exp = 0;
    return;
}
void Littlehero::update_gold()//每回合更新金币
{
    int interest;
    if (Gold >= 50)
        interest = 5;
    else 
        interest = Gold / 10;
     Gold = Gold + Winning_Streak_Rewards * VICTORY + Gold_Per_Turn+interest;
     Goldlabel->setString(StringUtils::toString(Gold));
     showInterest();
}
void Littlehero::update_gold(int num)//更新金币
{
    Gold = Gold + num;
    Goldlabel->setString(StringUtils::toString(Gold));
   showInterest();
}
void Littlehero::showInterest()//显示利息的图标
{
    int interest;
    if (Gold >= 50)
        interest = 5;
    else
        interest = Gold / 10;
    auto node = heroslayer->getChildByName("Interest");
    if (node != nullptr)
        node->removeFromParent();
    if (interest > 0)
    {
       Sprite* newnode = GCreator::getInstance()->createSprite("herolayer/Interest" + StringUtils::toString(interest) + ".png", 0, 0, 0, 0);
       newnode->setContentSize(Size(1600.0f, 948.0f));
        heroslayer->addChild(newnode, 0, "Interest");
    }
   
}
/*————————————————————————————————————*/
/*下面是实现棋子拖动的几个函数*/
/*————————————————————————————————————*/
void Littlehero::initMouseListeners()
{
    auto mouseListener = EventListenerMouse::create();

    // 左键监听
    mouseListener->onMouseDown = CC_CALLBACK_1(Littlehero::onLeftMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(Littlehero::onLeftMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(Littlehero::onLeftMouseUp, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), heroslayer);

    // 右键监听
    mouseListener->onMouseDown = CC_CALLBACK_1(Littlehero::onRightMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, heroslayer);
}

bool Littlehero::onLeftMouseDown(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        //判断这个位置上有没有棋子
        Vec2 location = event->getLocationInView();
        Lastposition = YourLittleHreo->getPosition();
        //两个for循环遍历备战席和场上的棋子
        if (YourLittleHreo->getBoundingBox().containsPoint(location))
        {
            isDragging = true;
            return true;
        }
    }
    set_message("");
    //Messagelabel->setString("");
    return false;
}

void Littlehero::onLeftMouseMove(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT&&isDragging==1)
    {
        //开始移动精灵
        Vec2 location = event->getLocationInView();
        //显示人口和回显
        My_Map->setmaplines(100);
        Population->setOpacity(100);
        heroslayer->getChildByName("PopulationLabel")->setOpacity(100);
        // 移动精灵

        YourLittleHreo->setPosition(location);
    }
    return;
}

void Littlehero::onLeftMouseUp(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && isDragging == 1)
    {
        // 处理左键释放事件
        //这里应该将棋子直接摆放到距离鼠标距离最近的正确的位置

        My_Map->setmaplines(0);
        Population->setOpacity(0);
        heroslayer->getChildByName("PopulationLabel")->setOpacity(0);
        Vec2 location = event->getLocationInView();
        YourLittleHreo->setPosition(getmidposition(location));
        isDragging = false;
        return;
    }
}
bool Littlehero::onRightMouseDown(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        Vec2 location = event->getLocationInView();
        YourLittleHreo->stopAllActions();
        float o = location.x - YourLittleHreo->getPosition().x;
        float a = location.y - YourLittleHreo->getPosition().y;
        float at = (float)CC_RADIANS_TO_DEGREES(atanf(o / a));
        YourLittleHreo->runAction(MoveTo::create(1, Vec2(location.x, location.y)));
        if (a < 0)
        {
            if (o < 0)
                at = 180 + fabs(at);
            else
                at = 180 - fabs(at);
        }
        return true;
    }

    return false;
}
/*————————————————————————————————————*/
/*下面是地图相关的函数*/
/*————————————————————————————————————*/
Vec2 Littlehero::getmidposition(int x, int y)
{
    Vec2 vec2;
    vec2.x = (MapSizeX[x] + MapSizeX[x + 1]) / 2;
    vec2.y = (MapSizeY[y] + MapSizeY[y + 1]) / 2;
    return vec2;
}
Vec2 Littlehero::getmidposition(Vec2 location)
{
    if ((location.x >= MapSizeX[0] && location.x <= MapSizeX[4] && location.y >= MapSizeY[0] && location.y <= MapSizeY[4]))
    {
        int i = 0;
        while (location.x > MapSizeX[i])
        {
            i++;
        }
        int j = 0;
        while (location.y > MapSizeY[j])
        {
            j++;
        }
        return  getmidposition(i - 1, j - 1);
    }
    else if(location.x >= PreparationsSizeX[0] && location.x <= PreparationsSizeX[9] && location.y >= PreparationsSizeY[0] && location.y <= PreparationsSizeY[1])
    {
        int i = 0;
        while (location.x > PreparationsSizeX[i])
        {
            i++;
        }
        return  getmidposition(i-1);
    }
    else
    {
        Messagelabel->setString("You can only place the chess on the left half of the square or on the Preparation Seat.");
        return Lastposition;
    }
}
Vec2 Littlehero::getmidposition(int x)
{
    Vec2 vec2;
    vec2.x = (PreparationsSizeX[x] + PreparationsSizeX[x + 1]) / 2;
    vec2.y = (PreparationsSizeY[1] + PreparationsSizeY[0]) / 2;
    return vec2;
}
