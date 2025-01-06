#include <imgui-cocos.hpp>
#include "../../Aquamarine.hpp"
#include "Speedhack.hpp"

// Helper for initializing and retrieving configuration values
template <typename T>
T setupConfig(const std::string& key, T defaultValue, bool saveImmediately = true) {
    aquamarine::Config::setValueIfUnset<T>(key, defaultValue, saveImmediately);
    return aquamarine::Config::getValue<T>(key, defaultValue, saveImmediately);
}

// Helper to create and register toggle and input widgets
void createSpeedhackWidget(const std::string& id, const std::string& label, const std::string& description,
                           const std::string& tab, bool* toggled, const std::function<void(bool)>& toggleCallback,
                           float* value, const std::function<void(float)>& valueCallback) {
    auto widget = aquamarine::ui::widgets::Widget::create(id)
        ->addToggle(id + ".toggle", toggleCallback, toggled)
        ->addFloatInput(id + ".value", valueCallback, "input", *value, 0.1f, 1000.0f)
        ->setLabel(label)
        ->setDescription(description)
        ->setTab(tab);
    aquamarine::ui::registerWidget(widget);
}

// SpeedhackMod implementation
void SpeedhackMod::init() {
    // Initialize configuration
    toggled = setupConfig<bool>("global.speedhack.enabled", false, false);
    value = setupConfig<float>("global.speedhack.value", 1.f);

    // Register widget
    createSpeedhackWidget("global.speedhack", "Speedhack", 
                          "Speeds up the game speed.", "Global", 
                          &toggled, [this](bool toggled) { onToggle(toggled); }, 
                          &value, [this](float value) { onValueChange(value); });
}

void SpeedhackMod::update(float dt) {
    // Optional update logic
}

std::string SpeedhackMod::getId() const {
    return "global.speedhack";
}

std::string SpeedhackMod::getTab() const {
    return "Global";
}

void SpeedhackMod::onToggle(bool toggled) {
    aquamarine::Config::setValue<bool>("global.speedhack.enabled", toggled, false);
}

void SpeedhackMod::onValueChange(float value) {
    aquamarine::Config::setValue<float>("global.speedhack.value", value);
}

// Modification to CCScheduler
#include <Geode/modify/CCScheduler.hpp>
class $modify(cocos2d::CCScheduler) {
    void update(float delta) {
        if (aquamarine::Config::getValue<bool>("global.speedhack.enabled", false, false)) {
            cocos2d::CCScheduler::update(delta * aquamarine::Config::getValue<float>("global.speedhack.value", 1.0));
        } else {
            cocos2d::CCScheduler::update(delta);
        }
    }
};

// SpeedAudioMod implementation
void SpeedAudioMod::init() {
    // Initialize configuration
    speedAudio = setupConfig<bool>("global.speedhack.audio.enabled", false);

    // Register widget
    auto widget = aquamarine::ui::widgets::Widget::create("global.speedhack.audio")
        ->addToggle("global.speedhack.audio.toggle", [this](bool toggled) { onToggleSpeed(toggled); }, &speedAudio)
        ->setLabel("Speedhack Audio Sync")
        ->setDescription("Speeds up audio to match speedhack.")
        ->setTab("Global");
    aquamarine::ui::registerWidget(widget);
}

void SpeedAudioMod::update(float dt) {
    for (int i = 0; i < 4; i++) {
        FMOD::Channel* channel;
        FMODAudioEngine::get()->m_system->getChannel(i + 126, &channel);
        if (channel) {
            FMOD::Sound* sound;
            channel->getCurrentSound(&sound);
            float freq;
            sound->getDefaults(&freq, nullptr);

            if (speedAudio && aquamarine::Config::getValue<bool>("global.speedhack.enabled", false, false)) {
                channel->setFrequency(freq * aquamarine::Config::getValue<float>("global.speedhack.value", 1.0));
            } else {
                channel->setFrequency(freq);
            }
        }
    }
}

std::string SpeedAudioMod::getId() const {
    return "global.speedhack.audio";
}

std::string SpeedAudioMod::getTab() const {
    return "Global";
}

void SpeedAudioMod::onToggleSpeed(bool toggled) {
    aquamarine::Config::setValue<bool>("global.speedhack.audio.enabled", toggled);
}
