#include "Setting.h"
USING_NS_CC;

Scene* Setting::createScene()
{
	return Setting::create();
}

//调试：文件打开失败时的信息输出
static void problemLoading(const std::string filename)
{
	log("打开文件%s不成功！", filename);
}

bool Setting::init()
{
	if (!Scene::init())
		return false;

	auto returnItem = MenuItemImage::create("settingToStartNormal.png", "settingToStartSelected.png", CC_CALLBACK_1(menuReturnCallback, this));	//返回开始界面
    if (returnItem == nullptr || returnItem->getContentSize().width <= 0 || returnItem->getContentSize().height <= 0)
        problemLoading("'settingToStartNormal.png' and 'settingToStartSelected.png'");
    else
    {
        float x = origin.x + visibleSize.width - returnItem->getContentSize().width / 2;
        float y = origin.y + visibleSize.height - returnItem->getContentSize().height / 2;
        returnItem->setPosition(Vec2(x, y));
    }

    //设置选项部分
    Vector<MenuItem*> parameters = { returnItem };

    auto musicSwitch = MenuItemImage::create("musicSwitchOn.png", "musicSwitchSelected.png", CC_CALLBACK_1(musicSwitchCallback, this)); //音乐开关
    musicSwitch->setName("music");
    parameters.pushBack(musicSwitch);


    auto menu = Menu::createWithArray(parameters);
    menu->setName("menu");
    addChild(menu);

    return true;
}

void Setting::menuReturnCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void Setting::musicSwitchCallback(Ref* pSender)
{
    static bool recentStatus = music;

    music = !recentStatus;
    recentStatus = music;
    
    //
    auto menu = getChildByName("menu");
    auto _switch = menu->getChildByName("music");
}

MenuItemImage* Setting::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, float x, float y)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);

    if (item == nullptr || item->getContentSize().width <= 0 || item->getContentSize().height <= 0)
        problemLoading("'" + normalImage + "' and '" + selectedImage);
    else
        item->setPosition(origin.x + x - item->getContentSize().width / 2, origin.y + y - item->getContentSize().height / 2);

    return item;
}