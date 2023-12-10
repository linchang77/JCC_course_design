#include "Setting.h"
USING_NS_CC;

Scene* Setting::createScene()
{
	return Setting::create();
}

//���ԣ��ļ���ʧ��ʱ����Ϣ���
static void problemLoading(const std::string filename)
{
	log("���ļ�%s���ɹ���", filename);
}

bool Setting::init()
{
	if (!Scene::init())
		return false;

	auto returnItem = MenuItemImage::create("settingToStartNormal.png", "settingToStartSelected.png", CC_CALLBACK_1(menuReturnCallback, this));	//���ؿ�ʼ����
    if (returnItem == nullptr || returnItem->getContentSize().width <= 0 || returnItem->getContentSize().height <= 0)
        problemLoading("'settingToStartNormal.png' and 'settingToStartSelected.png'");
    else
    {
        float x = origin.x + visibleSize.width - returnItem->getContentSize().width / 2;
        float y = origin.y + visibleSize.height - returnItem->getContentSize().height / 2;
        returnItem->setPosition(Vec2(x, y));
    }

    //����ѡ���
    Vector<MenuItem*> parameters = { returnItem };

    auto musicSwitch = MenuItemImage::create("musicSwitchOn.png", "musicSwitchSelected.png", CC_CALLBACK_1(musicSwitchCallback, this)); //���ֿ���
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