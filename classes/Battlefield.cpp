#include "Battlefield.h"
#include "Setting.h"
#include "GeneralCreator.h"
#include "httpTransmission.h"
<<<<<<< HEAD
#include "fight.h"
#include "prepare.h"
#include "Hextech.h"
=======
#include "Littlehero.h"
#include "prepare.h"
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
USING_NS_CC;
using namespace network;

Scene* Battlefield::createScene()
{
    return Battlefield::create();
}

bool Battlefield::init()
{
    if (!Scene::init())
        return false;
    auto glView = Director::getInstance()->getOpenGLView();
    glView->setFrameSize(1600, 948);
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //���ؿ�ʼ����
    auto returnItem = GCreator::getInstance()->createMenuItem("battlefieldToStartNormal.png", "battlefieldToStartSelected.png", CC_CALLBACK_1(Battlefield::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //��������
    auto setItem = GCreator::getInstance()->createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(Battlefield::menuSetCallback, this), visibleSize.width - returnItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);
    setItem->setScale(SetitemSize.x / setItem->getContentSize().width);
    setItem->setPosition(visibleSize.width, visibleSize.height);

    //�̵�
    store = Store::create();    //�������ݲ���Ⱦ
    store->setPosition(Vec2::ZERO);
    store->retain();
    auto storeItem = GCreator::getInstance()->createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(Battlefield::menuStoreCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);
    storeItem->setName("storeItem");

    //��սϯλ
    preparation = Preparation::create();

    //����ҳ��
    auto skillsIntroItem = GCreator::getInstance()->createMenuItem("skillsNormal.png", "skillsSelected.png", CC_CALLBACK_1(Battlefield::menuIntroductionCallback, this), visibleSize.width, 320.0f, 1.0f, 0.0f);
    auto trammelsIntroItem = GCreator::getInstance()->createMenuItem("trammelsNormal.png", "trammelsSelected.png", CC_CALLBACK_1(Battlefield::menuIntroductionCallback, this), visibleSize.width, 220.0f, 1.0f, 0.0f);

    auto menu = Menu::create(setItem, storeItem, skillsIntroItem, trammelsIntroItem, NULL);
    menu->setName("menu");
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    //ս���󱳾�
    //���������Ϣͼ��
    auto controler = LHcontroler::getInstance()->getMyLittleHero();
    auto herolayer = controler->get_heroslayer();//��ʼ��һ��
    //���ս��ͼ��
    auto map = controler->get_MyMap();
    auto preparelayer = prepare::getInstance();
<<<<<<< HEAD
    auto fightlayer = fight::getInstance();
    auto hextechlayer = Hextech::create();

    if (map == nullptr)
    {
        GCreator::problemLoading("'battlefield.png'");
    }
    else if (herolayer == nullptr)
    {
        GCreator::problemLoading("herolayer is nullptr");
    }
    else
    {
        // position the sprite on the center of the screen
        //sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(map, 0, "map");
        this->addChild(herolayer, 2, "herolayer");
        this->addChild(preparelayer, 2, "preparelayer");
        this->addChild(fightlayer, 3, "fightlayer");
        this->addChild(hextechlayer, 4, "hextechlayer");
        /*����G
             *LHcontroler::getInstance()->Godie(this);
             */
    }
=======
    auto fightlayer = fight::create();
	if (map == nullptr)
	{
		GCreator::problemLoading("'battlefield.png'");
	}
	else if (herolayer == nullptr)
	{
		GCreator::problemLoading("herolayer is nullptr");
	}
	else
	{
		// position the sprite on the center of the screen
		//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(map, 0, "map");
		this->addChild(herolayer, 2, "herolayer");
        this->addChild(preparelayer, 2, "preparelayer");
        this->addChild(fightlayer, 2, "fightlayer");
	}

    //��ս�׶ο�ʼ�����õ��ε�������ʱ
    scheduleOnce(CC_CALLBACK_1(Battlefield::dataExchange, this), prepareDuration, "dataExchange");
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c

    return true;
}

void Battlefield::pendCallback(float dt)
{
    httpTransmission::getInstance()->download(this);
}

Store* Battlefield::getCurrentStore()
{
    return store;
}

Preparation* Battlefield::getCurrentPreparation()
{
    return preparation;
}

void Battlefield::menuReturnCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void Battlefield::menuSetCallback(Ref* pSender)
{
    //���ý���Ӧ�����ɵ�����
    auto setting = Setting::createScene();
    Director::getInstance()->pushScene(setting);
}

void Battlefield::menuStoreCallback(Ref* pSender)
{
    if (!store->getStatus())    //���̵�
        addChild(store, 1);
    else                        //�ر��̵�
    {
        store->retain();
        removeChild(store, false);
    }

    store->reverseStatus();
    log("The store is %s now.", store->getStatus() ? "on" : "off");
}

void Battlefield::menuIntroductionCallback(Ref* pSender)
{
    auto click = dynamic_cast<MenuItem*>(pSender)->convertToWorldSpace({ 1.0f, 0.0f }); //�����еİ�ť�����½�����������ϵ�е�����

    if (introduction == nullptr)    //�򿪽���ҳ��
    {
        introduction = click.y > 300.0f ? Skills::createLayer() : Trammels::createLayer();  //���ݵ��λ���ж�Ҫ���ĸ�����ҳ��
        addChild(introduction, 3, "intro");
    }
    else                            //�رս���ҳ��
    {
        removeChild(introduction);
        introduction = nullptr;
    }
}

void Battlefield::uploadCallback(HttpClient* sender, HttpResponse* response)
{
    if (response == nullptr)
    {
        log("no response");
        return;
    }
    scheduleOnce(CC_CALLBACK_1(Battlefield::pendCallback, this), 0.5f, "loadingPend");
}

void Battlefield::downloadCallback(HttpClient* sender, HttpResponse* response)
{
    if (response == nullptr)
    {
        log("no response");
        return;
    }

    std::vector<char>* buffer = response->getResponseData();
    buffer->push_back('\0');

    log("into download callback.");
    httpTransmission::getInstance()->convert(buffer->data());

}

Preparation* Preparation::create()
{
    Preparation* preparation = new (std::nothrow) Preparation;

    CCASSERT(preparation, "not enough memory.");
    return preparation;
}

void Preparation::placeHero(Hero* hero)
{
<<<<<<< HEAD
    int i;
    for (i = 0; i < 9; i++)
    {
        if (!LHcontroler::getInstance()->getMyLittleHero()->Preparation[i])
            break;
    }
    hero->setPosition(startingPoint.x + i * seatWidth, startingPoint.y);
    LHcontroler::getInstance()->getMyLittleHero()->addhero(hero, i + 1);
    auto prepareLayer = prepare::getInstance();
    hero->SetSpace(prepareLayer);
    prepareLayer->addChild(hero, 2);
    LHcontroler::getInstance()->getMyLittleHero()->CheckUpgrade(hero);//�ж��Ƿ���Ҫ����
}
=======
    hero->setPosition(startingPoint.x + (occupied++) * seatWidth, startingPoint.y);
    //�����޸ĵĽ�Ӣ�ۼ��뵽׼��ͼ�㣬ͬʱ�����˽�Ӣ�۷ŵ���սϯ����
    LHcontroler::getInstance()->getMyLittleHero()->addhero(hero, occupied);
    auto heroesLayer = LHcontroler::getInstance()->getMyLittleHero()->get_heroslayer();
    hero->SetSpace(heroesLayer);
    heroesLayer->addChild(hero, 2);
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c

bool Preparation::is_full()
{
    int i;
    for (i = 0; i < 9; i++)
    {
        if (!LHcontroler::getInstance()->getMyLittleHero()->Preparation[i])
            return false;
    }
    return true;
}

bool Store::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    /*����̵걳��*/
    background = GCreator::getInstance()->createSprite("herolayer/Shopbackground.png", 0.0f, 0.0f, 0.0f, 0.0f);
    background->setContentSize(Size(1600.0f, 948.0f));
    background->setOpacity(200);
    background->setPosition(Vec2::ZERO);
    addChild(background, 1);

    displayment = Store::randomDisplay();       //��ǰ�̵����ݣ�Ӣ�����ݣ�

    Vector<MenuItem*> items;   //��ǰ�̵����ݣ���ʾ��ť��

    //��Ʒ��ť
    for (Vector<Hero*>::iterator p = displayment.begin(); p != displayment.end(); p++)
    {
        auto images = (*p)->getImages();         //��ȡͼ��
        auto item = GCreator::getInstance()->createMenuItem(images.imageInStoreNormal, images.imageInStoreSelected, CC_CALLBACK_1(Store::purchaseCallback, this), 0.0f, 0.0, 0.0f, 0.0f);   //�ȷŵ����½�
        item->setScale(1.44f);
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * (item->getContentSize().width*1.44f+50));   //���ɺ��ٵ���λ��
        items.pushBack(item);
    }

    //�˵�����
    menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 2);

    //ˢ�°�ť
    auto refreshItem = GCreator::getInstance()->createMenuItem("refreshNormal.png", "refreshSelected.png", CC_CALLBACK_1(Store::refreshCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);    //�ȷŵ����½�
    refreshItem->setPositionY(refreshItem->getContentSize().height);
    refresh = Menu::createWithItem(refreshItem);
    refresh->setPosition(Vec2::ZERO);
    addChild(refresh, 2);
    
    //������ʾ��ǩ
    const int level = LHcontroler::getInstance()->getMyLittleHero()->getLevel();
    auto probability = GCreator::getInstance()->createLabel("Probability: 1-" + std::to_string(possibilityTable[level - 1][0]) + "%      2-" + std::to_string(possibilityTable[level - 1][1]) + "%      3-" + std::to_string(possibilityTable[level - 1][2]) + "%", "fonts/Marker Felt.ttf", 16.0f, 1000.0f, 200.0f);
    probability->setName("probability");
    addChild(probability);

    return true;
}

