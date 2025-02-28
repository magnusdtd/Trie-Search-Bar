#ifndef SEARCHBAR_HPP
#define SEARCHBAR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include "TextField.hpp"
#include "./../model/CompressedTrie.hpp"

class SearchBar {
public:
    SearchBar(double x, double y);
    ~SearchBar();
    void handleEvent(const sf::Event& event, CompressedTrie *&trie);
    void update();
    void render(sf::RenderWindow& window);
    const std::string& getText() const;
    const std::vector<std::string>& getSuggestions() const;
    double getElapsedTime() { return elapsedTime; }

private:
    void handleTextEntered(const sf::Event& event, CompressedTrie *&trie);
    void updateSuggestions(CompressedTrie *&trie);

    TextField *textField;
    std::vector<std::string> suggestions;
    std::string userInput;

    double elapsedTime;
};

#endif // SEARCHBAR_HPP