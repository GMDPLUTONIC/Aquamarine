// #include "mods/AquaHacks.hpp"
#include "Aquamarine.hpp"

namespace aquamarine {
    matjson::Value Config::config = matjson::Value::object();
    matjson::Value Config::temp = matjson::Value::object();
    bool Config::initialized = false;
    bool Config::initializing = false;
    std::string Config::uiStyle = "";

    void Config::initialize() {
        if (!initialized && !initializing) {
            initializing = true;
            config = geode::Mod::get()->getSavedValue<matjson::Value>("config");
            // config = matjson::parse(geode::Mod::get()->getSavedValue<std::string>("config")).unwrapOrDefault();
            temp = matjson::Value::object();
            initialized = true;
        } else {
            #ifdef GEODE_DEBUG
            geode::log::warn("Config already initialized!");
            #endif
        }
    }

    void Config::setUIStyle(std::string style) {
        uiStyle = style;
        setValue<std::string>("uiStyle", style);
    }

    std::string Config::getUIStyle() {
        return uiStyle;
    }
}

UpdateManager *UpdateManager::get() {
    if (!instance) instance = new UpdateManager();
    return instance;
}

void UpdateManager::update(float dt)  {
    // for (auto& [id, mod] : aquamarine::mods::getMods()) {
    //     mod->update(dt);
    // }
}

bool UpdateManager::registerUpdate(std::string id, std::function<void(float)> update) {
    if (callbacks.find(id) != callbacks.end()) return false;
    callbacks[id] = update;
    return true;
}

bool UpdateManager::removeUpdate(std::string id) {
    if (callbacks.find(id) == callbacks.end()) return false;
    callbacks.erase(id);
    return true;
}

UpdateManager* UpdateManager::instance = nullptr;

$on_mod(Loaded) {
    // just so it starts
    UpdateManager::get();
}