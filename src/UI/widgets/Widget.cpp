#include <imgui-cocos.hpp>
#include "Widget.hpp"
#include "../UI.hpp"
#include "../imgui/FontManager.hpp"

namespace aquamarine::ui::widgets
{
  Widget *Widget::addToggle(std::string id, std::function<void(bool toggled)> callback, bool *toggleVal)
  {
    m_components.push_back(new Toggle{id, "Toggle", 0, toggleVal, callback});
    return this;
  }

  Widget *Widget::addButton(std::string id, std::function<void()> callback)
  {
    m_components.push_back(new Button{id, "Button", 0, callback});
    return this;
  }

  Widget *Widget::addFloatInput(std::string id, std::function<void(float value)> callback, std::string inputType, float value, float min, float max)
  {
    m_components.push_back(new FloatInput{id, "FloatInput", 0, value, callback, min, max, inputType});
    return this;
  }

  Widget *Widget::addIntInput(std::string id, std::function<void(int value)> callback, std::string inputType, int value, int min, int max)
  {
    m_components.push_back(new IntInput{id, "IntInput", 0, value, callback, min, max, inputType});
    return this;
  }

  Widget *Widget::addStringInput(std::string id, std::function<void(std::string value)> callback, int maxChars, std::string value)
  {
    m_components.push_back(new StringInput{id, "StringInput", 0, maxChars, value, callback});
    return this;
  }

  Widget *Widget::addDropdown(std::string id, std::function<void(int selected)> callback, std::vector<std::string> options, std::string selected, std::map<std::string, std::pair<std::string, std::string>> fonts)
  {
    int selId;
    for (int i = 0; i < options.size(); i++)
    {
      if (options[i] == selected)
      {
        selId = i;
        break;
      }
    }
    auto dd = new Dropdown{id, "Dropdown", 0, options, selId, callback};
    dd->fonts = fonts;
    m_components.push_back(dd);
    return this;
  }

  Widget *Widget::remove(std::string id)
  {
    for (auto it = m_components.begin(); it != m_components.end(); it++)
    {
      if ((*it)->id == id)
      {
        m_components.erase(it);
        delete *it;
        break;
      }
    }
    return this;
  }

  Widget *Widget::setLabel(std::string label)
  {
    m_label = label;
    return this;
  }

  Widget *Widget::setDescription(std::string desc)
  {
    m_description = desc;
    return this;
  }

  Widget *Widget::setTab(std::string tab) {
    m_tab = tab;
    return this;
  }

  Widget *Widget::registerOption(std::string tab)
  {
    return this;
  }

  Widget *Widget::unregisterOption()
  {
    return this;
  }

  std::string Widget::getId()
  {
    return m_id;
  }

  std::string Widget::getLabel()
  {
    return m_label;
  }

  std::string Widget::getDescription()
  {
    return m_description;
  }

  std::string Widget::getTab()
  {
    return m_tab;
  }

  std::vector<Component *> Widget::getComponents()
  {
    return m_components;
  }

  Component *Widget::getComponent(std::string id)
  {
    for (auto it = m_components.begin(); it != m_components.end(); it++)
    {
      if ((*it)->id == id)
      {
        return *it;
      }
    }
    return nullptr;
  }

