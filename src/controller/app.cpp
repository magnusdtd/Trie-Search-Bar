#include "app.hpp"
#include <iostream>

App::App() : window(sf::VideoMode(1200, 800), "Autocomplete"), textField(new TextField(129, 155)), trie(new Trie()), resultTab(new ResultTab(172, 305)), settingTab(new SettingTab(982, 187, 65)) {
    trie->readDataFromFile("./../data/words.txt");
    trie->setLimit(5);
    std::cout << "Load data successfully!\n";
    assert(trie != nullptr);
}

App::~App() {
    delete textField;
    textField = nullptr;
    delete trie;
    trie = nullptr;
    delete resultTab;
    resultTab = nullptr;
    delete settingTab;
    settingTab = nullptr;
}

void App::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::TextEntered) {
            handleTextEntered(event);
        }

        settingTab->handleEvent(event);
    }
}

void App::handleTextEntered(const sf::Event& event) {
    textField->handleInput(event);
    userInput = textField->getText();

    if (event.text.unicode == '\b' || (event.text.unicode >= 32 && event.text.unicode <= 126)) {
        updateSuggestions();
    }

    if (event.text.unicode == 10) {  // Enter key
        trie->userSelected(userInput);
    }

    // Update the result tab with the new suggestions
    resultTab->setResult(suggestions);
}

void App::updateSuggestions() {
    if (userInput.empty()) {
        suggestions.clear();
    } else if (cache.find(userInput) != cache.end()) {
        suggestions = cache[userInput];
    } else {
        suggestions = trie->autoComplete(userInput);
        cache[userInput] = suggestions;
    }
}

void App::update() {
    textField->update();
    userInput = textField->getText();
    resultTab->setUserInput(userInput);
    resultTab->setResult(suggestions);
}

void App::render() {
    window.clear(sf::Color::White);

    textField->render(window);
    resultTab->render(window);
    settingTab->render(window);

    window.display();
}