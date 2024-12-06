#ifndef SEARCHBAR_HPP
#define SEARCHBAR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include "TextField.hpp"
#include "./../model/trie.hpp"

class SearchBar {
public:
    SearchBar(double x, double y);
    ~SearchBar();
    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);
    const std::string& getText() const;
    const std::vector<std::string>& getSuggestions() const;

private:
    void handleTextEntered(const sf::Event& event);
    void updateSuggestions();

    TextField *textField;
    Trie *trie;
    std::vector<std::string> suggestions;
    std::unordered_map<std::string, std::vector<std::string>> cache;
    std::string userInput;
};

#endif // SEARCHBAR_HPP