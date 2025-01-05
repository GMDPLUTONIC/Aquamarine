#pragma once

#include <Geode/Geode.hpp>

namespace aquamarine {
    class Config {
        private:
            Config() {};
        protected:
            static bool initialized;
            static bool initializing;

            static matjson::Value config;
            static matjson::Value temp;

            static std::string uiStyle;
        public:
            static void initialize();

            template <typename T>
            static void setValue(std::string key, T value, bool saved = true) {
                if (!initialized) initialize();
                if (saved) {
                    config.set(key, value);
                    geode::Mod::get()->setSavedValue<matjson::Value>("config", config);
                    // geode::Mod::get()->setSavedValue<std::string>("config", config.dump());
                }
                else temp.set(key, value);
            }

            template <typename T>
            static void setValueIfUnset(std::string key, T value, bool saved = true) {
                if (!initialized) initialize();
                if (saved) {
                    if (!config.contains(key)) {
                        config.set(key, value);
                        geode::Mod::get()->setSavedValue<matjson::Value>("config", config);
                        // geode::Mod::get()->setSavedValue<std::string>("config", config.dump());
                    }
                }
                else if (!temp.contains(key)) temp.set(key, value);
            }

            template <typename T>
            static T getValue(std::string key, T defaultValue, bool saved = true) {
                if (!initialized) initialize();
                if (saved) return config.get<T>(key).unwrapOr(defaultValue);
                else return temp.get<T>(key).unwrapOr(defaultValue);
            }

            static void setUIStyle(std::string style);
            static std::string getUIStyle();
    };
}

class UpdateManager : public cocos2d::CCObject {
    protected:
        UpdateManager() {
            cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(UpdateManager::update), this, 0, false);
        }
        static UpdateManager *instance;
        std::map<std::string, std::function<void(float)>> callbacks;
    public:
        static UpdateManager* get();
        void update(float dt);
        bool registerUpdate(std::string id, std::function<void(float)> func);
        bool removeUpdate(std::string id);
};