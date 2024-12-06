#include "SettingTab.hpp"

SettingTab::SettingTab(double x, double y, double sizeOfButton) : button(new Button(sf::Vector2f(x, y), sf::Vector2f(sizeOfButton, sizeOfButton), "OK"))
{
    position = sf::Vector2f(x - 379, y + 68); // 969, 183

    button->setIsHide(true);

    isHide = true;

    if (!texture.loadFromFile("./../assets/img/setting-tab.png")) {
        std::cout << "Can't load texture\n";
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);

    button->setCallback([&]() -> void {
        std::cout << "Button of setting tab is pressed\n";
        isHide = !isHide;
    });
}

SettingTab::~SettingTab()
{
    delete button;
    button = nullptr;
}

void SettingTab::render(sf::RenderWindow &window) {
    button->render(window);
    if (!isHide) {
        window.draw(sprite);
    }
}

void SettingTab::handleEvent(const sf::Event& event) {
    button->handleEvent(event);
}

void SettingTab::setCallback(std::function<void()> callback)
{
    this->button->setCallback(callback);
}
