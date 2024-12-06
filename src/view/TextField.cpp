#include "TextField.hpp"

TextField::TextField(double x, double y) : Base() {
    position = sf::Vector2f(x, y);

    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(x + 150, y + 40);

    if (!texture.loadFromFile("./../assets/img/search-bar.png")) {
        std::cout << "Can't load texture\n";
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void TextField::handleInput(const sf::Event& event) {
    if (event.text.unicode == '\b') { // Handle backspace
        if (!userInput.empty()) {
            userInput.pop_back();
        }
    } else if (event.text.unicode < 128) { // Handle regular characters
        userInput += static_cast<char>(event.text.unicode);
    }
}

void TextField::update() {
    inputText.setString(userInput);
}

void TextField::render(sf::RenderWindow& window) {
    window.draw(sprite); // Draw the background sprite
    window.draw(inputText); // Draw the text input
}

const std::string& TextField::getText() const {
    return userInput;
}
