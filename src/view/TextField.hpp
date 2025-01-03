#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <functional>
#include "Base.hpp"

class TextField : public Base {
public:
    TextField(double x, double y);
    TextField(double x, double y, const std::string &textureFilePath);
    void handleInput(const sf::Event& event);
    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window) override;
    const std::string& getText() const;
    void setText(const std::string& text);
    void setExclusionArea(const sf::FloatRect& area);
    void loadTextureFromFile(const std::string& filePath);
    bool getIsFocus() { return isFocus; }
    void setDisBetSprTex(double disBetSprTexX, double disBetSprTexY);
    void setTextUpperBound(int textUpperBound) { this->textUpperBound = textUpperBound; }
    friend class SettingTab;

private:
    bool isFocus;
    sf::Text inputText;
    std::string userInput;
    sf::FloatRect exclusionArea;
    std::string textureFilePath;
    size_t displayStartIndex;
    size_t textUpperBound;
};

#endif // TEXTFIELD_HPP