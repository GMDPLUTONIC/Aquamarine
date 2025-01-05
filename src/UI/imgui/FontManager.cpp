#include <imgui-cocos.hpp>
#include "FontManager.hpp"

namespace aquamarine::ui::imgui {
    // font, style
    std::map<std::pair<std::string, std::string>, ImFont*> imfonts = {};

    std::string currentFont = "Carme";
    std::string currentFontStyle = "Regular";

    std::vector<std::string> fonts = {
        "Alegreya",
        "Assistant",
        "Carme",
        "Lato",
        "Montserrat",
        "Nunito",
        "OpenSans",
        "OpenSansCondensed",
        "OpenSansSemiCondensed",
        "Poppins",
        "Roboto",
        "SourceCodePro",
        "Ubuntu"
    };

    std::vector<std::string> fontStyles = {
        "Black",
        "BlackItalic",
        "Bold",
        "BoldItalic",
        "ExtraBold",
        "ExtraBoldItalic",
        "ExtraLight",
        "ExtraLightItalic",
        "Italic",
        "Light",
        "LightItalic",
        "Medium",
        "MediumItalic",
        "Regular",
        "SemiBold",
        "SemiBoldItalic",
        "Thin",
        "ThinItalic"
    };

    std::map<std::string, std::vector<std::string>> availableStyles = {
        {"Ubuntu", {"Bold", "BoldItalic", "Italic", "Light", "LightItalic", "Medium", "MediumItalic", "Regular"}}
    };

    bool setFont(std::string font, std::string style) {
        if (isFontStyleSupported(font, style)) {
            auto imfont = imfonts[{font, style}];
            ImGui::GetIO().FontDefault = imfont;
            return true;
        } else {
            geode::log::warn("Font style {} is not supported for font {}", style, font);
            if (imfonts.find({font, "Regular"}) == imfonts.end()) {
                geode::log::warn("Could not find regular font for {}", font);
                return false;
            }
            auto imfont = imfonts[{font, "Regular"}];
            
            ImGui::GetIO().FontDefault = imfont;
            return true;
        }
    }

    bool pushFont(std::string font, std::string style) {
        if (isFontStyleSupported(font, style)) {
            auto imfont = imfonts[{font, style}];
            ImGui::PushFont(imfont);
            return true;
        } else {
            geode::log::warn("Font style {} is not supported for font {}", style, font);
            if (imfonts.find({font, "Regular"}) == imfonts.end()) {
                geode::log::warn("Could not find regular font for {}", font);
                return false;
            }
            auto imfont = imfonts[{font, "Regular"}];
            
            ImGui::PushFont(imfont);
            return true;
        }
    }

    void popFont() {
        ImGui::PopFont();
    }

    bool isFontStyleSupported(std::string font, std::string style) {
        return std::find(availableStyles[font].begin(), availableStyles[font].end(), style) != availableStyles[font].end();
    }

    std::vector<std::string> getFonts() {
        return fonts;
    }

    std::vector<std::string> getFontStyles() {
        return fontStyles;
    }

    std::vector<std::string> getFontStyles(std::string font) {
        return availableStyles[font];
    }

    std::map<std::pair<std::string, std::string>, ImFont*> getImFonts() {
        return imfonts;
    }

    void init() {
        for (auto& [font, styles] : availableStyles) {
            for (auto& style : styles) {
                if (!std::filesystem::exists(geode::Mod::get()->getResourcesDir() / (font + "-" + style + ".ttf"))) {
                    geode::log::warn("Could not find font file for {}-{}", font, style);
                    continue;
                }    
                auto* imfont = ImGui::GetIO().Fonts->AddFontFromFileTTF((geode::Mod::get()->getResourcesDir() / (font + "-" + style + ".ttf")).string().c_str(), 60.0f);
                imfonts[{font, style}] = imfont;
            }
        }
        if (imfonts.find({"Carme", "Regular"}) != imfonts.end())
            ImGui::GetIO().FontDefault = imfonts[{"Carme", "Regular"}];
    }
}