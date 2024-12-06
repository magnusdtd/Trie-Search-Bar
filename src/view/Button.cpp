#include "Button.hpp"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text) {
    buttonShape.setPosition(position);
    buttonShape.setSize(size);
    buttonShape.setFillColor(sf::Color::Blue);

    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(
        position.x + (size.x - buttonText.getLocalBounds().width) / 2,
        position.y + (size.y - buttonText.getLocalBounds().height) / 2
    );
}

void Button::setCallback(std::function<void()> callback) {
    this->callback = callback;
}

void Button::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (buttonShape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                if (callback) {
                    callback();
                }
            }
        }
    }
}

void Button::render(sf::RenderWindow& window) {
    if (!isHide) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }
}