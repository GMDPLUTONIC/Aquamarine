#pragma once

#include "widgets/Widget.hpp"

namespace aquamarine::ui {
    class UIStyle {
        public:
            virtual void init() = 0;
            virtual std::string getName() = 0;
            virtual void open() = 0;
            virtual void close() = 0;
            virtual void toggle() = 0;
            // on non-imgui styles, this will probably be ignored.
            virtual void draw() = 0;
    };

    float getUIScale();
    void setUIScale(float scale);

    void registerStyle(UIStyle* style);
    UIStyle* getStyle(std::string type, std::string style);
    std::vector<std::string> getStyles(std::string type); 
    void setStyle(std::string type, std::string style);
    UIStyle* getCurrentStyle();

    void registerWidget(widgets::Widget *widget);
    void unregisterWidget(widgets::Widget *widget);
    std::unordered_map<std::string, widgets::Widget*> getWidgets();
    std::unordered_map<std::string, widgets::Widget*> getWidgets(std::string tab);

    #define REGISTER_STYLE(style) $on_mod(Loaded){ registerStyle(new style()); }
}