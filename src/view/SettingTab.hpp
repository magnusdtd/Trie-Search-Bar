#ifndef SETTING_TAB_HPP
#define SETTING_TAB_HPP

#include "Base.hpp"
#include "Button.hpp"
#include "TextField.hpp"


class SettingTab : public Base {
public:
    SettingTab(double x, double y, double sizeOfButton);
    ~SettingTab();
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event);
    void update();
    void setCallback(std::function<void()> callback);

private:
    Button *button;
    TextField *limitWordField;
    TextField *addWordField;
    TextField *removeWordField;
};

#endif // SETTING_TAB_HPP