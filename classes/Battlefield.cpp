#include "Battlefield.h"
#include "Setting.h"
#include "GeneralCreator.h"
#include "httpTransmission.h"
#include "fight.h"
#include "prepare.h"
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
    auto glView = Director::getInstance()->getOpenGLView();
    glView->setFrameSize(1600, 948);
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //���ؿ�ʼ����
    auto returnItem = GCreator::getInstance()->createMenuItem("battlefieldToStartNormal.png", "battlefieldToStartSelected.png", CC_CALLBACK_1(Battlefield::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //��������
    auto setItem = GCreator::getInstance()->createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(Battlefield::menuSetCallback, this), visibleSize.width - returnItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);
    setItem->setScale(SetitemSize.x / setItem->getContentSize().width);
    setItem->setPosition(1550, 948);
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
    auto preparelayer = prepare::getInstance();
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
        this->addChild(fightlayer, 3, "fightlayer");
        /*����G
             *LHcontroler::getInstance()->Godie(this);
             */
    }

    //��ս�׶ο�ʼ�����õ��ε�������ʱ
    scheduleOnce(CC_CALLBACK_1(Battlefield::dataExchange, this), prepareDuration, "dataExchange");

    return true;
}

void Battlefield::dataExchange(float dt)
{
    auto transmission = httpTransmission::getInstance();

    transmission->upload(this);
    transmission->download(this);
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

void Battlefield::preparationCallback(HttpClient* client, HttpResponse* response)
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
    buffer->push_back('\0');

    //����ظ�����
    httpTransmission::getInstance()->convert(buffer->data());
    //�����ССӢ�۵�enemyhero��ӵ�ս����
    //�����ǲ�������
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    Vector<Hero*> enemyFightingHeroes = littlehero->getEnemyFightingHeroes();
    for (Vector<Hero*>::iterator p = enemyFightingHeroes.begin(); p != enemyFightingHeroes.end(); p++)
        ;//����ѵз����Ӽӵ�ս����
    log("enemy's current Hp: %d", littlehero->getEnemyHp());

    //test
    log("%s", buffer->data());
}

Preparation* Preparation::create()
{
    Preparation* preparation = new (std::nothrow) Preparation;

    CCASSERT(preparation, "not enough memory.");
    return preparation;
}

void Preparation::placeHero(Hero* hero)
{
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
}

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
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //���ɺ��ٵ���λ��
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
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();

    if (dynamic_cast<Battlefield*>(getParent())->getCurrentPreparation()->is_full())   //������ϯ
        littlehero->set_message("The preparation seats are full!");
    else    //Ҳ����Թ���
    {
        MenuItem* chosenItem = dynamic_cast<MenuItem*>(pSender);                //��ѡ�е���Ʒ��ť
        const float pos = chosenItem->convertToWorldSpace({ 0.0f, 1.0f }).x;    //��ȡ������item����������ϵ�ĺ�����
        const int good = chosenItem->getName().back() - '0' - 1;

        //good������ҹ�����������̵��е�˳�򣨴�������0~4��
        if (littlehero->get_gold() - displayment.at(0)->getCost() < 0)    //�����ഢ
            littlehero->set_message("You're out of money!");
        else   //ȷʵ���Թ���
        {
            littlehero->update_gold(-displayment.at(0)->getCost());
            static_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentPreparation()->placeHero(displayment.at(good));    //��������Ⱦ����սϯ��
            chosenItem->removeFromParent();     //������Ʒ��ť���̵��Ƴ�������ֻ�Ǽ򵥵�remove������Ҫ�����ӵ�Ч��������ʵ�֣�
            log("you've purchased hero %s", displayment.at(good)->getName().data());
        }
    }
}

void Store::refreshCallback(Ref* pSender)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    
    if (littlehero->get_gold() - 2 < 0)    //�����ഢ
        littlehero->set_message("You're out of money!");
    else
    {
        //�������������Ʒ
        displayment = randomDisplay();

        //����˵�����
        menu->removeAllChildren();

        //���½������
        littlehero->update_gold(-2);

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
}

bool Store::getStatus()
{
    return on;
}

void Store::reverseStatus()
{
    on = !on;
}
