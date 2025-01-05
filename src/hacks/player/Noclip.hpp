#pragma once

#include "../AquaHacks.hpp"

// Refactored NoclipMod class definition
class NoclipMod : public aquamarine::mods::Mod {
private:
    // Configuration states
    bool noclip = false;      // Global noclip toggle
    bool player1 = true;      // Player 1 noclip state
    bool player2 = true;      // Player 2 noclip state
    bool allPassable = false; // Global passable state

public:
    // Lifecycle methods
    void init() override;           // Initialize mod settings and UI
    void update(float dt) override; // Update loop (optional functionality)

    // Identification methods
    std::string getId() const override; // Unique mod identifier
    std::string getTab() const override; // Associated UI tab

    // Event handlers
    void onNoclip(bool toggled);    // Handle noclip state changes
    void onPlayer1(bool toggled);   // Handle Player 1 noclip toggle
    void onPlayer2(bool toggled);   // Handle Player 2 noclip toggle
    void onPassable(bool toggled);  // Handle passable state toggle
};

// Macro for registering the mod
REGISTER_MOD(new NoclipMod());
