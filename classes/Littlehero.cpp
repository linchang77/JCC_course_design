#include "Map.h"
#include "cocos2d.h"
#include"Heroes.h"
#include"Littlehero.h"
#define LHNUM 6      //最大小小英雄数量
#define M_LEVEL 6    //最大等级
#define Winning_Streak_Rewards 1//连胜或者连败奖励
#define Gold_Per_Turn  5//每回合固定金币
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
    heros.at(LHcontroler::get_mynumber())->init_layer();//初始化图层此玩家的选手图层
    heros.at(LHcontroler::get_mynumber())->init_MyMap();
    return true;
}
void Littlehero::init_layer()
{
    heroslayer = Layer::create();//创建图层
    //放置增加经验的按钮
    auto BuyexpItem = createMenuItem("closeNormal.png", "closeSelected.png", CC_CALLBACK_0(Littlehero::Buy_exp, this), visibleSize.width * 0.618f, visibleSize.height * 0.618f);
    auto menu = Menu::create(BuyexpItem, NULL);
    menu->setPosition(Vec2::ZERO);
    heroslayer->addChild(menu, 1);
    //放置金币标签
    Goldlabel = Label::createWithTTF("Your Gold:" + StringUtils::toString(Gold), "fonts/Marker Felt.ttf", 24);
    Goldlabel->setAnchorPoint(Vec2(0, 1));
    Goldlabel->setPosition(Vec2(5, visibleSize.height - 3 * Goldlabel->getContentSize().height));
    heroslayer->addChild(Goldlabel, 0, "Goldlabel");
    //放置三个标签
    set_threelabel();
    //在右侧显示选手ID
    set_IDs();
    //在右侧显示选手头像
    set_avatar();
    //加入小小英雄
    YourLittleHreo = Sprite::create("littlehero1.png");
    YourLittleHreo->runAction(JumpTo::create(4, Vec2(300, 48), 100, 4));
    YourLittleHreo->setAnchorPoint(Vec2(0.5, 0.5));
    heroslayer->addChild(YourLittleHreo, 0, "littlehero");
    /*创建监听器*/
    initMouseListeners();
}
void Littlehero::init_MyMap()
{
    My_Map = MapData::create();
    return;
}
/*设置经验等级血量ID头像标签的函数*/
void Littlehero::set_threelabel()
{
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
void Littlehero::set_IDs()
{
    auto heros = LHcontroler::getInstance()->heros;
    for (int i = 0; i < M_LEVEL; i++)
    {
        auto IDlabel = Label::createWithTTF(heros.at(i)->ID, "fonts/Marker Felt.ttf", 24);
        IDlabel->setAnchorPoint(Vec2(1, 1));
        IDlabel->setPosition(Vec2(visibleSize.width, visibleSize.height - 60-i*110));
        heroslayer->addChild(IDlabel, 0, "IDlabel"+ heros.at(i)->ID);
    }
}
void Littlehero::update_Hp(int hp)
{
    Hp -= hp;
}
void Littlehero::Buy_exp()
{
    Exp = Exp + 4;
    //判断是否要升级
    Checklevel();
    //更新标签
    Explabel->setString("Your Exp:" + StringUtils::toString(Exp) + "/" + StringUtils::toString(Level == M_LEVEL ? 0 : Explevel[Level]));
    Levellabel->setString("Your Level:" + StringUtils::toString(Level));
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
     Gold = Gold + Winning_Streak_Rewards * VICTORY + Gold_Per_Turn;
     Goldlabel->setString("Your Gold:" + StringUtils::toString(Gold));
}
void Littlehero::update_gold(int num)//更新金币
{
    Gold = Gold + num;
}
void Littlehero::set_HP_Bar()//显示血条
{

}
void Littlehero::set_avatar()//显示头像
{
    avatar = Sprite::create("avatar/Portraits2_02.png");
    avatar->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 ));
    heroslayer->addChild(avatar, 0, "avatar");
}



/*下面是实现棋子拖动的几个函数*/
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
        //两个for循环遍历备战席和场上的棋子
        if (YourLittleHreo->getBoundingBox().containsPoint(location))
        {
            isDragging = true;
            return true;
        }
    }

    return false;
}

void Littlehero::onLeftMouseMove(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT&&isDragging==1)
    {
        //开始移动精灵
        Vec2 location = event->getLocationInView();
        // 移动精灵
        My_Map->setmaplines(100);
        YourLittleHreo->setPosition(location);
    }
    return ;
}

void Littlehero::onLeftMouseUp(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        // 处理左键释放事件
        //这里应该将棋子直接摆放到距离鼠标距离最近的正确的位置
        isDragging = false;
        My_Map->setmaplines(0);
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

/*下面是实现小小英雄移动的函数*/

/*按钮创建函数
*后四个参数是设置x，y坐标，设置x，y锚点
*/
>>>>>>> CJ
MenuItemImage* Littlehero::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float x, const float y, const float anchorX, const float anchorY)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);

    if (item == nullptr || item->getContentSize().width <= 0 || item->getContentSize().height <= 0)
        problemLoading("'" + normalImage + "' and '" + selectedImage);
    else
    {
        item->setAnchorPoint({ anchorX, anchorY });
        item->setPosition(origin.x + x, origin.y + y);
    }
    return item;
}
