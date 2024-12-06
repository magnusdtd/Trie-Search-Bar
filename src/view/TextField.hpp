#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Base.hpp"

class TextField : public Base {
public:
    TextField(double x, double y);
    void handleInput(const sf::Event& event);
    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window) override;
    const std::string& getText() const;
    void setExclusionArea(const sf::FloatRect& area);

private:
    bool isFocus;
    sf::Text inputText;
    std::string userInput;
    sf::FloatRect exclusionArea;
};

#endif // TEXTFIELD_HPP