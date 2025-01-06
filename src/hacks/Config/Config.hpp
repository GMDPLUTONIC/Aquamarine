#pragma once

#include "../AquaHacks.hpp"

class ConfigMods : public aquamarine::mods::Mod {
    private:
        bool showBall = false;
        float uiScale = 1.f;
        std::string currentFont = "Carme";
        std::string currentFontStyle = "Regular";
    public:
        void init() override;
        void update(float dt) override;
        std::string getId() const override;
        std::string getTab() const override;
        void onShowBall(bool value);
        void onUiScale(float value);
};

REGISTER_MOD(new ConfigMods());