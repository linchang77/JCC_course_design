#include "Map.h"
#include "cocos2d.h"
#include"Heroes.h"
#include"Littlehero.h"
#include "GeneralCreator.h"
#include"Battlefield.h"
#include "AudioEngine.h"
USING_NS_CC;
static LHcontroler* s_Sharedcontroler = nullptr;
static int mynumber = 0;
static int Status = LOCAL;
int LHcontroler::get_mynumber()
{
    return mynumber;
}
int LHcontroler::GetStatus()
{
    return Status;
}
LHcontroler* LHcontroler::getInstance()
{
    if (!s_Sharedcontroler)
    {
        s_Sharedcontroler = new (std::nothrow) LHcontroler;
        // CCASSERT(s_SharedModeSelector, "FATAL: Not enough memory");
    }
    return s_Sharedcontroler;
}
void LHcontroler::initlocal()
{
    Status = LOCAL;
    //����

}
void LHcontroler::initonline()
{
    Status = ONLINE;
}
void LHcontroler::clearInstance()
{
    if (s_Sharedcontroler)
        delete s_Sharedcontroler;
    s_Sharedcontroler = nullptr;
}
//ССӢ�۵ĳ�ʼ��
bool Littlehero::init()
{
    return true;
}
//�������ĳ�ʼ��
bool LHcontroler::init()
{
    /*����Ŀǰ����*/
    if (Status == ONLINE)
    {
        for (int i = 0; i < 2; i++)
        {
            heros.pushBack(Littlehero::create());
            heros.at(i)->ID = "Gamer" + StringUtils::toString(i);
        }
    }
    else if (Status == LOCAL)
    {
        /*������ı��ص�ССӢ��*/
        heros.pushBack(Littlehero::create());
        heros.at(0)->ID = "You";
        for (int i = 1; i < 4; i++)
        {
            heros.pushBack(Littlehero::create());
            heros.at(i)->ID = "AI" + StringUtils::toString(i);
        }
    }
    heros.at(LHcontroler::get_mynumber())->init_layer();//��ʼ��ͼ�����ҵ�ѡ��ͼ��
    heros.at(LHcontroler::get_mynumber())->init_MyMap();
    return true;
}
void Littlehero::init_layer()
{

    heroslayer = Layer::create();//����ͼ��
    
    if (Status == ONLINE)
    {
        heroslayer->retain();
    }
    
    //���ù�����İ�ť
    set_ExpButton();
    //���ý�ұ�ǩ,��ͼ��
<<<<<<< HEAD
    set_Gold();
=======
    set_Gold(); 
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
    //������Ϣ��ʾ��
    set_Messagelabel();
    //�����˿ڵ�ͼ��
    set_PopulationLabel();
    //��ʾѪ��
    set_HP_Bar();
    //����������ǩ
    set_threelabel();
    //���Ҳ���ʾѡ��ID
    set_IDs();
    //���Ҳ���ʾѡ��ͷ��
    set_avatar();
    //����ССӢ��
    add_Littlehero();
    sellarea = GCreator::getInstance()->createSprite("herolayer/Sellarea.png", 0, 0, 0, 0);
    sellarea->setContentSize(Size(1600.0f, 948.0f));
    sellarea->retain();
    /*����������*/
    initMouseListeners();
}
void Littlehero::init_MyMap()
{
    My_Map = MapData::create();
    My_Map->retain();
    return;
}
/*�����ǳ�ʼ��ѡ��ͼ����صĺ���*/
/*������������������������������������������������������������������������*/
/*���þ���ȼ�Ѫ��IDͷ���ǩ�ĺ���*/
void Littlehero::set_threelabel()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Hplabel = Label::createWithTTF("Your Hp:" + StringUtils::toString(Hp), "fonts/Marker Felt.ttf", 24);
    Explabel = Label::createWithTTF("Your Exp:" + StringUtils::toString(Exp) + "/" + StringUtils::toString(Level == M_LEVEL ? 0 : Explevel[Level]), "fonts/Marker Felt.ttf", 24);
    Levellabel = Label::createWithTTF("Your Level:" + StringUtils::toString(Level), "fonts/Marker Felt.ttf", 24);
    Hplabel->setAnchorPoint(Vec2(0, 1));
    Explabel->setAnchorPoint(Vec2(0, 1));
    Levellabel->setAnchorPoint(Vec2(0, 1));
    Hplabel->setPosition(Vec2(5, 948));
    Explabel->setPosition(Vec2(5, 948 - Hplabel->getContentSize().height));
    Levellabel->setPosition(Vec2(5, 948 - 2 * Explabel->getContentSize().height));
    heroslayer->addChild(Hplabel, 0, "Hplabel");
    heroslayer->addChild(Explabel, 0, "Hplabel");
    heroslayer->addChild(Levellabel, 0, "Levellabel");
}
void Littlehero::add_Littlehero()//����ССӢ��
{
    YourLittleHreo = Sprite::create("littlehero1.png");
    YourLittleHreo->setPosition(Vec2(280, 960 - 560));
    YourLittleHreo->setAnchorPoint(Vec2(0.5, 0.5));
    heroslayer->addChild(YourLittleHreo, 0, "littlehero");
}
void Littlehero::set_ExpButton()//���ù�����İ�ť
{
    //�������Ӿ���İ�ť
    auto BuyexpItem = GCreator::getInstance()->createMenuItem("herolayer/BuylvlButton.png", "herolayer/BuylvlButton.png", CC_CALLBACK_0(Littlehero::Buy_exp, this), 48, 948 - 926, 0, 0);
    BuyexpItem->setScale(0.8f*BuyexpButtonSize.x / BuyexpItem->getContentSize().width);
    auto menu = Menu::create(BuyexpItem, NULL);
    menu->setPosition(Vec2(1385,100));
    heroslayer->addChild(menu, 1, "Buyexpitem");
}
void Littlehero::set_Gold()   //���ý�ұ�ǩ,��ͼ��
{
    Goldlabel = Label::createWithTTF(StringUtils::toString(Gold), "fonts/Marker Felt.ttf", 24);
    Goldimage = GCreator::getInstance()->createSprite("herolayer/gold.png", 0, 0, 0, 0);
    Goldimage->setContentSize(Size(1600.0f, 948.0f));
    Goldlabel->setAnchorPoint(Vec2(0, 1));
    Goldlabel->setPosition(GoldLabelPosition);
    heroslayer->addChild(Goldlabel, 0, "Goldlabel");
    heroslayer->addChild(Goldimage, 0, "Goldimage");
}
void Littlehero::set_PopulationLabel()//�����˿ڵ�ͼ��
{
    /*�����˿ڱ�ǩ��ͼ��*/

    PopulationLabel = Label::createWithTTF(StringUtils::toString(chequers) + "/" + StringUtils::toString(Level), "fonts/Marker Felt.ttf", 48);
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
    auto LH = LHcontroler::getInstance();
    if (LH->GetStatus() == LOCAL)
    {
        for (int i = 0; i < 4; i++)
        {
            auto IDlabel = Label::createWithTTF(heros.at(i)->ID, "fonts/Marker Felt.ttf", 24);
            IDlabel->setAnchorPoint(Vec2(1, 1));
            IDlabel->setPosition(Vec2(1600.0f, 948.0f - 60.0f - i * 110.0f));
            heroslayer->addChild(IDlabel, 0, "IDlabel" + heros.at(i)->ID);
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            auto IDlabel = Label::createWithTTF(heros.at(i)->ID, "fonts/Marker Felt.ttf", 24);
            IDlabel->setAnchorPoint(Vec2(1, 1));
            IDlabel->setPosition(Vec2(1600.0f, 948.0f - 60.0f - i * 110.0f));
            heroslayer->addChild(IDlabel, 0, "IDlabel" + heros.at(i)->ID);
        }
    }

}
void Littlehero::set_avatar()//��ʾͷ��
{
    auto LH = LHcontroler::getInstance();
    if (LH->GetStatus() == LOCAL)
        avatarimage = GCreator::getInstance()->createSprite("herolayer/AvatarLocal.png", 0, 0, 0, 0);
    else
        avatarimage = GCreator::getInstance()->createSprite("herolayer/AvatarOnline1.png", 0, 0, 0, 0);
    avatarimage->setContentSize(Size(1600.0f, 948.f));
    heroslayer->addChild(avatarimage, 0, "avatarimage");
}
//��ʾ��Ϣ��ʾ��ǩ
void Littlehero::set_Messagelabel()
{
    Messagelabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    Messagelabel->setPosition(MESSAGELABEL);
    heroslayer->addChild(Messagelabel, 0, "Messagelabel");
}
void Littlehero::set_HP_Bar()//��ʾѪ��
{
    auto LH = LHcontroler::getInstance();
    if (LH->GetStatus() == LOCAL)
    {
        Hpframe = GCreator::getInstance()->createSprite("herolayer/HpframeLocal.png", 0, 0, 0, 0);
        Hpframe->setContentSize(Size(1600.0f, 948.f));
        heroslayer->addChild(Hpframe, 1, "  Hpframe");
        for (int i = 0; i < 4; i++)
        {
            Hpbar[i] = Sprite::create("herolayer/HpBar.png");
            Hpbar[i]->setAnchorPoint(Point(0, 0));
            Hpbar[i]->setContentSize(Size(16, 66));
            Hpbar[i]->setPosition(1504.0f, 940.0f - (145.0f + 115 * i));
            heroslayer->addChild(Hpbar[i], 0);
        }
    }
    else
    {
        Hpframe = GCreator::getInstance()->createSprite("herolayer/HpframeOnline.png", 0, 0, 0, 0);
        Hpframe->setContentSize(Size(1600.0f, 948.f));
        heroslayer->addChild(Hpframe, 1, "  Hpframe");
        for (int i = 0; i < 2; i++)
        {
            Hpbar[i] = Sprite::create("herolayer/HpBar.png");
            Hpbar[i]->setAnchorPoint(Point(0, 0));
            Hpbar[i]->setContentSize(Size(16, 66));
            Hpbar[i]->setPosition(1505.0f, 940.0f - (145.0f + 115 * i));
            heroslayer->addChild(Hpbar[i], 0);
        }
    }

}
/*������������������������������������������������������������������������*/
/*�����Ǹ���������صĺ���*/
/*������������������������������������������������������������������������*/
void Littlehero::update_Hp(int updatehp)
{
    Hp -= updatehp;
    if (Hp < 0)
        Hp = 0;
    Hps[0] = Hp;
    Hplabel->setString(StringUtils::toString(Hp));
    auto LH = LHcontroler::getInstance();
    if (LH->GetStatus() == LOCAL)
        for (int i = 0; i < 4; i++)
            Hpbar[i]->setScaleY(Hps[i] / 100.0f);
    else
    {
        Hpbar[0]->setScaleY(Hp / 100.0f);
        Hpbar[1]->setScaleY(enemyHp / 100.0f);
    }
}
void Littlehero::Buy_exp()
{
    if (Gold >= 4 && Level !=5)
    {
        update_gold(-4);
        Exp = Exp + 4;
        //�ж��Ƿ�Ҫ����
        Checklevel();
        //���±�ǩ
        Explabel->setString("Your Exp:" + StringUtils::toString(Exp) + "/" + StringUtils::toString(Level == M_LEVEL ? 0 : Explevel[Level]));
        Levellabel->setString("Your Level:" + StringUtils::toString(Level));
    }
    else
    {
        set_message("You are out of money!");
    }
}
void Littlehero::Update_exp(int exp)
{
    if (Level == M_LEVEL)
        return;
    Exp += exp;
    if (is_ClearMind())
        Exp +=3 ;
    Checklevel();
    Explabel->setString("Your Exp:" + StringUtils::toString(Exp) + "/" + StringUtils::toString(Level == M_LEVEL ? 0 : Explevel[Level]));
    Levellabel->setString("Your Level:" + StringUtils::toString(Level));

}
void Littlehero::Checklevel()
{
    while (Level <= M_LEVEL-1 && Exp - Explevel[Level] >= 0)
    {
        Exp -= Explevel[Level];
        Level++;
    }
    if (Level == M_LEVEL)
        Exp = 0;
    dynamic_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentStore()->ChangePossibility();
    return;
}
/*����˹��غ���*/
bool Littlehero::is_ClearMind()
{
    if (HextechStatus != CLEARMIND)
        return false;
    for (int i = 0; i < 9; i++)
        if (Preparation[i] != nullptr)
            return false;
    return true;
}
void Littlehero::update_gold()//ÿ�غϸ��½��
{
    int interest;
    if (VICTORY)
        Gold++;
    if (Gold >= 70 && HextechStatus == MONEY)
        interest = 7;
    else if (Gold >= 50 && HextechStatus != MONEY)
        interest = 5;
    else
        interest = Gold / 10;
    Gold = Gold + Winning_Streak_Rewards * (WinOrLoseReword[VICTORY]+WinOrLoseReword[LOST]) + Gold_Per_Turn + interest;
    Goldlabel->setString(StringUtils::toString(Gold));
    showInterest();
}
void Littlehero::update_gold(int num)//���½��
{
    Gold = Gold + num;
    Goldlabel->setString(StringUtils::toString(Gold));
    showInterest();
}
void Littlehero::update_WinOrLose(int Win, int Lose)
{
    VICTORY = Win == 0 ? 0 : VICTORY + 1;
    VICTORY = VICTORY > 5 ? 5 : VICTORY;
    LOST = Lose == 0 ? 0 : LOST + 1;
    LOST = LOST > 5 ? 5 : LOST;
}
void Littlehero::showInterest()//��ʾ��Ϣ��ͼ��
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
/*������������������������������������������������������������������������*/
/*������ʵ�������϶��ļ�������*/
/*������������������������������������������������������������������������*/
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
        Lastposition = getmidposition(location);
        //����forѭ��������սϯ�ͳ��ϵ�����
        if (location.x >= PreparationsSizeX[0] && location.x <= PreparationsSizeX[9] && location.y >= PreparationsSizeY[0] && location.y <= PreparationsSizeY[1])//�����ս����
        {
<<<<<<< HEAD
            if (Preparation[getPreparationarrayposition(location)] != nullptr)
=======
         if (Preparation[getPreparationarrayposition(location)] != nullptr)
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
            {
                Draging_hero = Preparation[getPreparationarrayposition(location)];
                isDragging = true;
            }
        }
        else if (location.x >= MapSizeX[0] && location.x <= MapSizeX[4] && location.y >= MapSizeY[0] && location.y <= MapSizeY[4])//����ڱ�սϯ��
        {
            Vec2 vec2 = getFightarrayposition(location);
            int x = vec2.x;
            int y = vec2.y;
            if (Fightfield[x][y] != nullptr)
            {
                Draging_hero = Fightfield[x][y];
                Lastposition = Draging_hero->getPosition();
                isDragging = true;
            }
        }
    }
    set_message("");
    //Messagelabel->setString("");
    return false;
}

