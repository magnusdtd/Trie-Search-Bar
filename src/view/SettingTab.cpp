#include "SettingTab.hpp"

SettingTab::SettingTab(double x, double y, double sizeOfButton) 
    : button(new Button(sf::Vector2f(x, y), sf::Vector2f(sizeOfButton, sizeOfButton), "OK")),
      limitWordField(new TextField(x - 118, y + 188)),
      addWordField(new TextField(x - 118, y + 188 + 52)),
      removeWordField(new TextField(x - 118, y + 188 + 52 * 2))
{
    position = sf::Vector2f(x - 379, y + 68);

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

    limitWordField->loadTextureFromFile("./../assets/img/text-box.png");
    addWordField->loadTextureFromFile("./../assets/img/text-box.png");
    removeWordField->loadTextureFromFile("./../assets/img/text-box.png");
    limitWordField->setDisBetSprTex(7, 2);
    addWordField->setDisBetSprTex(7, 2);
    removeWordField->setDisBetSprTex(7, 2);
}

SettingTab::~SettingTab()
{
    delete button;
    button = nullptr;
    delete limitWordField;
    limitWordField = nullptr;
    delete addWordField;
    addWordField = nullptr;
    delete removeWordField;
    removeWordField = nullptr;
}

void SettingTab::render(sf::RenderWindow &window) {
    button->render(window);
    if (!isHide) {
        window.draw(sprite);
        limitWordField->render(window);
        addWordField->render(window);
        removeWordField->render(window);
    }
}

void SettingTab::handleEvent(const sf::Event& event) {
    button->handleEvent(event);
    limitWordField->handleEvent(event);
    addWordField->handleEvent(event);
    removeWordField->handleEvent(event);

    if (event.type == sf::Event::TextEntered && event.text.unicode == 13) {
        std::string limitWordText = limitWordField->getText();
        std::string addWordText = addWordField->getText();
        std::string removeWordText = removeWordField->getText();

        if (!limitWordText.empty() && limitWordField->getIsFocus()) {
            try {
                int limit = std::stoi(limitWordText);
            } catch (...) {
                std::cout << "limitWordText is not a number\n";
            }
            std::cout << "Call set Limit function\n";
            limitWordField->setText("");
        }

        if (!addWordText.empty() && addWordField->getIsFocus()) {
            std::cout << "Call add string function\n";
            addWordField->setText("");
        }

        if (!removeWordText.empty() && removeWordField->getIsFocus()) {
            std::cout << "Call remove string function\n";
            removeWordField->setText("");
        }
    }
}

void SettingTab::update()
{
    limitWordField->update();
    addWordField->update();
    removeWordField->update();
}

void SettingTab::setCallback(std::function<void()> callback)
{
    this->button->setCallback(callback);
}
