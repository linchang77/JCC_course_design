#include "Battlefield.h"
#include "Setting.h"
#include "GeneralCreator.h"
#include "httpTransmission.h"
USING_NS_CC;
using namespace network;

float Battlefield::prepareDuration = 1.0f;

Scene* Battlefield::createScene()
{
    return Battlefield::create();
}

bool Battlefield::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();

	//���ؿ�ʼ����
    auto returnItem = GCreator::getInstance()->createMenuItem("battlefieldToStartNormal.png", "battlefieldToStartSelected.png", CC_CALLBACK_1(Battlefield::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //��������
    auto setItem = GCreator::getInstance()->createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(Battlefield::menuSetCallback, this), visibleSize.width - returnItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);

    //�̵�
    store = Store::create();    //�������ݲ���Ⱦ
    store->retain();
    auto storeItem = GCreator::getInstance()->createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(Battlefield::menuStoreCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);

    //��սϯλ
    preparation = Preparation::create();

    //����

    auto menu = Menu::create(returnItem, setItem, storeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    //ս���󱳾�
	//���������Ϣͼ��
	auto controler = LHcontroler::getInstance()->getMyLittleHero();
	auto herolayer = controler->get_heroslayer();//��ʼ��һ��
    //���ս��ͼ��
    auto map = controler->get_MyMap();

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
	}

    //��ս�׶ο�ʼ�����õ��ε�������ʱ
    scheduleOnce(CC_CALLBACK_1(Battlefield::dataExchange, this), prepareDuration, "dataExchange");

    return true;
}

void Battlefield::dataExchange(float dt)
{
    auto transmission = httpTransmission::getInstance();

    //transmission->upload(this);
   // transmission->download(this);

    //�����ǵ����ô���
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    Vector<Hero*> enemyFightingHeroes = littlehero->getEnemyFightingHeroes();
    for (Vector<Hero*>::iterator p = enemyFightingHeroes.begin(); p != enemyFightingHeroes.end(); p++)
        addChild(*p);
    log("enemy's current Hp: %d", littlehero->getEnemyHp());
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
    {
        addChild(store, 1);
        store->setPosition(Vec2::ZERO);
    }
    else                        //�ر��̵�
    {
        store->retain();
        removeChild(store, false);
    }

    store->reverseStatus();
    log("The store is %s now.", store->getStatus() ? "on" : "off");
}

void Battlefield::heroesCallback(HttpClient* client, HttpResponse* response)
{
    if (response == nullptr)
    {
        log("no response");
        return;
    }

    /*
    if (!response->isSucceed())
    {
        log("error msg: %s", response->getErrorBuffer());
        return;
    }
    */

    //�������˻ظ�����
    std::vector<char>* buffer = response->getResponseData();
    long statusCode = response->getResponseCode();

    //���õз����ӱ�
    LHcontroler::getInstance()->getMyLittleHero()->setEnemyFightingHeroes(httpTransmission::getInstance()->stringToHeroData(buffer->data()));
}

void Battlefield::hpCallback(HttpClient* client, HttpResponse* response)
{
    if (response == nullptr)
    {
        log("no response");
        return;
    }

    /*
    if (!response->isSucceed())
    {
        log("error msg: %s", response->getErrorBuffer());
        return;
    }
    */

    //�������˻ظ�����
    std::vector<char>* buffer = response->getResponseData();
    long statusCode = response->getResponseCode();

    //���õз�Ѫ��
    LHcontroler::getInstance()->getMyLittleHero()->setEnemyHp(std::stoi(buffer->data()));
}

//ģʽѡ�����ĵ�������
static ModeSelector* s_SharedModeSelector = nullptr;

ModeSelector* ModeSelector::getInstance()
{
    if (!s_SharedModeSelector)
    {
        s_SharedModeSelector = new (std::nothrow) ModeSelector;
        CCASSERT(s_SharedModeSelector, "FATAL: Not enough memory");
        s_SharedModeSelector->mode = Practice;
        s_SharedModeSelector->scene = nullptr;
    }

    return s_SharedModeSelector;
}

bool ModeSelector::setMode(const Mode mode, Scene* scene)
{
    if (!this)
        log("ģʽѡ������δ��ʼ����");

    this->mode = mode;
    if (scene)
    {
        this->scene = scene;
        return true;
    }
    else
        return false;
}

Mode ModeSelector::getMode()
{
    return mode;
}

Preparation* Preparation::create()
{
    Preparation* preparation = new (std::nothrow) Preparation;

    CCASSERT(preparation, "not enough memory.");
    return preparation;
}

void Preparation::placeHero(Hero* hero)
{
    hero->setPosition(startingPoint.x + (occupied++) * seatWidth, startingPoint.y);
    auto heroesLayer = LHcontroler::getInstance()->getMyLittleHero()->get_heroslayer();
    hero->SetSpace(heroesLayer);
    heroesLayer->addChild(hero, 2);

    //��սϯ���������̵갴ť
    if (occupied == size)
        static_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentStore()->menuDisabled();
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
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //���ɺ��ٵ���λ��
        item->setScale(0.3f);
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
    
    return true;
}

//Ӣ�۳س�ʼ��
Vector<Hero*> Store::pool = { Golem::create() };

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
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //���ɺ��ٵ���λ��
        menu->addChild(item);
    }
}

bool Store::getStatus()
{
    return on;
}

void Store::reverseStatus()
{
    on = !on;
}

void Store::menuDisabled()
{
    menu->setEnabled(false);
    refresh->setEnabled(false);
}
