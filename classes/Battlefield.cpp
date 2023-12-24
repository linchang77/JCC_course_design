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
    store = Store::create();    //�������ݲ���Ⱦ
    store->retain();
    auto storeItem = createMenuItem("storeNormal.png", "storeSelected.png", CC_CALLBACK_1(Battlefield::menuStoreCallback, this), visibleSize.width, 0.0f, 1.0f, 0.0f);

    //��սϯλ
    preparation = Preparation::create();  //������������Ⱦ
    addChild(preparation, 1);

    //����

    auto menu = Menu::create(returnItem, setItem, storeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    //ս���󱳾�
    auto map = MapData::create();
//���������Ϣͼ��
auto controler = LHcontroler::getInstance()->heros.at(0);
auto herolayer=controler->get_heroslayer();//��ʼ��һ��
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
    //���ý���Ӧ�����ɵ�����
    auto setting = Setting::createScene();
    Director::getInstance()->pushScene(setting);
}

void Battlefield::menuStoreCallback(Ref* pSender)
{
    if (!store->getStatus())    //���̵�
    {
        addChild(store, 2);
        store->setPosition(origin.x, origin.y);
    }
    else        //�ر��̵�
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

    //��Ⱦϯλ
    for (int i = 0; i < size; i++)
    {
        auto seat = Sprite::create(this->seat);
        if (seat == nullptr)
            problemLoading(this->seat);
        else
        {
            seat->setTag(i);    //���������ǩ������ȡ����i�ű�սϯ��λ��
            //�ȵ���ͼƬ�ߴ�����Ӧ��Ļ��С
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
    occupied++;     //��ռ��ϯλ����������
}

bool Store::init()
{
    if (!Layer::init())
        return false;

    displayment = Store::randomDisplay();       //��ǰ�̵����ݣ�Ӣ�����ݣ�

    Vector<MenuItem*> items;   //��ǰ�̵����ݣ���ʾ��ť��

    for (Vector<Hero*>::iterator p = displayment.begin(); p != displayment.end(); p++)
    {
        auto images = (*p)->getImages();         //��ȡͼ��
        auto item = createMenuItem(images.imageInStoreNormal, images.imageInStoreSelected, CC_CALLBACK_1(Store::purchaseCallback, this), 0.0f, visibleSize.height, 0.0f, 1.0f);   //�ȷŵ����Ͻ�
        item->setName("good" + std::to_string(p - displayment.begin() + 1));
        item->setPositionX((p - displayment.begin()) * item->getContentSize().width);   //���ɺ��ٵ���λ��
        items.pushBack(item);
    }

    menu = Menu::createWithArray(items);
    menu->setPosition(origin.x, origin.y);
    addChild(menu, 2);
    return true;
}

//Ӣ�۳س�ʼ��
Vector<Hero*> Store::pool = { Example::create() };

bool Store::addHero(Hero* newHero)
{
	if (pool.contains(newHero))  //�������Ӣ��ָ�����ڳ��У������ظ����
		return false;

    pool.pushBack(newHero);
    return true;
}

bool Store::removeHero(Hero* toBeRemoved)
{
	if (pool.contains(toBeRemoved)) //�������Ӣ��ָ�����ڳ��У��Ž���ɾ��
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
        float sampleCost = random(0.0f, 100.0f);    //�����ģ����������ѳ�ȡ��
        int j, total;
        for (j = total = 0; j < MAX_COST && (total += possibilityTable[grade - 1][j]) < sampleCost; j++)
            ;
        //����ѭ��ʱ��j����ȡ���ķ����±꣬j+1����ȡ���ķ���
        log("get cost %d", j + 1);
        int sampleHero = random(1, countHeroByCost(j + 1));     //�����ģ���������Ӣ�۳�ȡ��
        result.pushBack(getHeroByCost(j + 1, sampleHero));      //��ȡ���������������
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
    Hero* copy = nullptr;   //���ؿ���

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
    MenuItem* chosenItem = dynamic_cast<MenuItem*>(pSender);    //��ѡ�е���Ʒ��ť
    const float pos = chosenItem->convertToWorldSpace({ 0.0f, 1.0f }).x;    //��ȡ������item����������ϵ�ĺ�����
    const int good = chosenItem->getName().back() - '0' - 1;

    //good������ҹ�����������̵��е�˳�򣨴�������0~4��������Ĳ��������������ʵ��
    static_cast<Battlefield*>(Director::getInstance()->getRunningScene())->getCurrentPreparation()->placeHero(displayment.at(good));    //��������Ⱦ����սϯ��
    chosenItem->removeFromParent();     //������Ʒ��ť���̵��Ƴ�������ֻ�Ǽ򵥵�remove������Ҫ�����ӵ�Ч��������ʵ�֣�
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
