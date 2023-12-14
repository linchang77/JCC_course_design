#include "Battlefield.h"
#include "Setting.h"
USING_NS_CC;

Scene* Battlefield::createScene()
{
    return Battlefield::create();
}

//���ԣ��ļ���ʧ��ʱ����Ϣ���
static void problemLoading(const std::string filename)
{
    log("���ļ�%s���ɹ���", filename);
}

bool Battlefield::init()
{
    if (!Scene::init())
        return false;

	//���ؿ�ʼ����
    auto returnItem = createMenuItem("battlefieldToStartNormal.png", "battlefieldToStartSelected.png", CC_CALLBACK_1(Battlefield::menuReturnCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //��������
    auto setItem = createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(Battlefield::menuSetCallback, this), visibleSize.width - returnItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);

    //�̵�
    store = Store::createLayer();    //�������ݲ���Ⱦ
    auto storeItem = createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(Battlefield::menuStoreCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);

    //��սϯλ
    preparation = Preparation::createLayer();  //������������Ⱦ
    addChild(preparation, 1);

    //����

    auto menu = Menu::create(returnItem, setItem, storeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    //ս���󱳾�
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
    //���ý���Ӧ�����ɵ�����
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

//ģʽѡ�����ĵ�������
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
        log("ģʽѡ������δ��ʼ����");

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

    //��Ⱦϯλ
    for (int i = 0; i < size; i++)
    {
        auto seat = Sprite::create(this->seat);
        if (seat == nullptr)
            problemLoading(this->seat);
        else
        {
            //�ȵ���ͼƬ�ߴ�����Ӧ��Ļ��С
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

    displayment = Store::randomDisplay();       //��ǰ�̵����ݣ�Ӣ�����ݣ�

    for (Vector<Hero*>::iterator p = displayment.begin(); p != displayment.end(); p++)
    {
        auto images = (*p)->getImages();         //��ȡͼ��
        auto item = createMenuItem(images.imageInStoreNormal, images.imageInStoreSelected, CC_CALLBACK_1(Store::purchaseCallback, this), 0.0f, 0.0f, 0.0f, 1.0f);   //�ȷŵ����Ͻ�
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //���ɺ��ٵ���λ��
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
        float sampleCost = random(0.0f, 100.0f);    //�����ģ����������ѳ�ȡ��
        int j, total;
        for (j = 0, total = 0; j < MAX_COST && (total += possibilityTable[grade][j]) < sampleCost; j++)
            ;
        //����ѭ��ʱ��j����ȡ���ķ����±�
        int sampleHero = random(0, int(pool[j].size() - 1));  //�����ģ���������Ӣ�۳�ȡ��
        result.pushBack(pool[j].at(sampleHero));
    }

    return result;
}

void Store::purchaseCallback(Ref* pSender)
{
    const float pos = dynamic_cast<MenuItem*>(pSender)->convertToWorldSpace({ 0.0f, 1.0f }).x;    //��ȡ������item����������ϵ�ĺ�����
    const int good = pos / getChildByName("good1")->getContentSize().width;

    //good������ҹ�����������̵��е�˳�򣨴�������0~4��������Ĳ��������������ʵ��
    log("��������Ӣ��%s", displayment.at(good)->getName().data());
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
