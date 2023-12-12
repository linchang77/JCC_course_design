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

<<<<<<< HEAD
    //���ؿ�ʼ����
	auto returnItem = createMenuItem("settingToStartNormal.png", "settingToStartSelected.png", CC_CALLBACK_1(Setting::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //����ѡ��֣�����ֻ��һ�����ֿ��أ�
    Vector<MenuItem*> items = { returnItem };

    auto musicSwitch = createMenuItem("musicSwitchOn.png", "musicSwitchSelected.png", CC_CALLBACK_1(Setting::musicSwitchCallback, this), (1 - 0.618f) * visibleSize.width, 0.618f * visibleSize.height); //���ֿ���
    musicSwitch->setName("music");
    items.pushBack(musicSwitch);
    auto musicLabel = createLabel("MUSIC", "fonts/Marker Felt.ttf", 16, (1 - 0.618f) * visibleSize.width - musicSwitch->getContentSize().width / 2, 0.618f * visibleSize.height, 1.0f);
    addChild(musicLabel, 1);

    //�˵���������Ⱦ
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    menu->setName("menu");
    addChild(menu, 1);
=======
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
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2

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

<<<<<<< HEAD
MenuItemImage* Setting::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float x, const float y, const float anchorX, const float anchorY)
=======
MenuItemImage* Setting::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, float x, float y)
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

    return item;
}

Label* Setting::createLabel(const std::string& text, const std::string& font, const float fontSize, const float x, const float y, const float anchorX, const float anchorY)
{
    //��ʱֻʵ����TTF�ı���ǩ
    auto label = Label::createWithTTF(text, font, fontSize);
    if (label == nullptr)
    {
        problemLoading("'" + font + "'");
    }
    else
    {
        label->setAnchorPoint({ anchorX, anchorY });
        label->setPosition(origin.x + x, origin.y + y);
    }

    return label;
=======
        item->setPosition(origin.x + x - item->getContentSize().width / 2, origin.y + y - item->getContentSize().height / 2);

    return item;
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
}