void Store::ChangePossibility()
{
    removeChildByName("probability");

    const int level = LHcontroler::getInstance()->getMyLittleHero()->getLevel();
    auto probability = GCreator::getInstance()->createLabel("Probability: 1-" + std::to_string(possibilityTable[level - 1][0]) + "%      2-" + std::to_string(possibilityTable[level - 1][1]) + "%      3-" + std::to_string(possibilityTable[level - 1][2]) + "%", "fonts/Marker Felt.ttf", 16.0f, 1000, 200);

    probability->setName("probability");
    addChild(probability);
    return;
}

//Ӣ�۳س�ʼ��
Vector<Hero*> Store::pool = { Golem::create(), Ninja::create(),Goblin::create(),King::create(), Pirate::create(), Fairy::create(), Archer::create(),Wizard::create(),Mummy::create()};

bool Store::addHero(Hero* newHero)
{
	if (pool.contains(newHero))  //�������Ӣ��ָ�����ڳ��У������ظ����
		return false;

    pool.pushBack(newHero);
    return true;
}

bool Store::removeHero(Hero* toBeRemoved)
{
	if (pool.contains(toBeRemoved)) //�������Ӣ��ָ�����ڳ��У��Ž���ɾ��
    {
		pool.eraseObject(toBeRemoved);
		return true;
	}

    return false;
}

