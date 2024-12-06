#include "ResultTab.hpp"

ResultTab::ResultTab(double x, double y) : Base()
{
    position = sf::Vector2f(x, y);
    suggestionText.setFillColor(sf::Color::Black);
    suggestionText.setFont(font);
    suggestionText.setCharacterSize(24);

    if (!texture.loadFromFile("./../assets/img/result-tab.png")) {
        std::cout << "Can't load texture\n";
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void ResultTab::render(sf::RenderWindow &window)
{
    window.draw(sprite);

    if (userInput.empty()) {
        std::string initilizationText = "Enter your word";
        suggestionText.setString(initilizationText);
        suggestionText.setPosition(position.x + 197, position.y + 26);
        window.draw(suggestionText);
    } else if (result.empty() && !userInput.empty()) {
        std::string emptyMessage = "No word match";
        suggestionText.setString(emptyMessage);
        suggestionText.setPosition(position.x + 197, position.y + 26);
        window.draw(suggestionText);
    } else {
        for (size_t i = 0; i < result.size() && i < 10; ++i) {
            suggestionText.setString(result[i]);
            suggestionText.setPosition(position.x + 197, position.y + 26 + i * 30);
            window.draw(suggestionText);
        }
    }
}

void ResultTab::setResult(const std::vector<std::string> &result)
{
    this->result = result;
}

void ResultTab::setUserInput(const std::string &userInput)
{
    this->userInput = userInput;
}
