
#pragma once

#include "../UIManager.hpp"
#include <imgui-cocos.hpp>

namespace aquamarine::ui::cocos {
    class CocosUI : public UIStyle {
        protected:
            bool visible = false;
        public:
            void init() override;
            std::string getName() override;
            void open() override;
            void close() override;
            void toggle() override;
            void draw() override;
    };
}

REGISTER_STYLE(aquamarine::ui::cocos::CocosUI);