Vector<Hero*> Store::randomDisplay()
{
    Vector<Hero*> result;
    const int level = LHcontroler::getInstance()->getMyLittleHero()->getLevel();
    
    for (int i = 0; i < size; i++)
    {
        float sampleCost = random(0.0f, 100.0f);    //�����ģ����������ѳ�ȡ��
        int j, total;
        for (j = total = 0; j < MAX_COST && (total += possibilityTable[level - 1][j]) < sampleCost; j++)
            ;
        //����ѭ��ʱ��j����ȡ���ķ����±꣬j+1����ȡ���ķ���
        log("get cost %d", j + 1);
        int sampleHero = random(1, countHeroByCost(j + 1));     //�����ģ���������Ӣ�۳�ȡ��
        result.pushBack(getHeroByCost(j + 1, sampleHero));      //��ȡ���������������
    }

    return result;
}

int Store::countHeroByCost(const int cost)
{
    int count = 0;

    for (Vector<Hero*>::iterator p = pool.begin(); p != pool.end(); p++)
        if ((*p)->getCost() == cost)
            count++;

    return count;
}

Hero* Store::getHeroByCost(const int cost, const int i)
{
    int count = 0;
    Hero* copy = nullptr;   //���ؿ���

    for (Vector<Hero*>::iterator p = pool.begin(); p != pool.end(); p++)
    {
        if ((*p)->getCost() == cost)
            count++;
        if (count == i)
        {
            copy = Hero::copy(*p);
            break;
        }
    }

    return copy;
}

