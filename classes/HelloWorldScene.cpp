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
#include "Room.h"
#include "GeneralCreator.h"
#include "AudioEngine.h"
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
    auto glView = director->getOpenGLView();
    glView->setFrameSize(1600, 900);

    // auto backgroundAudioID =AudioEngine::play2d("music.mp3", true);
    //get visible size of the screen
    auto visibleSize = director->getVisibleSize();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = creator->createMenuItem("closeNormal.png", "closeSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this), visibleSize.width, visibleSize.height, 1.0f, 1.0f);
    closeItem->setScale(CloseitemSize.x / closeItem->getContentSize().width);
    closeItem->setPosition(CloseitemPosition);

    //ģʽѡ�ť������
    auto intoPracticeMode = creator->createMenuItem("PracticeModeSelectedNormal.png", "PracticeModeSelected.png", CC_CALLBACK_1(HelloWorld::menuPracticeCallback, this), PracticeItemPosition.x, PracticeItemPosition.y);  //��ʼ��Ϸ����ϰģʽ��
    intoPracticeMode->setScale(ModeitemSize.x/ intoPracticeMode->getContentSize().width);
    auto intoBattleMode = creator->createMenuItem("OnlineModeNormal.png", "OnlineModeSelected.png", CC_CALLBACK_1(HelloWorld::menuBattleCallback, this), OnlineItemPosition.x, OnlineItemPosition.y); //��ʼ��Ϸ��ս��ģʽ����
    intoBattleMode->setScale(ModeitemSize.x / intoPracticeMode->getContentSize().width);
    auto PracticeWords = creator->createSprite("PracticeWord.png", 0, 0,0,0);
    PracticeWords->setContentSize(Size(1600, 900));
    auto OnlineWords = creator->createSprite("OnlineWord.png", 0, 0,0,0);
    OnlineWords->setContentSize(Size(1600, 900));
    this->addChild(PracticeWords, 1);
    this->addChild(OnlineWords, 1);

    //���ò˵�ѡ�ť
    auto setItem = creator->createMenuItem("setNormal.png", "setSelected.png", CC_CALLBACK_1(HelloWorld::menuSetCallback, this), SetitemPosition.x, SetitemPosition.y, 1.0f, 1.0f);
    setItem->setScale(SetitemSize.x / setItem->getContentSize().width);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, intoPracticeMode, intoBattleMode, setItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = creator->createLabel("Golden Shovel War", "fonts/Marker Felt.ttf", 48, visibleSize.width / 2, 0.0f);
    label->setPositionY(visibleSize.height - label->getContentSize().height);
    addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = creator->createSprite("StartUI.png", 0, 0,0,0);
    sprite->setContentSize(Size(1600, 948));
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
    LHcontroler::clearInstance();   //��Ⱦ����ǰ��������ССӢ�ۿ���������
    LHcontroler::getInstance()->initlocal();
    LHcontroler::getInstance()->init();

    auto battlefield = Battlefield::createScene();
    Director::getInstance()->pushScene(battlefield);
}

void HelloWorld::menuBattleCallback(Ref* pSender)
{
    LHcontroler::clearInstance();   //��Ⱦ����ǰ��������ССӢ�ۿ���������
    LHcontroler::getInstance()->initonline();
    LHcontroler::getInstance()->init();

    auto room = Room::createScene();
    Director::getInstance()->pushScene(room);
}

void HelloWorld::menuSetCallback(Ref* pSender)
{
    auto setting = Setting::createScene();
    Director::getInstance()->pushScene(setting);
}

