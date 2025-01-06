#pragma once

#include "../AquaHacks.hpp"

class NoclipMod : public aquamarine::mods::Mod {
    private:
        bool noclip = false;
        bool player1 = true;
        bool player2 = true;
        bool allPassable = false;
    public:
        void init() override;
        void update(float dt) override;
        std::string getId() const override;
        std::string getTab() const override;
        void onNoclip(bool toggled);
        void onPlayer1(bool toggled);
        void onPlayer2(bool toggled);
        void onPassable(bool toggled);
};

REGISTER_MOD(new NoclipMod());