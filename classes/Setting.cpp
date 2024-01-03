#include "Setting.h"
#include "GeneralCreator.h"
#include "AudioEngine.h"
USING_NS_CC;

Scene* Setting::createScene()
{
	return Setting::create();
}

bool Setting::init()
{
	if (!Scene::init())
		return false;

    //���ؿ�ʼ����
	auto returnItem = GCreator::getInstance()->createMenuItem("settingToStartNormal.png", "settingToStartSelected.png", CC_CALLBACK_1(Setting::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);
    returnItem->setScale(50 / returnItem->getContentSize().width);
    returnItem->setPosition(Vec2(1600,925));
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
        auto swoosh = GCreator::getInstance()->createSprite("swoosh.png", (1 - 0.618f) * visibleSize.width, 0.618f * visibleSize.height);
        swoosh->setName("musicSwoosh");
        addChild(swoosh, 1);
        AudioEngine::resume(0);
        
    }
    else
    {
        auto swoosh = getChildByName("musicSwoosh");
        swoosh->removeFromParent();
        AudioEngine::pause(0);
    }

    log("Music is %s now.", !music ? "on" : "off");
}

MenuItemImage* Setting::setParameter(const ParameterType type, const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y)
{
    //���ؾ���
    auto _switch = GCreator::getInstance()->createMenuItem(normalImage, selectedImage, callback, x, y);
    _switch->setName(SettingParameters::getInstance()->getName(type));

    //ѡ���ǩ
    auto musicLabel = GCreator::getInstance()->createLabel(SettingParameters::getInstance()->getName(type), "fonts/Marker Felt.ttf", 24, x - _switch->getContentSize().width, y, 1.0f);
    addChild(musicLabel, 1);

    //��ʾ��ѡЧ��
    if (SettingParameters::getInstance()->getValue(type))//������ֹͣ
    {
        auto swoosh = GCreator::getInstance()->createSprite("swoosh.png", x, y);
        swoosh->setName(SettingParameters::getInstance()->getName(type) + "Swoosh");
        addChild(swoosh, 1);
    }
  
    return _switch;
}

//ģʽѡ�����ĵ�������
static SettingParameters* s_SharedSettingParameters = nullptr;

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

