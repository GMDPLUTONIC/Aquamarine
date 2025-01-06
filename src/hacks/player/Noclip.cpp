#include <imgui-cocos.hpp>
#include "../../Aquamarine.hpp"
#include "Noclip.hpp"

void NoclipMod::init() {
    aquamarine::Config::setValueIfUnset<bool>("player.noclip.enabled", false);
    noclip = aquamarine::Config::getValue<bool>("player.noclip.enabled", false);

    aquamarine::Config::setValueIfUnset<bool>("player.noclip.player1", true);
    player1 = aquamarine::Config::getValue<bool>("player.noclip.player1", true);

    aquamarine::Config::setValueIfUnset<bool>("player.noclip.player2", true);
    player2 = aquamarine::Config::getValue<bool>("player.noclip.player2", true);

    aquamarine::Config::setValueIfUnset<bool>("player.noclip.passable", true);
    allPassable = aquamarine::Config::getValue<bool>("player.noclip.passable", true);

    auto widget = aquamarine::ui::widgets::Widget::create("player.noclip")
        ->addToggle("player.noclip.toggle", [this](bool toggled) {
            onNoclip(toggled);
        }, &noclip)
        ->setLabel("Noclip")
        ->setDescription("Prevents you from dying.")
        ->setTab("Player");
    aquamarine::ui::registerWidget(widget);

    auto widget4 = aquamarine::ui::widgets::Widget::create("player.passable")
        ->addToggle("player.noclip.passable", [this](bool toggled) {
            onPassable(toggled);
        }, &allPassable)
        ->setLabel("All Passable")
        ->setDescription("Makes all objects passable.")
        ->setTab("Player");
    aquamarine::ui::registerWidget(widget4);
}

void NoclipMod::update(float dt) {
    
}

// void NoclipMod::renderImGui() {
//     ImGui::Checkbox("Noclip", &noclip);
//     if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
//     {
//         ImGui::SetTooltip("Prevents you from dying.");
//     }
//     ImGui::SameLine(ImGui::GetWindowWidth() - 35);
//     ImGui::SetNextItemWidth(100);
//     if (ImGui::Button(" > ")) ImGui::OpenPopup("Noclip");
//         if (ImGui::BeginPopup("Noclip")) {
//         ImGui::Checkbox("Player 1", &player1);
//         if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
//         {
//             ImGui::SetTooltip("Prevents player 1 from dying.");
//         }
//         if (lastPlayer1 != player1) {
//             lastPlayer1 = player1;
//             aquamarine::Config::setValue<bool>("player.noclip.player1", player1);
//         }
            
//         ImGui::Checkbox("Player 2", &player2);
//         if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
//         {
//             ImGui::SetTooltip("Prevents player 2 from dying.");
//         }
//         if (lastPlayer2 != player2) {
//             lastPlayer2 = player2;
//             aquamarine::Config::setValue<bool>("player.noclip.player2", player2);
//         }

//         ImGui::EndPopup();
//     }
//     if (lastNoclip != noclip) {
//         lastNoclip = noclip;
//         onNoclip(noclip);
//     }
// }

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

#include <Geode/modify/PlayLayer.hpp>
class $modify (PlayLayer) {
    void destroyPlayer(PlayerObject *player, GameObject *obj) {
        if (!aquamarine::Config::getValue<bool>("player.noclip.enabled", false) || obj == m_anticheatSpike) {
            PlayLayer::destroyPlayer(player, obj);
            return;
        }
        if ((m_player1 == player && !aquamarine::Config::getValue<bool>("player.noclip.player1", false)) || (m_player2 == player && !aquamarine::Config::getValue<bool>("player.noclip.player2", false))) {
            PlayLayer::destroyPlayer(player, obj);
            return;
        }
    }
};

#include <Geode/modify/GameObject.hpp>
class $modify (PassGameObject, GameObject) {
    void customSetup() {
        GameObject::customSetup();
        m_isPassable = aquamarine::Config::getValue<bool>("player.noclip.passable", true);
    }
};