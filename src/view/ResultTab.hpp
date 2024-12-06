#ifndef RESULT_TAB_HPP
#define RESULT_TAB_HPP

#include <vector>
#include "Base.hpp"

class ResultTab : public Base {
public:
    ResultTab(double x, double y);
    void render(sf::RenderWindow& window) override;
    void setResult(const std::vector<std::string>& result);
    void setUserInput(const std::string& userInput);
private:
    std::vector<std::string> result;
    std::string userInput;
    sf::Text suggestionText;
};

#endif