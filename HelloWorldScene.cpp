/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Setting.h"
#include "Battlefield.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const std::string filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = createMenuItem("closeNormal.png", "closeSelected.png", CC_CALLBACK_1(menuCloseCallback, this), visibleSize.width, visibleSize.height);

    //模式选项
    auto intoPracticeMode = createMenuItem("PraticeNormal.png", "PracticeSelected.png", CC_CALLBACK_1(menuPracticeCallback, this), visibleSize.width * 0.618, visibleSize.height * 0.618);
    auto intoBattleMode = createMenuItem("BattleNormal.png", "BattleSelected.png", CC_CALLBACK_1(menuBattleCallback, this), visibleSize.width * 0.618, visibleSize.height * 0.618 - intoPracticeMode->getContentSize().height);

    //设置菜单选项
    auto setItem = createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(menuSetCallback, this), visibleSize.width - closeItem->getContentSize().width, visibleSize.height);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, intoPracticeMode, intoBattleMode, setItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Golden Shovel War", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Start.png");
    if (sprite == nullptr)
    {
        problemLoading("'Start.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::menuPracticeCallback(Ref* pSender)
{
    auto practice = Battlefield::createScene();
    Director::getInstance()->pushScene(practice);
    ModeSelector::getInstance()->setMode(Practice, practice);
}

void HelloWorld::menuBattleCallback(Ref* pSender)
{
    auto battle = Battlefield::createScene();
    Director::getInstance()->pushScene(battle);
    ModeSelector::getInstance()->setMode(Battle, battle);
}

void HelloWorld::menuSetCallback(Ref* pSender)
{
    static auto setting = Setting::createScene();
    Director::getInstance()->pushScene(setting);
}

MenuItemImage* HelloWorld::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, float x, float y)
{
    auto item = MenuItemImage::create(normalImage, selectedImage, callback);

    if (item == nullptr || item->getContentSize().width <= 0 || item->getContentSize().height <= 0)
        problemLoading("'" + normalImage + "' and '" + selectedImage);
    else
        item->setPosition(origin.x + x - item->getContentSize().width / 2, origin.y + y - item->getContentSize().height / 2);

    return item;
}
