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
    log("Error while loading: %s\n", filename.data());
    log("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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
    auto closeItem = createMenuItem("closeNormal.png", "closeSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //模式选项按钮
    auto intoPracticeMode = createMenuItem("practiceNormal.png", "practiceSelected.png", CC_CALLBACK_1(HelloWorld::menuPracticeCallback, this), visibleSize.width * 0.618f, visibleSize.height * 0.618f);  //开始游戏（练习模式）
    auto intoBattleMode = createMenuItem("battleNormal.png", "battleSelected.png", CC_CALLBACK_1(HelloWorld::menuBattleCallback, this), visibleSize.width * 0.618f, visibleSize.height * 0.618f - intoPracticeMode->getContentSize().height); //开始游戏（战斗模式？）

    //设置菜单选项按钮
    auto setItem = createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(HelloWorld::menuSetCallback, this), visibleSize.width - closeItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);

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
    log("Now your in %s mode.", ModeSelector::getInstance()->getMode() == Practice ? "practice" : "battle");
}

void HelloWorld::menuBattleCallback(Ref* pSender)
{
    auto battle = Battlefield::createScene();
    Director::getInstance()->pushScene(battle);
    ModeSelector::getInstance()->setMode(Battle, battle);
    log("Now your in %s mode.", ModeSelector::getInstance()->getMode() == Practice ? "practice" : "battle");
}

void HelloWorld::menuSetCallback(Ref* pSender)
{
    auto setting = Setting::createScene();
    Director::getInstance()->pushScene(setting);
}

MenuItemImage* HelloWorld::createMenuItem(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const float x, const float y, const float anchorX, const float anchorY)
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

