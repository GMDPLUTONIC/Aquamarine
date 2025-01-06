#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace aquamarine::ui::cocos {

    class AquaBall : public CCMenu {
    protected:
        static AquaBall *instance;
        
        float m_scale = 1.0f;
        float m_multiplier = 0.8f;
        bool move = false;

        CCPoint *startPos;
        CCPoint diff;
        
        CCSprite *m_sprite;

        bool init() override;
        bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
        void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
        void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override;
        void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) override {
            ccTouchEnded(touch, event);
        }
        void registerWithTouchDispatcher() override;

    public:
        static AquaBall *get();
        void onPress();
        void update(float dt) override;
    };

}