#ifndef RESULT_TAB_HPP
#define RESULT_TAB_HPP

#include <vector>
#include "Base.hpp"
#include <SFML/Graphics.hpp>

class ResultTab : public Base {
public:
    ResultTab(double x, double y);
    void render(sf::RenderWindow& window) override;
    void setResult(const std::vector<std::string>& result);
    void setUserInput(const std::string& userInput);
    void handleEvent(const sf::Event& event);
    void update(double elapsedTime);

private:
    std::vector<std::string> result;
    std::string userInput;
    sf::Text suggestionText;
    sf::Texture scrollBarTexture;
    sf::Texture scrollBarHandleTexture;
    sf::Sprite scrollBar;
    sf::Sprite scrollBarHandle;
    float scrollOffset;
    float scrollStep;
    bool isScrolling;

    sf::Text elapsedTime;

    void updateScrollBar();
};

#endif