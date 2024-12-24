#include "Theme.hpp"

Theme::Theme(const std::string& filePath, const sf::Vector2f& buttonPosition, const sf::Vector2f& buttonSize)
    : button(new Button(buttonPosition, buttonSize, "Toggle Theme")), displayed(false) {
    if (!texture.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load theme image");
    }
    sprite.setTexture(texture);
    button->setCallback([this]() { toggleDisplay(); });
    button->setIsHide(true);
}

Theme::~Theme() {}

void Theme::render(sf::RenderWindow& window) {
    if (displayed) {
        window.draw(sprite);
    }
    button->render(window);
}

void Theme::handleEvent(const sf::Event& event) {
    button->handleEvent(event);
}

void Theme::toggleDisplay() {
    displayed = !displayed;
}