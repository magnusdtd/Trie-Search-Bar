#ifndef SETTING_TAB_HPP
#define SETTING_TAB_HPP

#include "Base.hpp"
#include "Button.hpp"

class SettingTab : public Base {
public:
    SettingTab(double x, double y, double sizeOfButton);
    ~SettingTab();
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event);
    void setCallback(std::function<void()> callback);

private:
    Button *button;
};

#endif // SETTING_TAB_HPP