#include "Battlefield.h"
#include "Setting.h"
USING_NS_CC;

Scene* Battlefield::createScene()
{
    return Battlefield::create();
}

//调试：文件打开失败时的信息输出
static void problemLoading(const std::string filename)
{
    log("打开文件%s不成功！", filename);
}

bool Battlefield::init()
{
    if (!Scene::init())
        return false;

	//返回开始界面
    auto returnItem = createMenuItem("battlefieldToStartNormal.png", "battlefieldToStartSelected.png", CC_CALLBACK_1(Battlefield::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //进入设置
    auto setItem = createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(Battlefield::menuSetCallback, this), visibleSize.width - returnItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);

    //商店
    store = Store::create();    //创建但暂不渲染
    store->retain();
    auto storeItem = createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(Battlefield::menuStoreCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);

    //备战席位
    preparation = Preparation::create();  //创建后立即渲染
    addChild(preparation, 1);

    //棋盘

    auto menu = Menu::create(returnItem, setItem, storeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    //战场大背景
    auto map = MapData::create();
//添加人物信息图层
auto controler = LHcontroler::getInstance()->heros.at(0);
auto herolayer=controler->get_heroslayer();//初始化一下
if (map == nullptr)
{
    problemLoading("'battlefield.png'");
}
else if (herolayer==nullptr)
{
    problemLoading("herolayer is nullptr");
}
else
{
    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(map, 0,"map");
    this->addChild(herolayer, 2, "herolayer");
}
    return true;
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
        addChild(store, 2);
        store->setPosition(origin.x, origin.y);
    }
    else        //关闭商店
    {
        store->retain();
        removeChild(store, false);
    }

    store->reverseStatus();
    log("The store is %s now.", store->getStatus() ? "on" : "off");
}

MenuItemImage* Battlefield::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float x, const float y, const float anchorX, const float anchorY)
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

//模式选择器的单例对象
ModeSelector* s_SharedModeSelector = nullptr;

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

bool Board::init()
{
    if (!Layer::init())
        return false;

    return true;
}

bool Preparation::init()
{
    if (!Layer::init())
        return false;

    //渲染席位
    for (int i = 0; i < size; i++)
    {
        auto seat = Sprite::create(this->seat);
        if (seat == nullptr)
            problemLoading(this->seat);
        else
        {
            seat->setTag(i);    //用序号作标签，便于取定第i号备战席的位置
            //先调整图片尺寸以适应屏幕大小
            seat->setScale(Director::getInstance()->getVisibleSize().width / size / seat->getContentSize().width);
            seat->setPosition(seat->getContentSize().width * seat->getScale() * (0.5f + i), seat->getContentSize().height * seat->getScale() / 2);
            addChild(seat);
        }
    }

    return true;
}

void Preparation::placeHero(Hero* hero)
{
    hero->setPosition(getChildByTag(occupied)->getPosition());
    getParent()->addChild(hero, 2);
    occupied++;     //已占用席位计数器自增
}

bool Store::init()
{
    if (!Layer::init())
        return false;

    displayment = Store::randomDisplay();       //当前商店内容（英雄数据）

    Vector<MenuItem*> items;   //当前商店内容（显示按钮）

    for (Vector<Hero*>::iterator p = displayment.begin(); p != displayment.end(); p++)
    {
        auto images = (*p)->getImages();         //获取图像集
        auto item = createMenuItem(images.imageInStoreNormal, images.imageInStoreSelected, CC_CALLBACK_1(Store::purchaseCallback, this), 0.0f, visibleSize.height, 0.0f, 1.0f);   //先放到左上角
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //生成后再调整位置
        items.pushBack(item);
    }

    menu = Menu::createWithArray(items);
    menu->setPosition(origin.x, origin.y);
    addChild(menu, 2);
    return true;
}

//英雄池初始化
Vector<Hero*> Store::pool = { Example::create() };

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
    const int grade = LittleHero::getInstance()->getGrade();
    
    for (int i = 0; i < size; i++)
    {
        float sampleCost = random(0.0f, 100.0f);    //随机数模拟抽样（按费抽取）
        int j, total;
        for (j = total = 0; j < MAX_COST && (total += possibilityTable[grade - 1][j]) < sampleCost; j++)
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

bool Store::getStatus()
{
    return on;
}

void Store::reverseStatus()
{
    on = !on;
}

MenuItemImage* Store::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float x, const float y, const float anchorX, const float anchorY)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);

    if (item == nullptr || item->getContentSize().width <= 0 || item->getContentSize().height <= 0)
        problemLoading("'" + normalImage + "' and '" + selectedImage);
    else
    {
        item->setAnchorPoint({ anchorX, anchorY });
        item->setPosition(x, y);
    }

    return item;
}