void Littlehero::onLeftMouseMove(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && isDragging == 1)
    {
        //��ʼ�ƶ�����
        Vec2 location = event->getLocationInView();
        //��ʾ��������
<<<<<<< HEAD
        if (heroslayer->getChildByName("sellarea") == nullptr)
            heroslayer->addChild(sellarea, -1, "sellarea");
=======
        if(heroslayer->getChildByName("sellarea")==nullptr)
             heroslayer->addChild(sellarea, -1, "sellarea");
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
        //��ʾ�˿ںͻ���
        My_Map->setmaplines(100);
        if (HextechStatus == POPULATION)
            PopulationLabel->setString(StringUtils::toString(chequers) + "/" + StringUtils::toString(Level + 1));
        else
            PopulationLabel->setString(StringUtils::toString(chequers) + "/" + StringUtils::toString(Level));
        Population->setOpacity(100);
        heroslayer->getChildByName("PopulationLabel")->setOpacity(100);
        // �ƶ�����

        Draging_hero->setPosition(location);
    }
    return;
}

void Littlehero::onLeftMouseUp(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && isDragging == 1)
    {
        // ��������ͷ��¼�
        //����Ӧ�ý�����ֱ�Ӱڷŵ������������������ȷ��λ��
        My_Map->setmaplines(0);
        Population->setOpacity(0);
        heroslayer->getChildByName("PopulationLabel")->setOpacity(0);
        sellarea->removeFromParent();
        Vec2 location = event->getLocationInView();
        //�ж����̧��λ��Ŀ��
        if (location.x >= PreparationsSizeX[0] && location.x <= PreparationsSizeX[9] && location.y >= PreparationsSizeY[0]
<<<<<<< HEAD
            && location.y <= PreparationsSizeY[1] && Lastposition.y <= 315)//�����սϯ���϶�����ʼ���ڱ�սϯ
=======
            && location.y <= PreparationsSizeY[1]&&Lastposition.y<=315)//�����սϯ���϶�����ʼ���ڱ�սϯ
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
        {
            int x = getPreparationarrayposition(location);
            int pre = getPreparationarrayposition(Lastposition);//��ȡ�ƶ�֮ǰ������λ��
            if (Preparation[x] != nullptr)
            {
                Draging_hero->setPosition(getmidposition(x));
                Preparation[x]->setPosition(Lastposition);
                Preparation[pre] = Preparation[x];
<<<<<<< HEAD
                Preparation[x] = Draging_hero;
=======
                Preparation[x] = Draging_hero;  
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
            }
            else
            {
                Draging_hero->setPosition(getmidposition(x));
                Preparation[x] = Draging_hero;
                Preparation[pre] = nullptr;
            }
        }
        else if (location.x >= MapSizeX[0] && location.x <= MapSizeX[4] && location.y >= MapSizeY[0]
<<<<<<< HEAD
            && location.y <= MapSizeY[4] && Lastposition.y >= 315)//�����ս�����϶�����ʼ����ս����
=======
                 && location.y <= MapSizeY[4]&&Lastposition.y>=315)//�����ս�����϶�����ʼ����ս����
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
        {
            Vec2 vec2 = getFightarrayposition(location);
            int x = vec2.x;
            int y = vec2.y;
<<<<<<< HEAD
            HeroPosition h1;
            h1.x = x;
            h1.y = y;
            Draging_hero->setHeroPosition(h1);
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
            int prex = getFightarrayposition(Lastposition).x;
            int prey = getFightarrayposition(Lastposition).y;//��ȡ�ƶ�֮ǰ������λ��
            if (Fightfield[x][y] != nullptr)//����
            {
<<<<<<< HEAD
                Draging_hero->setPosition(getmidposition(x, y));
=======
                Draging_hero->setPosition(getmidposition(x,y));
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
                Fightfield[x][y]->setPosition(Lastposition);
                Fightfield[prex][prey] = Fightfield[x][y];
                Fightfield[x][y] = Draging_hero;
            }
            else
            {
                Draging_hero->setPosition(getmidposition(x, y));
<<<<<<< HEAD
                Fightfield[prex][prey] = nullptr;
                Fightfield[x][y] = Draging_hero;
            }
        }
        else if (location.x >= PreparationsSizeX[0] && location.x <= PreparationsSizeX[9] && location.y >= PreparationsSizeY[0]
            && location.y <= PreparationsSizeY[1] && Lastposition.y >= 315)//�����սϯ�ڣ��϶�����ʼ����ս��
=======
                Fightfield[prex][prey] =nullptr;
                Fightfield[x][y] = Draging_hero;
            }
        }
        else if (location.x >= PreparationsSizeX[0] && location.x <= PreparationsSizeX[9] && location.y >= PreparationsSizeY[0] 
                 && location.y <= PreparationsSizeY[1] && Lastposition.y >= 315)//�����սϯ�ڣ��϶�����ʼ����ս��
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
        {
            int x = getPreparationarrayposition(location);
            int prex = getFightarrayposition(Lastposition).x;
            int prey = getFightarrayposition(Lastposition).y;//��ȡ�ƶ�֮ǰ������λ��
            if (Preparation[x] != nullptr)
            {
                Draging_hero->setPosition(getmidposition(x));
                Preparation[x]->setPosition(Lastposition);
                Fightfield[prex][prey] = Preparation[x];
                Preparation[x] = Draging_hero;
<<<<<<< HEAD
                
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
            }
            else
            {
                Draging_hero->setPosition(getmidposition(x));
                Preparation[x] = Draging_hero;
                Fightfield[prex][prey] = nullptr;
<<<<<<< HEAD
                chequers--;
                auto p1 = fightheros.find(Draging_hero);//��ȡָ������ָ��
                fightheros.erase(p1);//����ָ��ɾȥ
            }
        }
        else if (location.x >= MapSizeX[0] && location.x <= MapSizeX[4] && location.y >= MapSizeY[0]
            && location.y <= MapSizeY[4] && Lastposition.y <= 315)//�����ս���ϣ��϶�����ʼ���ڱ�սϯ��
