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
<<<<<<< HEAD
    auto returnItem = createMenuItem("battlefieldToStartNormal.png", "battlefieldToStartSelected.png", CC_CALLBACK_1(Battlefield::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //进入设置
    auto setItem = createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(Battlefield::menuSetCallback, this), visibleSize.width - returnItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);

    //商店
    store = Store::create();    //创建但暂不渲染
    auto storeItem = createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(Battlefield::menuStoreCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);

    //备战席位
    preparation = Preparation::createLayer();  //创建后立即渲染
    addChild(preparation, 1);
=======
    auto returnItem = createMenuItem("settingToStartNormal.png", "settingToStartSelected.png", CC_CALLBACK_1(menuReturnCallback, this), visibleSize.width, visibleSize.height);

    //进入设置
    auto setItem = createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(menuSetCallback, this), visibleSize.width - returnItem->getContentSize().width, visibleSize.height);

    //商店
    store = Store::create();    //创建但暂不渲染
    auto storeItem = createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(menuStoreCallback, this), visibleSize.width, 0);

    //备战席位
    preparation = Preparation::createLayer();  //创建后立即渲染
    
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2

    //棋盘

    auto menu = Menu::create(returnItem, setItem, storeItem, NULL);
<<<<<<< HEAD
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
=======
    addChild(menu);

>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
    return true;
}

void Battlefield::menuReturnCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void Battlefield::menuSetCallback(Ref* pSender)
{
    //设置界面应否做成单例？
<<<<<<< HEAD
    auto setting = Setting::createScene();
=======
    static auto setting = Setting::createScene();
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
    Director::getInstance()->pushScene(setting);
}

void Battlefield::menuStoreCallback(Ref* pSender)
{
    addChild(store);
    store->setPosition(visibleSize.width - store->getContentSize().width / 2, visibleSize.height - store->getContentSize().height / 2);
}

<<<<<<< HEAD
MenuItemImage* Battlefield::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float x, const float y, const float anchorX, const float anchorY)
=======
MenuItemImage* Battlefield::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, float x, float y)
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);

    if (item == nullptr || item->getContentSize().width <= 0 || item->getContentSize().height <= 0)
        problemLoading("'" + normalImage + "' and '" + selectedImage);
    else
<<<<<<< HEAD
    {
        item->setAnchorPoint({ anchorX, anchorY });
        item->setPosition(origin.x + x, origin.y + y);
    }
=======
        item->setPosition(origin.x + x - item->getContentSize().width / 2, origin.y + y - item->getContentSize().height / 2);
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2

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
<<<<<<< HEAD
    if (!Layer::init())
        return false;

    return true;
=======

>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
}

Layer* Preparation::createLayer()
{
    return Preparation::create();
}

bool Preparation::init()
{
    if (!Layer::init())
        return false;

<<<<<<< HEAD
=======
    //计算备战席尺寸（待完善）
    size = MaxSize;

>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
    //渲染席位
    for (int i = 0; i < size; i++)
    {
        auto seat = Sprite::create(this->seat);
        if (seat == nullptr)
            problemLoading(this->seat);
        else
        {
<<<<<<< HEAD
            //先调整图片尺寸以适应屏幕大小
            seat->setScale(Director::getInstance()->getVisibleSize().width / size / seat->getContentSize().width);
            seat->setPosition(seat->getContentSize().width * seat->getScale() * (0.5f + i), seat->getContentSize().height * seat->getScale() / 2);
            addChild(seat);                                                                                        
        }
    }

    return true;
=======
            seat->setPosition(seat->getContentSize().height / 2, seat->getContentSize().width * (0.5 + i));
            addChild(seat);
        }
    }
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
}
