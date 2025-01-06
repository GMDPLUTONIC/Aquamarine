#pragma once

namespace aquamarine::ui::widgets {

  struct Component {
    std::string id;
    std::string type;
    int order = 0;
  };
  struct Toggle : Component {
    bool *toggled;
    std::function<void(bool toggled)> callback;
    std::string type = "Toggle";
    bool lastToggled = false;
  };
  struct Button : Component {
    // std::string id;
    std::function<void()> callback;
    std::string type = "Button";
  };
  struct StringInput : Component {
    int maxChars = 0;
    std::string value = "";
    std::function<void(std::string value)> callback;
    std::string type = "StringInput";
    std::string lastValue = "";
  };
  struct IntInput : Component {
    // @brief input, slider, or step
    int value = 0;
    std::function<void(int value)> callback;
    int min = INT_MIN;
    int max = INT_MAX;
    std::string inputType = "input";
    std::string type = "IntInput";
    int lastValue = 0;
  };
  struct FloatInput : Component {
    // @brief input, slider, or step
    float value = 0;
    std::function<void(float value)> callback;
    float min = FLT_MIN;
    float max = FLT_MAX;
    std::string inputType = "input";
    std::string type = "FloatInput";
    float lastValue = 0;
  };
  struct Dropdown : Component {
    std::vector<std::string> options;
    int selected = 0;
    std::function<void(int selected)> callback;
    std::string type = "Dropdown";
    std::map<std::string, std::pair<std::string, std::string>> fonts = {};
  };
  class Widget {
    protected:
      std::string m_id;
      std::string m_label;
      std::string m_description;
      std::string m_tab;
      std::vector<Component*> m_components;
      Widget(std::string id) {
        m_id = id;
      }
    public:
      // these all return the widget so you can call things like myWidget->addThing()->setThat() etc
      // @brief Adds a toggle to the widget
      Widget *addToggle(std::string id, std::function<void(bool toggled)> callback, bool *toggleVal);
      // @brief Adds a button to the widget
      Widget *addButton(std::string id, std::function<void()> callback);
      // @brief Adds a string input to the widget
      Widget *addStringInput(std::string id, std::function<void(std::string value)> callback, int maxChars, std::string default_);
      // @brief Adds an integer input to the widget
      Widget *addIntInput(std::string id, std::function<void(int value)> callback, std::string type, int min, int max, int default_);
      // @brief Adds a float input to the widget
      Widget *addFloatInput(std::string id, std::function<void(float value)> callback, std::string type, float default_, float min = FLT_MIN, float max = FLT_MAX);
      // @brief Adds a dropdown to the widget
      Widget *addDropdown(std::string id, std::function<void(int selected)> callback, std::vector<std::string> options, std::string default_, std::map<std::string, std::pair<std::string, std::string>> = {});

      // @brief Removes a component from the widget.
      Widget *remove(std::string id);

      // @brief Sets the label of the widget
      Widget *setLabel(std::string label);
      // @brief Sets the description of the widget
      Widget *setDescription(std::string desc);
      // @brief Sets the tab of the widget
      Widget *setTab(std::string tab);
      
      // @brief Register this option to a tab in the UI
      Widget *registerOption(std::string tab);
      // @brief Unregister this option from the UI
      Widget *unregisterOption();

      // @brief Get the ID of the widget
      std::string getId();

      // @brief Get the label of the widget
      std::string getLabel();
      // @brief Get the description of the widget
      std::string getDescription();
      // @brief Get the tab of the widget
      std::string getTab();
      // @brief Get the components of the widget
      std::vector<Component*> getComponents();
      // @brief Get a component by ID
      Component *getComponent(std::string id);

      void imRender();
      cocos2d::CCNode *createCocosNode();

      // @brief Create a new widget
      static Widget *create(std::string id);
  };
}