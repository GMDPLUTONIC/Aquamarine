#pragma once

#include "../AquaHacks.hpp"

// IconHackMod class definition
class IconHackMod : public aquamarine::mods::Mod {
private:
    // State for the icon hack toggle
    bool toggled = false;

public:
    // Lifecycle methods
    void init() override;           // Initialize mod settings and UI
    void update(float dt) override; // Update loop (optional functionality)

    // Identification methods
    std::string getId() const override; // Unique mod identifier
    std::string getTab() const override; // Associated UI tab

    // Event handler
    void onToggle(bool toggled); // Handle toggle state changes
};

// Macro for registering the mod
REGISTER_MOD(new IconHackMod());
