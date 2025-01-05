#include "UI.hpp"
#include <imgui-cocos.hpp>
#include "imgui/FontManager.hpp"
#include "../Aquamarine.hpp"

namespace aquamarine::ui {
    std::map<std::string, UIStyle*> styles = {};
    UIStyle* currentStyle = nullptr;
    float uiScale = 1.f;

    float getUIScale() {
        return uiScale;
    }

    void setUIScale(float scale) {
        uiScale = scale;
    }

    void registerStyle(UIStyle* style) {
        styles[style->getName()] = style;
    }

    UIStyle* getStyle(std::string type, std::string style) {
        return styles[style];
    }

    std::vector<std::string> getStyles() {
        std::vector<std::string> styleNames;
        for (auto& [name, style] : styles) {
            styleNames.push_back(name);
        }
        return styleNames;
    }

    void setStyle(std::string style) {
        if (styles.find(style) == styles.end()) {
            geode::log::warn("Could not find style {}", style);
            return;
        }
        currentStyle = styles[style];
    }

    UIStyle* getCurrentStyle() {
        return currentStyle;
    }

    std::unordered_map<std::string, widgets::Widget*> widgetMap = {};
    
    void registerWidget(widgets::Widget *widget) {
        widgetMap[widget->getId()] = widget;
    }

    void unregisterWidget(widgets::Widget *widget) {
        widgetMap.erase(widget->getId());
    }

    std::unordered_map<std::string, widgets::Widget*> getWidgets() {
        return widgetMap;
    }

    std::unordered_map<std::string, widgets::Widget*> getWidgets(std::string tab) {
        std::unordered_map<std::string, widgets::Widget*> tabWidgets;
        for (auto& [id, widget] : widgetMap) {
            if (widget->getTab() == tab) {
                tabWidgets[id] = widget;
            }
        }
        return tabWidgets;
    }
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        for (auto& [name, style] : aquamarine::ui::styles) {
            style->init();
        }

        aquamarine::ui::imgui::init();

        aquamarine::ui::setStyle(aquamarine::Config::getValue<std::string>("config.uistyle", "ImGui Tabbed"));
    }).draw([] {
        for (auto& [name, style] : aquamarine::ui::styles) {
        }
        if (aquamarine::ui::getCurrentStyle() != nullptr)
            aquamarine::ui::getCurrentStyle()->draw();
    }); 
}