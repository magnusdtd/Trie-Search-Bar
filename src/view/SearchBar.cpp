#include "SearchBar.hpp"

SearchBar::SearchBar(double x, double y) : textField(new TextField(x, y)) {
    textField->loadTextureFromFile("./../assets/img/search-bar.png");
    textField->setExclusionArea(sf::FloatRect(982, 187, 65, 65));
    textField->setDisBetSprTex(150, 40);
    textField->setTextUpperBound(400.f);
}

SearchBar::~SearchBar() {
    delete textField;
    textField = nullptr;
}

void SearchBar::handleEvent(const sf::Event& event, CompressedTrie *&trie) {
    textField->handleEvent(event);
    if (event.type == sf::Event::TextEntered) {
        handleTextEntered(event, trie);
    }
}

void SearchBar::handleTextEntered(const sf::Event& event, CompressedTrie *&trie) {
    userInput = textField->getText();

    if (event.text.unicode == '\b' || (event.text.unicode >= 32 && event.text.unicode <= 126)) {
        updateSuggestions(trie);
    }

    if (event.text.unicode == 10) {  // Enter key
        trie->userSelected(userInput);
    }
}

void SearchBar::updateSuggestions(CompressedTrie *&trie) {
    if (userInput.empty()) {
        suggestions.clear();
    } else if (cache.find(userInput) != cache.end()) {
        suggestions = cache[userInput];
    } else {

        auto startTime = std::chrono::high_resolution_clock::now();
        suggestions = trie->search(userInput);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        elapsedTime = duration.count();

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