#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Base.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class Button : public Base {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text);

    void setCallback(std::function<void()> callback);
    void handleEvent(const sf::Event& event);
    void render(sf::RenderWindow& window);
    void setText(const std::string& text);

    friend class DropdownBox;
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    std::function<void()> callback;
};

#endif // BUTTON_HPP