#include "app.hpp"

App::App() : 
    window(sf::VideoMode(1200, 800), "Autocomplete"), 
    searchBar(new SearchBar(129, 155)), 
    resultTab(new ResultTab(172, 305)), 
    settingTab(new SettingTab(982, 187, 65)),
    trie(new CompressedTrie())
{
    std::cout << "Load data successfully!\n";
    trie->readDataFromFile("./data/merged_words.txt");
    trie->setLimitWord(100);
}

App::~App() {
    delete searchBar;
    searchBar = nullptr;
    delete resultTab;
    resultTab = nullptr;
    delete settingTab;
    settingTab = nullptr;
    delete trie;
    trie = nullptr;
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

        searchBar->handleEvent(event, trie);
        settingTab->handleEvent(event, trie);
        resultTab->handleEvent(event);
    }
}

void App::update() {
    searchBar->update();
    resultTab->setUserInput(searchBar->getText());
    resultTab->setResult(searchBar->getSuggestions());
    settingTab->update();
    // std::cout << "Check elapsed time before update function of App " << searchBar->getElapsedTime() << " ms\n";
    resultTab->update(searchBar->getElapsedTime());
}

void App::render() {
    window.clear(sf::Color::White);

    searchBar->render(window);
    resultTab->render(window);
    settingTab->render(window);

    window.display();
}