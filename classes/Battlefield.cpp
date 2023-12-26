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

	//返回开始界面
    auto returnItem = GCreator::getInstance()->createMenuItem("battlefieldToStartNormal.png", "battlefieldToStartSelected.png", CC_CALLBACK_1(Battlefield::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //进入设置
    auto setItem = GCreator::getInstance()->createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(Battlefield::menuSetCallback, this), visibleSize.width - returnItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);

    //商店
    store = Store::create();    //创建但暂不渲染
    store->retain();
    auto storeItem = GCreator::getInstance()->createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(Battlefield::menuStoreCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);

    //备战席位
    preparation = Preparation::create();

    //棋盘

    auto menu = Menu::create(returnItem, setItem, storeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    //战场大背景
	//添加人物信息图层
	auto controler = LHcontroler::getInstance()->getMyLittleHero();
	auto herolayer = controler->get_heroslayer();//初始化一下
    //添加战场图层
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

    //备战阶段开始，启用单次调度器计时
    scheduleOnce(CC_CALLBACK_1(Battlefield::dataExchange, this), prepareDuration, "dataExchange");

    return true;
}

void Battlefield::dataExchange(float dt)
{
    auto transmission = httpTransmission::getInstance();

    //transmission->upload(this);
   // transmission->download(this);

    //下面是调试用代码
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
    //设置界面应否做成单例？
    auto setting = Setting::createScene();
    Director::getInstance()->pushScene(setting);
}

void Battlefield::menuStoreCallback(Ref* pSender)
{
    if (!store->getStatus())    //打开商店
    {
        addChild(store, 1);
        store->setPosition(Vec2::ZERO);
    }
    else                        //关闭商店
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

    //服务器端回复内容
    std::vector<char>* buffer = response->getResponseData();
    long statusCode = response->getResponseCode();

    //设置敌方棋子表
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

    //服务器端回复内容
    std::vector<char>* buffer = response->getResponseData();
    long statusCode = response->getResponseCode();

    //设置敌方血量
    LHcontroler::getInstance()->getMyLittleHero()->setEnemyHp(std::stoi(buffer->data()));
}

//模式选择器的单例对象
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
        log("模式选择器尚未初始化！");

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

    //备战席满，禁用商店按钮
    if (occupied == size)
        static_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentStore()->menuDisabled();
}

bool Store::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    /*添加商店背景*/
    background = GCreator::getInstance()->createSprite("herolayer/Shopbackground.png", 0.0f, 0.0f, 0.0f, 0.0f);
    background->setContentSize(Size(1600.0f, 948.0f));
    background->setOpacity(200);
    background->setPosition(Vec2::ZERO);
    addChild(background, 1);

    displayment = Store::randomDisplay();       //当前商店内容（英雄数据）

    Vector<MenuItem*> items;   //当前商店内容（显示按钮）

    //商品按钮
    for (Vector<Hero*>::iterator p = displayment.begin(); p != displayment.end(); p++)
    {
        auto images = (*p)->getImages();         //获取图像集
        auto item = GCreator::getInstance()->createMenuItem(images.imageInStoreNormal, images.imageInStoreSelected, CC_CALLBACK_1(Store::purchaseCallback, this), 0.0f, 0.0, 0.0f, 0.0f);   //先放到左下角
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //生成后再调整位置
        item->setScale(0.3f);
        items.pushBack(item);
    }

    //菜单创建
    menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 2);

    //刷新按钮
    auto refreshItem = GCreator::getInstance()->createMenuItem("refreshNormal.png", "refreshSelected.png", CC_CALLBACK_1(Store::refreshCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);    //先放到右下角
    refreshItem->setPositionY(refreshItem->getContentSize().height);
    refresh = Menu::createWithItem(refreshItem);
    refresh->setPosition(Vec2::ZERO);
    addChild(refresh, 2);
    
    return true;
}

//英雄池初始化
Vector<Hero*> Store::pool = { Golem::create() };

bool Store::addHero(Hero* newHero)
{
	if (pool.contains(newHero))  //若待添加英雄指针已在池中，则不再重复添加
		return false;

    pool.pushBack(newHero);
    return true;
}

bool Store::removeHero(Hero* toBeRemoved)
{
	if (pool.contains(toBeRemoved)) //若待添加英雄指针已在池中，才进行删除
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
        float sampleCost = random(0.0f, 100.0f);    //随机数模拟抽样（按费抽取）
        int j, total;
        for (j = total = 0; j < MAX_COST && (total += possibilityTable[level - 1][j]) < sampleCost; j++)
            ;
        //跳出循环时，j即抽取到的费用下标，j+1即抽取到的费用
        log("get cost %d", j + 1);
        int sampleHero = random(1, countHeroByCost(j + 1));     //随机数模拟抽样（按英雄抽取）
        result.pushBack(getHeroByCost(j + 1, sampleHero));      //抽取结果放入结果序列中
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
    Hero* copy = nullptr;   //返回拷贝

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
    MenuItem* chosenItem = dynamic_cast<MenuItem*>(pSender);    //被选中的商品按钮
    const float pos = chosenItem->convertToWorldSpace({ 0.0f, 1.0f }).x;    //获取被点中item在世界坐标系的横坐标
    const int good = chosenItem->getName().back() - '0' - 1;

    //good就是玩家购买的棋子在商店中的顺序（从左到右是0~4），后面的操作请棋子设计者实现
    static_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentPreparation()->placeHero(displayment.at(good));    //将棋子渲染到备战席上
    chosenItem->removeFromParent();     //该项商品按钮从商店移除（现在只是简单的remove，若需要更复杂的效果请自行实现）
    log("you've purchased hero %s", displayment.at(good)->getName().data());
}

void Store::refreshCallback(Ref* pSender)
{
    //重新随机生成商品
    displayment = randomDisplay();

    //清除菜单内容
    menu->removeAllChildren();

    //重新渲染商品按钮
    for (Vector<Hero*>::iterator p = displayment.begin(); p != displayment.end(); p++)
    {
        auto images = (*p)->getImages();         //获取图像集
        auto item = GCreator::getInstance()->createMenuItem(images.imageInStoreNormal, images.imageInStoreSelected, CC_CALLBACK_1(Store::purchaseCallback, this), 0.0f, 0.0f, 0.0f, 0.0f);   //先放到坐下角
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //生成后再调整位置
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
