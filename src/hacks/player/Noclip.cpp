#include <imgui-cocos.hpp>
#include "../../Aquamarine.hpp"
#include "Noclip.hpp"

// Helper to simplify setting and getting configuration values
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

void NoclipMod::init() {
    // Initialize configuration values
    noclip = setupConfig<bool>("player.noclip.enabled", false);
    player1 = setupConfig<bool>("player.noclip.player1", true);
    player2 = setupConfig<bool>("player.noclip.player2", true);
    allPassable = setupConfig<bool>("player.noclip.passable", true);

    // Register widgets
    createToggleWidget("player.noclip.toggle", "Noclip", "Makes The Player Basically Indestructable.", 
                       "Player", &noclip, [this](bool toggled) { onNoclip(toggled); });

    createToggleWidget("player.noclip.passable", "All Passable", "Makes Every Object With A Hitbox Passable.", 
                       "Player", &allPassable, [this](bool toggled) { onPassable(toggled); });
}

void NoclipMod::update(float dt) {
    // Optional update logic for the noclip mod
}

std::string NoclipMod::getId() const {
    return "player.noclip";
}

std::string NoclipMod::getTab() const {
    return "Player";
}

void NoclipMod::onNoclip(bool toggled) {
    aquamarine::Config::setValue<bool>("player.noclip.enabled", toggled);
}

void NoclipMod::onPlayer1(bool toggled) {
    aquamarine::Config::setValue<bool>("player.noclip.player1", toggled);
}

void NoclipMod::onPlayer2(bool toggled) {
    aquamarine::Config::setValue<bool>("player.noclip.player2", toggled);
}

void NoclipMod::onPassable(bool toggled) {
    aquamarine::Config::setValue<bool>("player.noclip.passable", toggled);
}

// Modifications to PlayLayer
#include <Geode/modify/PlayLayer.hpp>
class $modify (PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        if (!aquamarine::Config::getValue<bool>("player.noclip.enabled", false) || obj == m_anticheatSpike) {
            PlayLayer::destroyPlayer(player, obj);
            return;
        }
        if ((m_player1 == player && !aquamarine::Config::getValue<bool>("player.noclip.player1", false)) ||
            (m_player2 == player && !aquamarine::Config::getValue<bool>("player.noclip.player2", false))) {
            PlayLayer::destroyPlayer(player, obj);
            return;
        }
    }
};

// Modifications to GameObject
#include <Geode/modify/GameObject.hpp>
class $modify (PassGameObject, GameObject) {
    void customSetup() {
        GameObject::customSetup();
        m_isPassable = aquamarine::Config::getValue<bool>("player.noclip.passable", true);
    }
};