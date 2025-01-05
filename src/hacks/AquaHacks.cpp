#include "AquaHacks.hpp"

namespace aquamarine::mods {
    std::unordered_map<std::string, Mod*> mods;
    std::vector<std::string> tabs;

    void registerMod(Mod* mod) {
        mods[mod->getId()] = mod;
        mod->init();
    }

    std::unordered_map<std::string, Mod*> getMods() {
        return mods;
    }

    Mod* getMod(std::string id) {
        return mods[id];
    }

    void registerTab(std::string tab) {
        tabs.push_back(tab);
    }

    std::vector<std::string> getTabs() {
        return tabs;
    }

    std::unordered_map<std::string, Mod*> getModsInTab(std::string tab) {
        std::unordered_map<std::string, Mod*> modsInTab;
        for (auto& mod : mods) {
            if (mod.second->getTab() == tab) {
                modsInTab[mod.first] = mod.second;
            }
        }
        return modsInTab;
    }

    REGISTER_TAB("Global");
    REGISTER_TAB("Level")
    REGISTER_TAB("Player");
    REGISTER_TAB("Cosmetic")
    REGISTER_TAB("Bypass");
    REGISTER_TAB("Config");
    REGISTER_TAB("Shortcuts");
}