=======
            }
        }
        else if (location.x >= MapSizeX[0] && location.x <= MapSizeX[4] && location.y >= MapSizeY[0]
            && location.y <= MapSizeY[4]&& Lastposition.y <= 315)//�����ս���ϣ��϶�����ʼ���ڱ�սϯ��
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
        {
            Vec2 vec2 = getFightarrayposition(location);
            int x = vec2.x;
            int y = vec2.y;
            int pre = getPreparationarrayposition(Lastposition);
            if (Fightfield[x][y] != nullptr)//����
            {
                Draging_hero->setPosition(getmidposition(x, y));
                Fightfield[x][y]->setPosition(Lastposition);
                Preparation[pre] = Fightfield[x][y];
                Fightfield[x][y] = Draging_hero;
            }
            else
            {
<<<<<<< HEAD
                if (HextechStatus == POPULATION)
                    MaxPeople = Level + 1;
                else
                    MaxPeople = Level;
                if (chequers < MaxPeople)
                {
                    Draging_hero->setPosition(getmidposition(x, y));
                    Preparation[pre] = nullptr;
                    Fightfield[x][y] = Draging_hero;
                    chequers++;
                    fightheros.pushBack(Draging_hero);
                }
                else
                {
                    Messagelabel->setString("The total number of chess pieces cannot exceed the population.");
                    Draging_hero->setPosition(Lastposition);
                }
            }
        }
        else if ((location.x >= 1370 && location.x <= 1477 && location.y >= (948 - 375) && location.y <= (948 - 300)))//�˴���ӳ�������
        {
            update_gold(Draging_hero->getvalue());//���½��
            if (Lastposition.y <= 315)//����Ǳ�սϯ
            {
                int pre = getPreparationarrayposition(Lastposition);
                HerosType[Draging_hero->getID() + 9 * (Draging_hero->getStar() - 1)]--;
                Draging_hero->removeFromParent();
                Preparation[pre] = nullptr;
            }
            else //�����ս��
            {
                int prex = getFightarrayposition(Lastposition).x;
                int prey = getFightarrayposition(Lastposition).y;//��ȡ�ƶ�֮ǰ������λ��
                chequers--;
                Draging_hero->removeFromParent();
                Fightfield[prex][prey] = nullptr;
            }
            
=======
                Draging_hero->setPosition(getmidposition(x, y));
                Preparation[pre] = nullptr;
                Fightfield[x][y] = Draging_hero;
            }
        }
        else if ((location.x >= 84 && location.x <= 188 && location.y >= (948-368) && location.y <= (948 - 290) || (location.x >= 1370
            && location.x <= 1477 && location.y >= (948 - 375) && location.y <= (948 - 300))))//�˴���ӳ�������
        {
            if (Lastposition.y <= 315)//����Ǳ�սϯ
             {
                int pre = getPreparationarrayposition(Lastposition);
                Draging_hero->removeFromParent();
                Preparation[pre] = nullptr;
             }
             else //�����ս��
             {
                int prex = getFightarrayposition(Lastposition).x;
                int prey = getFightarrayposition(Lastposition).y;//��ȡ�ƶ�֮ǰ������λ��
                Draging_hero->removeFromParent();
                Fightfield[prex][prey] = nullptr;
             }
             update_gold(Draging_hero->getCost());//���½��
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
        }
        else
        {
            Messagelabel->setString("You can only place the chess on the left half of the square or on the Preparation Seat.");
<<<<<<< HEAD
            Draging_hero->setPosition(Lastposition);
=======
            Draging_hero->setPosition( Lastposition);
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
        }
        isDragging = false;
        Lastposition = Vec2(0, 0);

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
/*������������������������������������������������������������������������*/
/*�����ǵ�ͼ��صĺ���*/
/*������������������������������������������������������������������������*/
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
<<<<<<< HEAD
    else if (location.x >= PreparationsSizeX[0] && location.x <= PreparationsSizeX[9] && location.y >= PreparationsSizeY[0] && location.y <= PreparationsSizeY[1])
