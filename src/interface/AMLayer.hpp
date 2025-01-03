#pragma once

#include <Geode/Geode.hpp>
#include <iostream>
#include "ModMenu.hpp"
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;
using namespace std;
using namespace keybinds;

class AMLayer : public CCLayer {
public:
    virtual bool init();
    static AMLayer* create();
    void hideButton();
    void showButton();
    void setButtonParent(CCNode* parent);
    void resetButtonPositioning();
    void onButton(CCObject* obj) {
        if (menuWasCreated) {
            menu->show();
        }
        else {
            menu = Aquamarine::create();
            this->addChild(menu);
        }
        menuWasCreated = true;
    };
private:
    bool menuWasCreated = false;
    Aquamarine* menu;
    CCMenuItemSpriteExtra* am_button;
    CCMenu* aquamarine;
};

inline void AMLayer::hideButton()
{
    am_button->setVisible(false);
}

inline void AMLayer::showButton()
{
    am_button->setVisible(true);
}

inline void AMLayer::setButtonParent(CCNode* parent)
{
    am_button->retain();
    am_button->removeFromParent();
    parent->addChild(am_button);
    am_button->release();
}

inline void AMLayer::resetButtonPositioning()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    setButtonParent(aquamarine);
    am_button->setPositionX(screenSize.width / -2 + 57);
    am_button->setPositionY(screenSize.height / 2 - 18.5f);
}

bool AMLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    aquamarine = CCMenu::create();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("AM_Button.png"_spr);
asm_button = CCMenuItemSpriteExtra::create(
        sprite, this, menu_selector(AMLayer::onButton)
    );

    float buttonSize = 0.25f;
    sprite->setScale(buttonSize);
    sprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sprite->setPosition(CCPoint(0.0f, 0.0f));
    am_button->setContentSize(CCSize(128.0f * buttonSize, 128.0f * buttonSize));

    am_button->setPositionX(screenSize.width / -2 + 57);
    am_button->setPositionY(screenSize.height / 2 - 18.5f);

    aquamarine->addChild(am_button);
    aquamarine->setID("AMButtonMenu");
    this->addChild(aquamarine);
    this->setID("AMLayer");

    this->setZOrder(999);

#ifdef GEODE_IS_WINDOWS
    this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
        if (event->isDown()) {
            cout << "open AM" << endl;
            AMLayer::onButton(nullptr);
        }
        return ListenerResult::Propagate;
        }, "open-aquamarine"_spr);
#endif

    return true;
}

AMLayer* AMLayer::create() {
    AMLayer* me = new AMLayer();
    me->init();
    return me;
}