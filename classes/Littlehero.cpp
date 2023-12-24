#include "Map.h"
#include "cocos2d.h"
#include"Heroes.h"
#include"Littlehero.h"
#define LHNUM 6      //���ССӢ������
#define M_LEVEL 6    //���ȼ�
#define Winning_Streak_Rewards 1//��ʤ�������ܽ���
#define Gold_Per_Turn  5//ÿ�غϹ̶����
USING_NS_CC;
static void problemLoading(const std::string filename)
{
    log("���ļ�%s���ɹ���", filename);
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
//ССӢ�۵ĳ�ʼ��
bool Littlehero::init()
{
    return true;
}
//�������ĳ�ʼ��
bool LHcontroler::init()
{
    //����
    for (int i = 0; i < LHNUM; i++)
    {
        heros.pushBack(Littlehero::create());
        heros.at(i)->ID = "Gamer"+StringUtils::toString( i);
    }
    heros.at(LHcontroler::get_mynumber())->init_layer();//��ʼ��ͼ�����ҵ�ѡ��ͼ��
    heros.at(LHcontroler::get_mynumber())->init_MyMap();
    return true;
}
void Littlehero::init_layer()
{
    heroslayer = Layer::create();//����ͼ��
    //�������Ӿ���İ�ť
    auto BuyexpItem = createMenuItem("closeNormal.png", "closeSelected.png", CC_CALLBACK_0(Littlehero::Buy_exp, this), visibleSize.width * 0.618f, visibleSize.height * 0.618f);
    auto menu = Menu::create(BuyexpItem, NULL);
    menu->setPosition(Vec2::ZERO);
    heroslayer->addChild(menu, 1);
    //���ý�ұ�ǩ
    Goldlabel = Label::createWithTTF("Your Gold:" + StringUtils::toString(Gold), "fonts/Marker Felt.ttf", 24);
    Goldlabel->setAnchorPoint(Vec2(0, 1));
    Goldlabel->setPosition(Vec2(5, visibleSize.height - 3 * Goldlabel->getContentSize().height));
    heroslayer->addChild(Goldlabel, 0, "Goldlabel");
    //����������ǩ
    set_threelabel();
    //���Ҳ���ʾѡ��ID
    set_IDs();
    //���Ҳ���ʾѡ��ͷ��
    set_avatar();
    //����ССӢ��
    YourLittleHreo = Sprite::create("littlehero1.png");
    YourLittleHreo->runAction(JumpTo::create(4, Vec2(300, 48), 100, 4));
    YourLittleHreo->setAnchorPoint(Vec2(0.5, 0.5));
    heroslayer->addChild(YourLittleHreo, 0, "littlehero");
    /*����������*/
    initMouseListeners();
}
void Littlehero::init_MyMap()
{
    My_Map = MapData::create();
    return;
}
/*���þ���ȼ�Ѫ��IDͷ���ǩ�ĺ���*/
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
    //�ж��Ƿ�Ҫ����
    Checklevel();
    //���±�ǩ
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
void Littlehero::update_gold()//ÿ�غϸ��½��
{
     Gold = Gold + Winning_Streak_Rewards * VICTORY + Gold_Per_Turn;
     Goldlabel->setString("Your Gold:" + StringUtils::toString(Gold));
}
void Littlehero::update_gold(int num)//���½��
{
    Gold = Gold + num;
}
void Littlehero::set_HP_Bar()//��ʾѪ��
{

}
void Littlehero::set_avatar()//��ʾͷ��
{
    avatar = Sprite::create("avatar/Portraits2_02.png");
    avatar->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 ));
    heroslayer->addChild(avatar, 0, "avatar");
}



/*������ʵ�������϶��ļ�������*/
void Littlehero::initMouseListeners()
{
    auto mouseListener = EventListenerMouse::create();

    // �������
    mouseListener->onMouseDown = CC_CALLBACK_1(Littlehero::onLeftMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(Littlehero::onLeftMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(Littlehero::onLeftMouseUp, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), heroslayer);

    // �Ҽ�����
    mouseListener->onMouseDown = CC_CALLBACK_1(Littlehero::onRightMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, heroslayer);
}

bool Littlehero::onLeftMouseDown(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        //�ж����λ������û������
        Vec2 location = event->getLocationInView();
        //����forѭ��������սϯ�ͳ��ϵ�����
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
        //��ʼ�ƶ�����
        Vec2 location = event->getLocationInView();
        // �ƶ�����
        My_Map->setmaplines(100);
        YourLittleHreo->setPosition(location);
    }
    return ;
}

void Littlehero::onLeftMouseUp(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        // ��������ͷ��¼�
        //����Ӧ�ý�����ֱ�Ӱڷŵ������������������ȷ��λ��
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

/*������ʵ��ССӢ���ƶ��ĺ���*/

/*��ť��������
*���ĸ�����������x��y���꣬����x��yê��
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