=======
    else if(location.x >= PreparationsSizeX[0] && location.x <= PreparationsSizeX[9] && location.y >= PreparationsSizeY[0] && location.y <= PreparationsSizeY[1])
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
    {
        int i = 0;
        while (location.x > PreparationsSizeX[i])
        {
            i++;
        }
<<<<<<< HEAD
        return  getmidposition(i - 1);
    }
    else
    {
        return(Vec2(0, 0));
=======
        return  getmidposition(i-1);
    }
    else
    {
       
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
    }
}
Vec2 Littlehero::getmidposition(int x)
{
    Vec2 vec2;
    vec2.x = (PreparationsSizeX[x] + PreparationsSizeX[x + 1]) / 2;
    vec2.y = (PreparationsSizeY[1] + PreparationsSizeY[0]) / 2;
    return vec2;
}
Vec2 Littlehero::getFightarrayposition(Vec2 location)//�������귵�ط��ؾ��������ά���������ս����������
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
<<<<<<< HEAD
    return  Vec2(i - 1, j - 1);
=======
    return  Vec2(i-1,j-1);
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
}
int Littlehero::getPreparationarrayposition(Vec2 location)//�����������귵�ط��ؾ��������ά��������ı�սϯ��������
{
    int i = 0;
    while (location.x > PreparationsSizeX[i])
    {
        i++;
    }
    return  i - 1;
}
<<<<<<< HEAD

