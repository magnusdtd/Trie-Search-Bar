#ifndef THEME_HPP
#define THEME_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class Theme {
public:
    Theme(const std::string& filePath, const sf::Vector2f& buttonPosition, const sf::Vector2f& buttonSize);
    ~Theme();
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    void toggleDisplay();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    Button *button;
    bool displayed;
};

#endif