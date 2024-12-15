#include "TextField.hpp"

TextField::TextField(double x, double y) : Base(), isFocus(false), textureFilePath("")
{
    position = sf::Vector2f(x, y);

    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(x + 150, y + 40);

    sprite.setPosition(position);    
}

TextField::TextField(double x, double y, const std::string &textureFilePath) : Base(), isFocus(false), textureFilePath(textureFilePath)
{
    position = sf::Vector2f(x, y);

    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(x, y);

    if (!texture.loadFromFile(textureFilePath)) {
        std::cout << "Can't load texture\n";
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void TextField::handleInput(const sf::Event& event) {
    if (isFocus) {
        // Handle backspace
        if (event.text.unicode == '\b') { 
            if (!userInput.empty()) {
                userInput.pop_back();
            }
        }
        // Handle enter key
        else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
            return;
        // Handle regular characters
        } else if (event.text.unicode < 128) { 
            userInput += static_cast<char>(event.text.unicode);
        }
    }
}

void TextField::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (sprite.getGlobalBounds().contains(mousePos) && !exclusionArea.contains(mousePos)) {
            isFocus = true;
        } else {
            isFocus = false;
        }
    } else if (event.type == sf::Event::TextEntered) {
        handleInput(event);
    }
}

void TextField::update() {
    inputText.setString(userInput);
}

void TextField::render(sf::RenderWindow& window) {
    if (!textureFilePath.empty()) 
        window.draw(sprite);
    window.draw(inputText);
}

const std::string& TextField::getText() const {
    return userInput;
}

void TextField::setText(const std::string& text) {
    userInput = text;
    inputText.setString(userInput);
}

void TextField::setExclusionArea(const sf::FloatRect& area) {
    exclusionArea = area;
}

void TextField::loadTextureFromFile(const std::string &filePath)
{
    textureFilePath = filePath;
    if (!texture.loadFromFile(textureFilePath)) {
        std::cout << "Can't load texture\n";
        exit(1);
    }
    sprite.setTexture(texture);   
}

void TextField::setDisBetSprTex(double disBetSprTexX, double disBetSprTexY)
{
    inputText.setPosition(position.x + disBetSprTexX, position.y + disBetSprTexY);
}
