#include <Geode/Geode.hpp>

#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp> // hide
#include <Geode/modify/LevelSelectLayer.hpp> // show
#include <Geode/modify/LevelInfoLayer.hpp> // show
#include <Geode/modify/EditLevelLayer.hpp> // show / reset
#include <Geode/modify/CreatorLayer.hpp>

#include "interface/AMLayer.hpp"
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <iostream>

using namespace geode::prelude;
using namespace keybinds;

bool buttonExists = false;
bool btnEditorMode = false;
AMLayer* amLayer;

class $modify(MenuLayer){
    bool init() {
        if (!MenuLayer::init()) return false;

        if (!Mod::get()->setSavedValue("seen-intro-popup", true)) {
            FLAlertLayer* popup = FLAlertLayer::create(
                "Aquamarine",
                "Welcome to Aquamarine!\n<cb>Press The Tab Key Or Press The Button To Continue Your Voyage.</c>",
                "OK"
            );
            popup->m_scene = this;
            popup->show();
        }

        if (buttonExists) return true;

        amLayer = AMLayer::create();
        this->addChild(amLayer);

        amLayer->setVisible(true);
        amLayer->showButton();

        SceneManager::get()->keepAcrossScenes(amLayer);

        buttonExists = true;

        return true;
    }
};

void showButton(bool reset) {
    //if (reset) {
    //    amLayer->resetButtonPositioning();
    //}
    amLayer->setVisible(false);
    amLayer->showButton();
    btnEditorMode = false;
}

class $modify(PlayLayer) {
    bool init(GJGameLevel * level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        amLayer->hideButton();
        return true;
    }
};

class $modify(PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();
        amLayer->showButton();
    }
};

class $modify(EditLevelLayer) {
    bool init(GJGameLevel * level) {
        if (!EditLevelLayer::init(level)) { return false; }
        amLayer->hideButton();
        return true;
    }
};

/*class $modify(EditorPauseLayer) {
    bool init(LevelEditorLayer * level) {
        if (!EditorPauseLayer::init(level)) return false;

        auto guidelinesMenu = this->getChildByID("guidelines-menu");

        amLayer->setVisible(true);
        amLayer->showButton();
        amLayer->setButtonParent(guidelinesMenu);

        CCSprite* sprite = CCSprite::createWithSpriteFrameName("AM_Button.png"_spr);
        CCMenuItemSpriteExtra* am_button = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(AMLayer::onButton)
        );

        float buttonSize = 0.25f;
        sprite->setScale(buttonSize);
        sprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
        am_button->setContentSize(CCSize(128.0f * buttonSize, 128.0f * buttonSize));

        btnEditorMode = true;

        return true;
    }
};*/

// register keys
#ifdef GEODE_IS_WINDOWS
$execute{
    using namespace keybinds;

    BindManager::get()->registerBindable({
        "close-aquamarine"_spr,
        "Close Aquamarine",
        "",
        { Keybind::create(KEY_Escape, Modifier::None) },
        "Aquamarine/Menu Keybinds"
    });

    BindManager::get()->registerBindable({
        "open-aquamarine"_spr,
        "Open Aquamarine",
        "",
        { Keybind::create(KEY_Tab, Modifier::None) },
        "Aquamarine/Menu Keybinds"
    });
}
#endif