/*���Ǻ���*/
bool Littlehero::FindUpgradeHero(Hero*& hero1, Hero*& hero2, Hero*& hero3)//�ҵ����������ǵ�Ӣ����
{
    int ID;
   //�ҵ��������ǵ�����
    int k = 0;
    for (; k < 18; k++)
    {
        if (HerosType[k] == 3)
        {
            ID = k % 9;
            Hero* temp[3] = { nullptr,nullptr,nullptr };
            int index = 0;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    if (Fightfield[i][j] != nullptr)
                        if (Fightfield[i][j]->getID() == ID && Fightfield[i][j]->getStar() == k / 9 + 1)//���Ȱ�ս���ϵ���ѡΪһ��λ
                        {
                            if (index >= 1)
                                chequers--;
                            temp[index] = Fightfield[i][j];
                            Fightfield[i][j] = nullptr;
                            index++;
                        }
                }
            for (int i = 0; i < 9; i++)
                if (Preparation[i] != nullptr)
                    if (Preparation[i]->getID() == ID && Preparation[i]->getStar()==k/9+1)
                    {
                        temp[index] = Preparation[i];
                        Preparation[i] = nullptr;
                        index++;
                    }
            
            hero1 = temp[0];
            hero2 = temp[1];
            hero3 = temp[2];
            HerosType[k] = 0;
            return true;
        }
    }
    return false;
}
void Littlehero::CheckUpgrade(Hero* hero)
{
    Hero* h1;
    Hero* h2;
    Hero* h3;
    LHcontroler::getInstance()->getMyLittleHero()->HerosType[hero->getID()+9*(hero->getStar()-1)]++;
    if (LHcontroler::getInstance()->getMyLittleHero()->FindUpgradeHero(h1, h2, h3))//����п��Դ�һ���������ǵĻ�
    {
        //ִ�����Ƕ���
        auto heroTwoStart = h1->StarUp(h1, h2, h3);
        log("yes");
        h1->removeFromParent();
        h2->removeFromParent();
        h3->removeFromParent();
        //������Ӣ�۷ŵ���������
        if (heroTwoStart->getPosition().y > 315)//�����ս��
        {
            Vec2 vec2 = getFightarrayposition(heroTwoStart->getPosition());
            int x = vec2.x;
            int y = vec2.y;
            Fightfield[x][y] = heroTwoStart;
            fightheros.pushBack(heroTwoStart);
        }
        else
        {
            Preparation[getPreparationarrayposition(heroTwoStart->getPosition())] = heroTwoStart;
        }
        CheckUpgrade(heroTwoStart);
    }
}
/*��Ϸ���̵ĺ���*/
void LHcontroler::Godie(Node* layer)
{
    /*ʧ�ܶ���*/
    Gameover = 1;
    layer->removeAllChildren();
    auto Defeat = Sprite::create("Defeat.png");
    Defeat->setScale(2);
    auto closeItem = GCreator::getInstance()->createMenuItem("closeNormal.png", "closeSelected.png", CC_CALLBACK_1(LHcontroler::menuCloseCallback, this), 0, 0, 0, 0);
    closeItem->setScale(CloseitemSize.x / closeItem->getContentSize().width);
    closeItem->setPosition(EnditemPosition);
    Defeat->setPosition(DefeatPosition);
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    layer->addChild(menu, 1);
    layer->addChild(Defeat, 0);
}
void LHcontroler::menuCloseCallback(Ref* pSender)
{
    //clear the LHcontroller
    LHcontroler::clearInstance();
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
void LHcontroler::Govictory(Node* layer)
{
    /*ʤ������*/
    Gameover = 1;
    layer->removeAllChildren();
    auto Defeat = Sprite::create("Victor.png");
    Defeat->setScale(2);
    auto closeItem = GCreator::getInstance()->createMenuItem("closeNormal.png", "closeSelected.png", CC_CALLBACK_1(LHcontroler::menuCloseCallback, this), 0, 0, 0, 0);
    closeItem->setScale(CloseitemSize.x / closeItem->getContentSize().width);
    closeItem->setPosition(EnditemPosition);
    Defeat->setPosition(DefeatPosition);
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    layer->addChild(menu, 1);
    layer->addChild(Defeat, 0);
    int audioId = AudioEngine::play2d("victory.mp3", false);
}
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
