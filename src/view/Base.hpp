#ifndef BASE_HPP
#define BASE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Base {
public:
    Base();

    const sf::Font& getFont() const;

    virtual void render(sf::RenderWindow& window) = 0;

    void setIsHide(bool isHide) { this->isHide = isHide; } 

protected:
    static sf::Font font;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;
    bool isHide;
};

#endif