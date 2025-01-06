#include <imgui-cocos.hpp>
#include "../../Aquamarine.hpp"
#include "../../UI/imgui/FontManager.hpp"
#include "../../UI/UI.hpp"
#include "Config.hpp"

void ConfigMods::init() {
    aquamarine::Config::setValueIfUnset<bool>("config.showball", false);
    showBall = aquamarine::Config::getValue<bool>("config.showball", false);

    aquamarine::Config::setValueIfUnset<float>("config.uiscale", 1.f);
    uiScale = aquamarine::Config::getValue<float>("config.uiscale", 1.f);
    aquamarine::ui::setUIScale(uiScale);

    aquamarine::Config::setValueIfUnset<std::string>("config.font", "Carme");
    aquamarine::Config::setValueIfUnset<std::string>("config.fontstyle", "Regular");
    currentFont = aquamarine::Config::getValue<std::string>("config.font", "Carme");
    currentFontStyle = aquamarine::Config::getValue<std::string>("config.fontstyle", "Regular");
    geode::log::info("Selected font: {}", currentFont);
    geode::queueInMainThread([this]() {
        aquamarine::ui::imgui::setFont(currentFont, currentFontStyle);
    });

    auto widget = aquamarine::ui::widgets::Widget::create("config.showball")
        ->addToggle("config.showball.toggle", [this](bool toggled) {
            onShowBall(toggled);
        }, &showBall)
        ->setLabel("Show Ball")
        ->setDescription("Show the ball to open the menu.")
        ->setTab("Config");
    aquamarine::ui::registerWidget(widget);

    auto widget2 = aquamarine::ui::widgets::Widget::create("config.uiscale")
        ->addFloatInput("config.uiscale.input", [this](float value) {
            onUiScale(value);
        }, "input", uiScale, 0.1f, 2.f)
        ->setLabel("UI Scale")
        ->setDescription("Change the scale of the UI.")
        ->setTab("Config");
    aquamarine::ui::registerWidget(widget2);

    std::map<std::string, std::pair<std::string, std::string>> fonts;
    for (auto font : aquamarine::ui::imgui::getFonts()) {
        fonts[font] = {font, "Regular"};
    }

    auto widget3 = aquamarine::ui::widgets::Widget::create("config.font")
        ->setLabel("Font")
        ->setDescription("Change the font of the UI.")
        ->addDropdown("config.font.dropdown", [this](int selected) {
            currentFont = aquamarine::ui::imgui::getFonts()[selected];
            geode::log::info("Selected font: {}", currentFont);
            aquamarine::Config::setValue<std::string>("config.font", currentFont);
            geode::queueInMainThread([this]() {
                aquamarine::ui::imgui::setFont(currentFont, currentFontStyle);
            });
        }, aquamarine::ui::imgui::getFonts(), currentFont, fonts)
        ->setTab("Config");
    aquamarine::ui::registerWidget(widget3);

    std::map<std::string, std::pair<std::string, std::string>> fontStyles;
    for (auto style : aquamarine::ui::imgui::getFontStyles(currentFont)) {
        fontStyles[style] = {currentFont, style};
    }

    auto widget4 = aquamarine::ui::widgets::Widget::create("config.fontstyle")
        ->setLabel("Font Style")
        ->setDescription("Change the style of the font.")
        ->addDropdown("config.fontstyle.dropdown", [this](int selected) {
            currentFontStyle = aquamarine::ui::imgui::getFontStyles()[selected];
            aquamarine::Config::setValue<std::string>("config.fontstyle", currentFontStyle);
            geode::queueInMainThread([this]() {
                aquamarine::ui::imgui::setFont(currentFont, currentFontStyle);
            });
        }, aquamarine::ui::imgui::getFontStyles(), currentFontStyle, fontStyles)
        ->setTab("Config");
    aquamarine::ui::registerWidget(widget4);
}

void ConfigMods::update(float dt) {
    
}

std::string ConfigMods::getId() const {
    return "config";
}

std::string ConfigMods::getTab() const {
    return "Config";
}

void ConfigMods::onShowBall(bool value) {
    aquamarine::Config::setValue<bool>("config.showball", value);
}

void ConfigMods::onUiScale(float value) {
    aquamarine::Config::setValue<float>("config.uiscale", value);
    aquamarine::ui::setUIScale(value);
}