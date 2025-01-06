#include "AquaButton.hpp"
#include "../../Aquamarine.hpp"
#include "../UIManager.hpp"

using namespace aquamarine::ui::cocos;
using namespace geode::prelude;

bool initialized = false;

namespace aquamarine::ui::cocos {

AquaBall *AquaBall::instance = nullptr;

bool AquaBall::init() {
  if (!CCMenu::init()) {
    return false;
  }

  scheduleUpdate();

  instance = this;

  m_sprite = CCSprite::createWithSpriteFrameName("Aqua_Button.png"_spr);
  m_sprite->setScale(.4f);
  m_sprite->setID("sprite");
  addChild(m_sprite);
  setContentSize(m_sprite->getScaledContentSize());
  setContentSize(m_sprite->getScaledContentSize());
  m_sprite->setPosition(getContentSize() / 2);

  CCScene::get()->addChild(this);
  SceneManager::get()->keepAcrossScenes(this);

  setZOrder(9999998);
  auto x = aquamarine::Config::getValue<float>("ballPosX", 50.f);
  auto y = aquamarine::Config::getValue<float>("ballPosY", 50.f);
  x = std::clamp(x, -getContentWidth() / 2, CCDirector::get()->getWinSize().width - getContentWidth() / 2);
  y = std::clamp(y, -getContentHeight() / 2, CCDirector::get()->getWinSize().height - getContentHeight() / 2);
  setPosition({x, y});
  aquamarine::Config::setValue<float>("ballPosX", x);
  aquamarine::Config::setValue<float>("ballPosY", y);

  setID("aquamarine-button"_spr);

  return true;;
}

AquaBall *AquaBall::get() {
  if (instance)
    return instance;
  auto ret = new AquaBall();
  if (ret && ret->init()) {
    ret->autorelease();
    return ret;
  } else {
    delete ret;
    return nullptr;
  }
}

void AquaBall::registerWithTouchDispatcher() {
  CCTouchDispatcher::get()->addTargetedDelegate(this, -9999999, true);
}

bool AquaBall::ccTouchBegan(CCTouch *touch, CCEvent *evt) {
  // if (CocosMenu::get()) return false;
  if (!isVisible())
    return false;
  diff = getPosition() - touch->getLocation();
  startPos = new CCPoint(touch->getLocation());
  if (getScaledContentSize().width / 2 <
      ccpDistance(m_sprite->getPosition(),
                  convertToNodeSpace(touch->getLocation()))) {
    return false;
  }
  move = false;
  
  stopAllActions();
  runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale * m_multiplier)));
  return true;
}

void AquaBall::ccTouchEnded(CCTouch *touch, CCEvent *evt) {
  stopAllActions();
  runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale)));
  if (move)
    return;
  onPress();
}

void AquaBall::ccTouchMoved(CCTouch *touch, CCEvent *evt) {
  if (!move)
    if (ccpDistance(*startPos, touch->getLocation()) > 3)
      move = true;
  if (move) {
    auto pos = touch->getLocation() + diff;
    pos.x = std::clamp(pos.x, -getContentWidth() / 2, CCDirector::get()->getWinSize().width - getContentWidth() / 2);
    pos.y = std::clamp(pos.y, -getContentHeight() / 2, CCDirector::get()->getWinSize().height - getContentHeight() / 2);
    setPosition(pos);
    aquamarine::Config::setValue<float>("ballPosX", pos.x);
    aquamarine::Config::setValue<float>("ballPosY", pos.y);
  }
}

void AquaBall::onPress() { 
  // CocosMenu::open();
  if (auto uis = aquamarine::ui::getCurrentStyle()) uis->toggle();
}

void AquaBall::update(float dt) {
  #ifndef GEODE_IS_ANDROID
  if (aquamarine::Config::getValue<bool>("config.showball", false)) {
    setVisible(true);
  } else {
    setVisible(false);
  }
  #endif
}

} // namespace aquamarine::cocosui

bool firstML = false;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer){
  bool init(){
    if (!MenuLayer::init()) return false;
    if (!initialized) {
      AquaBall::get();
      initialized = true;
    }
    if (!firstML && aquamarine::Config::getValue<bool>("shownAlphaMessage", false) == false && Mod::get()->getVersion().getTag()->value == VersionTag::Alpha) {
      firstML = true;
      queueInMainThread([this]() {
        geode::createQuickPopup("Aquamarine", "Aquamarine Is Fairly New And Has Lots Of Bugs.", "Ok", "Do not show again", [this](auto, bool dontShow) {
        if (dontShow) aquamarine::Config::setValue<bool>("shownAlphaMessage", true);
      });
      });
    }
    return true;
  }
};

#include <Geode/modify/CCScene.hpp>

class $modify(CCScene) {
  int getHighestChildZ() {
    int btnZ;
    auto btn = AquaBall::get();
    if (btn) {
      btnZ = btn->getZOrder();
      btn->setZOrder(-1);
    }
    auto highest = CCScene::getHighestChildZ();
    if (btn) btn->setZOrder(btnZ);
    return highest;
  }
};