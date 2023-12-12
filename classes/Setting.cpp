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

    //���ؿ�ʼ����
	auto returnItem = createMenuItem("settingToStartNormal.png", "settingToStartSelected.png", CC_CALLBACK_1(Setting::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //����ѡ��֣�����ֻ��һ�����ֿ��أ�
    Vector<MenuItem*> items = { returnItem };

    auto musicSwitch = setParameter(Music, "musicSwitchOn.png", "musicSwitchSelected.png", CC_CALLBACK_1(Setting::musicSwitchCallback, this), (1 - 0.618f) * visibleSize.width, 0.618f * visibleSize.height); //���ֿ���
    items.pushBack(musicSwitch);

    //�˵���������Ⱦ
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    menu->setName("menu");
    addChild(menu, 1);

    return true;
}

void Setting::menuReturnCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void Setting::musicSwitchCallback(Ref* pSender)
{
    bool music = SettingParameters::getInstance()->getValue(Music);     //ע�⣺���ǵ��ǰ��ѡ��״̬
    SettingParameters::getInstance()->setValue(Music, !music);          //ѡ���÷�
    
    if (!music) //���ǰ�رգ�������Ϊ����״̬
    {
        auto swoosh = createSprite("swoosh.png", (1 - 0.618f) * visibleSize.width, 0.618f * visibleSize.height);
        swoosh->setName("musicSwoosh");
        addChild(swoosh, 1);
    }
    else
    {
        auto swoosh = getChildByName("musicSwoosh");
        swoosh->removeFromParent();
    }

    log("Music is %s now.", !music ? "on" : "off");
}

MenuItemImage* Setting::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float x, const float y, const float anchorX, const float anchorY)
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
}

Sprite* Setting::createSprite(const std::string& image, const float x, const float y, const float anchorX, const float anchorY)
{
    auto sprite = Sprite::create(image);
    if (sprite == nullptr)
        problemLoading(image);
    else
    {
        sprite->setAnchorPoint({ anchorX, anchorY });
        sprite->setPosition(origin.x + x, origin.y + y);
    }

    return sprite;
}

MenuItemImage* Setting::setParameter(const ParameterType type, const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y)
{
    //���ؾ���
    auto _switch = createMenuItem(normalImage, selectedImage, callback, x, y);
    _switch->setName(SettingParameters::getInstance()->getName(type));

    //ѡ���ǩ
    auto musicLabel = createLabel(SettingParameters::getInstance()->getName(type), "fonts/Marker Felt.ttf", 16, x - _switch->getContentSize().width, y, 1.0f);
    addChild(musicLabel, 1);

    //��ʾ��ѡЧ��
    if (SettingParameters::getInstance()->getValue(type))
    {
        auto swoosh = createSprite("swoosh.png", x, y);
        swoosh->setName(SettingParameters::getInstance()->getName(type) + "Swoosh");
        addChild(swoosh, 1);
    }

    return _switch;
}

//ģʽѡ�����ĵ�������
SettingParameters* s_SharedSettingParameters = nullptr;

SettingParameters* SettingParameters::getInstance()
{
    if (!s_SharedSettingParameters)
    {
        s_SharedSettingParameters = new (std::nothrow) SettingParameters;
        CCASSERT(s_SharedSettingParameters, "FATAL: Not enough memory");
    }

    return s_SharedSettingParameters;
}

bool SettingParameters::getValue(const ParameterType type)
{
    return parameters[type].value;
}

std::string SettingParameters::getName(const ParameterType type)
{
    return parameters[type].name;
}

void SettingParameters::setValue(const ParameterType type, bool value)
{
    parameters[type].value = value;
}

