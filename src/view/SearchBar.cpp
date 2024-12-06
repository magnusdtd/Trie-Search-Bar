#include "SearchBar.hpp"

SearchBar::SearchBar(double x, double y) : textField(new TextField(x, y)), trie(new Trie) {
    textField->loadTextureFromFile("./../assets/img/search-bar.png");
    trie->readDataFromFile("./../data/words.txt");
    trie->setLimit(100);
    textField->setExclusionArea(sf::FloatRect(982, 187, 65, 65));
    textField->setDisBetSprTex(150, 40);
}

SearchBar::~SearchBar() {
    delete textField;
    textField = nullptr;
    delete trie;
    trie = nullptr;
}

void SearchBar::handleEvent(const sf::Event& event) {
    textField->handleEvent(event);
    if (event.type == sf::Event::TextEntered) {
        handleTextEntered(event);
    }
}

void SearchBar::handleTextEntered(const sf::Event& event) {
    userInput = textField->getText();

    if (event.text.unicode == '\b' || (event.text.unicode >= 32 && event.text.unicode <= 126)) {
        updateSuggestions();
    }

    if (event.text.unicode == 10) {  // Enter key
        trie->userSelected(userInput);
    }
}

void SearchBar::updateSuggestions() {
    if (userInput.empty()) {
        suggestions.clear();
    } else if (cache.find(userInput) != cache.end()) {
        suggestions = cache[userInput];
    } else {
        suggestions = trie->autoComplete(userInput);
        cache[userInput] = suggestions;
    }
}

void SearchBar::update() {
    textField->update();
    userInput = textField->getText();
}

void SearchBar::render(sf::RenderWindow& window) {
    textField->render(window);
}

const std::string& SearchBar::getText() const {
    return userInput;
}

const std::vector<std::string>& SearchBar::getSuggestions() const {
    return suggestions;
}