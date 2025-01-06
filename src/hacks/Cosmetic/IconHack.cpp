#include <imgui-cocos.hpp>
#include "../../Aquamarine.hpp"
#include "IconHack.hpp"

// Helper function to initialize and retrieve configuration values
template <typename T>
T setupConfig(const std::string& key, T defaultValue) {
    aquamarine::Config::setValueIfUnset<T>(key, defaultValue);
    return aquamarine::Config::getValue<T>(key, defaultValue);
}

// Helper to create and register UI widgets
void createToggleWidget(const std::string& id, const std::string& label, const std::string& description,
                        const std::string& tab, bool* value, const std::function<void(bool)>& callback) {
    auto widget = aquamarine::ui::widgets::Widget::create(id)
        ->addToggle(id, callback, value)
        ->setLabel(label)
        ->setDescription(description)
        ->setTab(tab);
    aquamarine::ui::registerWidget(widget);
}

// IconHackMod implementation
void IconHackMod::init() {
    // Initialize configuration
    toggled = setupConfig<bool>("cosmetic.iconhack.enabled", false);

    // Register widget
    createToggleWidget("cosmetic.iconhack.toggle", "Icon Hack", 
                       "Unlocks Every Single Icon For You.", 
                       "Cosmetic", &toggled, [this](bool toggled) { onToggle(toggled); });
}

void IconHackMod::update(float dt) {
    // Optional update functionality
}

std::string IconHackMod::getId() const {
    return "cosmetic.iconhack";
}

std::string IconHackMod::getTab() const {
    return "Cosmetic";
}

void IconHackMod::onToggle(bool toggled) {
    aquamarine::Config::setValue<bool>("cosmetic.iconhack.enabled", toggled);
}

// Modifications to GameManager
#include <Geode/modify/GameManager.hpp>
class $modify(GameManager) {
    bool isIconUnlocked(int p0, IconType p1) {
        if (aquamarine::Config::getValue<bool>("cosmetic.iconhack.enabled", false)) {
            return true; // Bypass the lock check
        }
        return GameManager::isIconUnlocked(p0, p1); // Default behavior
    }

    bool isColorUnlocked(int p0, UnlockType p1) {
        if (aquamarine::Config::getValue<bool>("cosmetic.iconhack.enabled", false)) {
            return true; // Bypass the lock check
        }
        return GameManager::isColorUnlocked(p0, p1); // Default behavior
    }
};
