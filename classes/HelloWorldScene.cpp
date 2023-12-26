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
#include "GeneralCreator.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
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

    //get director and general creator instances
    auto director = Director::getInstance();
    auto creator = GCreator::getInstance();

    //get visible size of the screen
    auto visibleSize = director->getVisibleSize();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = creator->createMenuItem("closeNormal.png", "closeSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);

    //模式选项按钮
    auto intoPracticeMode = creator->createMenuItem("practiceNormal.png", "practiceSelected.png", CC_CALLBACK_1(HelloWorld::menuPracticeCallback, this), visibleSize.width * 0.618f, visibleSize.height * 0.618f);  //开始游戏（练习模式）
    auto intoBattleMode = creator->createMenuItem("battleNormal.png", "battleSelected.png", CC_CALLBACK_1(HelloWorld::menuBattleCallback, this), visibleSize.width * 0.618f, visibleSize.height * 0.618f - intoPracticeMode->getContentSize().height); //开始游戏（战斗模式？）

    //设置菜单选项按钮
    auto setItem = creator->createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(HelloWorld::menuSetCallback, this), visibleSize.width - closeItem->getContentSize().width, visibleSize.height, 1.0f, 1.0f);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, intoPracticeMode, intoBattleMode, setItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = creator->createLabel("Golden Shovel War", "fonts/Marker Felt.ttf", 24, visibleSize.width / 2, 0.0f);
    label->setPositionX(visibleSize.height - label->getContentSize().height);
    addChild(label, 0);

    // add "HelloWorld" splash screen"
    auto sprite = creator->createSprite("StartUI.png", visibleSize.width / 2, visibleSize.height / 2);
    addChild(sprite, 0);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //clear the LHcontroller
    LHcontroler::clearInstance();

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::menuPracticeCallback(Ref* pSender)
{
    LHcontroler::clearInstance();   //渲染战场前，先清理小小英雄控制器单例
    auto practice = Battlefield::createScene();
    Director::getInstance()->pushScene(practice);
    ModeSelector::getInstance()->setMode(Practice, practice);
    log("Now your in %s mode.", ModeSelector::getInstance()->getMode() == Practice ? "practice" : "battle");
}

void HelloWorld::menuBattleCallback(Ref* pSender)
{
    LHcontroler::clearInstance();   //渲染战场前，先清理小小英雄控制器单例
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

