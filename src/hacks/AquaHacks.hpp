#pragma once
#include "../UI/UI.hpp"

namespace aquamarine::mods {
    class Mod {
        public:
            virtual void init() = 0;
            virtual void update(float dt) = 0;
            virtual std::string getId() const = 0;
            virtual std::string getTab() const = 0;
    };
    void registerMod(Mod *mod);
    std::unordered_map<std::string, Mod*> getMods();
    Mod* getMod(std::string id);

    void registerTab(std::string tab);
    std::vector<std::string> getTabs();
    std::unordered_map<std::string, Mod*> getModsInTab(std::string tab);

    #define REGISTER_MOD(mod) $on_mod(Loaded){ aquamarine::mods::registerMod(mod); }
    #define REGISTER_TAB(tab) $on_mod(Loaded){ aquamarine::mods::registerTab(tab); }
}