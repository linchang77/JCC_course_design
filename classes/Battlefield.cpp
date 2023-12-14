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
    store = Store::createLayer();    //创建但暂不渲染
    auto storeItem = createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(Battlefield::menuStoreCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);

    //备战席位
    preparation = Preparation::createLayer();  //创建后立即渲染
    addChild(preparation, 1);

    //棋盘

    auto menu = Menu::create(returnItem, setItem, storeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    //战场大背景
    auto sprite = Sprite::create("battlefield.png");
    if (sprite == nullptr)
    {
        problemLoading("'battlefield.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
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
    addChild(store);
    store->setPosition(visibleSize.width - store->getContentSize().width / 2, visibleSize.height - store->getContentSize().height / 2);
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

Layer* Board::createLayer()
{
    return Board::create();
}

bool Board::init()
{
    if (!Layer::init())
        return false;

    return true;
}

Layer* Preparation::createLayer()
{
    return Preparation::create();
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
            //先调整图片尺寸以适应屏幕大小
            seat->setScale(Director::getInstance()->getVisibleSize().width / size / seat->getContentSize().width);
            seat->setPosition(seat->getContentSize().width * seat->getScale() * (0.5f + i), seat->getContentSize().height * seat->getScale() / 2);
            addChild(seat);                                                                                        
        }
    }

    return true;
}

Layer* Store::createLayer()
{
    return Store::create();
}

bool Store::init()
{
    if (!Layer::init())
        return false;

    displayment = Store::randomDisplay();       //当前商店内容（英雄数据）

    for (Vector<Hero*>::iterator p = displayment.begin(); p != displayment.end(); p++)
    {
        auto images = (*p)->getImages();         //获取图像集
        auto item = createMenuItem(images.imageInStoreNormal, images.imageInStoreSelected, CC_CALLBACK_1(Store::purchaseCallback, this), 0.0f, 0.0f, 0.0f, 1.0f);   //先放到左上角
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //生成后再调整位置
        addChild(item);
    }

    return true;
}

Vector<Hero*> Store::randomDisplay()
{
    Vector<Hero*> result;
    const int grade = LittleHero::getInstance()->getGrade();
    
    for (int i = 0; i < size; i++)
    {
        float sampleCost = random(0.0f, 100.0f);    //随机数模拟抽样（按费抽取）
        int j, total;
        for (j = 0, total = 0; j < MAX_COST && (total += possibilityTable[grade][j]) < sampleCost; j++)
            ;
        //跳出循环时，j即抽取到的费用下标
        int sampleHero = random(0, int(pool[j].size() - 1));  //随机数模拟抽样（按英雄抽取）
        result.pushBack(pool[j].at(sampleHero));
    }

    return result;
}

void Store::purchaseCallback(Ref* pSender)
{
    const float pos = dynamic_cast<MenuItem*>(pSender)->convertToWorldSpace({ 0.0f, 1.0f }).x;    //获取被点中item在世界坐标系的横坐标
    const int good = pos / getChildByName("good1")->getContentSize().width;

    //good就是玩家购买的棋子在商店中的顺序（从左到右是0~4），后面的操作请棋子设计者实现
    log("您购买了英雄%s", displayment.at(good)->getName().data());
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