  void Widget::imRender() {
    int i = 0;
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
      if (i > 0) ImGui::SameLine();
      i++;
      if ((*it)->type == "Toggle") {
        Toggle *t = static_cast<Toggle*>(*it);
        ImGui::Checkbox(fmt::format("##{}", t->id).c_str(), t->toggled);
        if (*t->toggled != t->lastToggled) {
          t->lastToggled = *t->toggled;
          t->callback(*t->toggled);
        }
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else if ((*it)->type == "Button") {
        Button *b = static_cast<Button*>(*it);
        if (ImGui::Button(b->id.c_str())) {
          b->callback();
        }
        
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else if ((*it)->type == "FloatInput") {
        FloatInput *f = static_cast<FloatInput*>(*it);
        if (f->inputType == "input") {
          ImGui::SetNextItemWidth(70 * aquamarine::ui::getUIScale());
          ImGui::InputFloat(fmt::format("##{}", f->id).c_str(), &f->value);
        } else if (f->inputType == "slider") {
          ImGui::SetNextItemWidth(70 * aquamarine::ui::getUIScale());
          ImGui::SliderFloat(fmt::format("##{}", f->id).c_str(), &f->value, f->min, f->max);
        } else if (f->inputType == "step") {
          ImGui::SetNextItemWidth(70 * aquamarine::ui::getUIScale());
          ImGui::DragFloat(fmt::format("##{}", f->id).c_str(), &f->value, 0.1f, f->min, f->max);
        }
        if (f->value != f->lastValue) {
          f->lastValue = f->value;
          f->callback(f->value);
        }
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else if ((*it)->type == "IntInput") {
        IntInput *f = static_cast<IntInput*>(*it);
        if (f->inputType == "input") {
          ImGui::SetNextItemWidth(70 * aquamarine::ui::getUIScale());
          ImGui::InputInt(fmt::format("##{}", f->id).c_str(), &f->value);
        } else if (f->inputType == "slider") {
          ImGui::SetNextItemWidth(70 * aquamarine::ui::getUIScale());
          ImGui::SliderInt(fmt::format("##{}", f->id).c_str(), &f->value, f->min, f->max);
        } else if (f->inputType == "step") {
          ImGui::SetNextItemWidth(70 * aquamarine::ui::getUIScale());
          ImGui::DragInt(fmt::format("##{}", f->id).c_str(), &f->value, 1, f->min, f->max);
        }
        if (f->value != f->lastValue) {
          f->lastValue = f->value;
          f->callback(f->value);
        }
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else if ((*it)->type == "StringInput") {
        StringInput *s = static_cast<StringInput*>(*it);
        ImGui::SetNextItemWidth(70 * aquamarine::ui::getUIScale());
        ImGui::InputText(fmt::format("##{}", s->id).c_str(), &s->value[0], s->maxChars);
        if (s->value != s->lastValue) {
          s->lastValue = s->value;
          s->callback(s->value);
        }
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else if ((*it)->type == "Dropdown") {
        Dropdown *d = static_cast<Dropdown*>(*it);
        ImGui::SetNextItemWidth(70 * aquamarine::ui::getUIScale());
        if (ImGui::BeginCombo(fmt::format("##{}", d->id).c_str(), d->options[d->selected].c_str())) {
          for (int i = 0; i < d->options.size(); i++) {
            bool isSelected = d->selected == i;
            if (d->fonts[d->options[i]].first != "") {
              if (d->fonts[d->options[i]].second != "")
                aquamarine::ui::imgui::pushFont(d->fonts[d->options[i]].first, d->fonts[d->options[i]].second);
              else
                aquamarine::ui::imgui::pushFont(d->fonts[d->options[i]].first, "Regular");
            }
            if (ImGui::Selectable(d->options[i].c_str(), isSelected)) {
              d->selected = i;
              d->callback(i);
            }
            if (isSelected) {
              ImGui::SetItemDefaultFocus();
            }
            if (d->fonts[d->options[i]].first != "")
              aquamarine::ui::imgui::popFont();
          }
          ImGui::EndCombo();
        }
        if (!m_description.empty())
        {
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::Text("%s", m_description.c_str());
            ImGui::EndTooltip();
          }
        }
      } else {
        geode::log::warn("Component {} in {} has an unrecognized component type: {}!", (*it)->id, m_id, (*it)->type);
      }
    }
    if (!m_label.empty())
    {
      if (i > 0) ImGui::SameLine();
      ImGui::Text("%s", m_label.c_str());
    }
    if (!m_description.empty())
    {
      if (ImGui::IsItemHovered())
      {
        ImGui::BeginTooltip();
        ImGui::Text("%s", m_description.c_str());
        ImGui::EndTooltip();
      }
    }
  }

  cocos2d::CCNode *Widget::createCocosNode()
  {
    return nullptr;
  }

  Widget *Widget::create(std::string id)
  {
    return new Widget(id);
  }

}