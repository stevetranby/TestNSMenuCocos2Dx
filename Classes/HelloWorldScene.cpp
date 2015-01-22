#include "HelloWorldScene.h"
#include <CocosGUI.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

    // Our custom UI
    this->setupUI();

    return true;
}

void HelloWorld::setupUI()
{
    auto textButton = ui::Text::create("Buy Item", "Arial", 30);
    textButton->setName("IAP_00_button");
    textButton->setNormalizedPosition(Vec2(.5,.1f));
    textButton->setTouchEnabled(true);
    textButton->setTouchScaleChangeEnabled(true);
    textButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType touchType) {
        if(touchType == ui::Widget::TouchEventType::ENDED) {
            // Testing Mock IAP to show calling into and out of platform-specific code and back
            //if(! UserDefault::getInstance()->getBoolForKey("IAP_00_purchased"))
            {
                // show alert view
                auto device = STDevice::getInstance();
                device->showAlertView(this, "IAP Purchase", "Item: $1.99", "Purchase", "Cancel");
            }
        }
    });
    this->addChild(textButton);
}

void HelloWorld::alertViewDidClose(int buttonIndex)
{
    if (buttonIndex == 1)
    {
        // okay
        auto prefs = UserDefault::getInstance();
        prefs->setBoolForKey("IAP_00_purchased", true);
        prefs->flush();

        {
            auto button = this->getChildByName<ui::Text*>("IAP_00_button");
            if(button) {
                button->setString("Item Purchased!");
                button->setEnabled(false);
            }
        }
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