<<<<<<< HEAD
void Store::Refresh()
=======
void Store::purchaseCallback(Ref* pSender)
{
    MenuItem* chosenItem = dynamic_cast<MenuItem*>(pSender);    //��ѡ�е���Ʒ��ť
    const float pos = chosenItem->convertToWorldSpace({ 0.0f, 1.0f }).x;    //��ȡ������item����������ϵ�ĺ�����
    const int good = chosenItem->getName().back() - '0' - 1;

    //good������ҹ�����������̵��е�˳�򣨴�������0~4��������Ĳ��������������ʵ��
    static_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentPreparation()->placeHero(displayment.at(good));    //��������Ⱦ����սϯ��
   
    chosenItem->removeFromParent();     //������Ʒ��ť���̵��Ƴ�������ֻ�Ǽ򵥵�remove������Ҫ�����ӵ�Ч��������ʵ�֣�
    log("you've purchased hero %s", displayment.at(good)->getName().data());
}

void Store::refreshCallback(Ref* pSender)
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
{
    //�������������Ʒ
    displayment = randomDisplay();

    //����˵�����
    menu->removeAllChildren();

    //������Ⱦ��Ʒ��ť
    for (Vector<Hero*>::iterator p = displayment.begin(); p != displayment.end(); p++)
    {
        auto images = (*p)->getImages();         //��ȡͼ��
        auto item = GCreator::getInstance()->createMenuItem(images.imageInStoreNormal, images.imageInStoreSelected, CC_CALLBACK_1(Store::purchaseCallback, this), 0.0f, 0.0f, 0.0f, 0.0f);   //�ȷŵ����½�
        item->setScale(1.44f);
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * (item->getContentSize().width * 1.44f + 50));    //���ɺ��ٵ���λ��
        menu->addChild(item);
    }
}

void Store::purchaseCallback(Ref* pSender)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();

    if (dynamic_cast<Battlefield*>(getParent())->getCurrentPreparation()->is_full())   //������ϯ
        littlehero->set_message("The preparation seats are full!");
    else    //Ҳ����Թ���
    {
        MenuItem* chosenItem = dynamic_cast<MenuItem*>(pSender);    //��ѡ�е���Ʒ��ť
        const int good = chosenItem->getName().back() - '0' - 1;    //��ҹ�����������̵��е�˳�򣨴�������0~4��
        
        if (littlehero->get_gold() - displayment.at(good)->getCost() < 0)    //�����ഢ
            littlehero->set_message("You're out of money!");
        else   //ȷʵ���Թ���
        {
            littlehero->update_gold(-displayment.at(good)->getCost());
            static_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentPreparation()->placeHero(displayment.at(good));    //��������Ⱦ����սϯ��
            chosenItem->removeFromParent();     //������Ʒ��ť���̵��Ƴ�������ֻ�Ǽ򵥵�remove������Ҫ�����ӵ�Ч��������ʵ�֣�
            log("you've purchased hero %s", displayment.at(good)->getName().data());
        }
    }
}

void Store::refreshCallback(Ref* pSender)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();

    //���½������
    if (littlehero->get_gold() - 2 < 0)    //�����ഢ
        littlehero->set_message("You're out of money!"); 
    littlehero->update_gold(-2);
    
    //ˢ���̵�����
    Refresh();
}

bool Store::getStatus()
{
    return on;
}

void Store::reverseStatus()
{
    on = !on;
}

bool Introduction::init()
{
    if (!Layer::init())
        return false;
    return true;
}

Introduction* Skills::createLayer()
{
    return Skills::create();
}

bool Skills::init()
{
    if (!Introduction::init())
        return false;

    auto intro = GCreator::getInstance()->createSprite("skillsIntro.png", visibleSize.width / 2, visibleSize.height / 2);
    intro->setScale(0.6f);
    addChild(intro);

    setPosition(Vec2::ZERO);    //ͼ��Ĭ�Ϸŵ����½�

    return true;
}

Introduction* Trammels::createLayer()
{
    return Trammels::create();
}

bool Trammels::init()
{
    if (!Introduction::init())
        return false;

    auto intro = GCreator::getInstance()->createSprite("trammelsIntro.png", visibleSize.width / 2, visibleSize.height / 2); //λ���Լ�����
    intro->setScale(0.75f);
    addChild(intro);

    setPosition(Vec2::ZERO);    //ͼ��Ĭ�Ϸŵ����½�

    return true;
}
