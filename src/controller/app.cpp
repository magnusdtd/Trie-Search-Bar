#include "app.hpp"

App::App() : 
    window(sf::VideoMode(1200, 800), "Autocomplete"), 
    searchBar(new SearchBar(129, 155)), 
    resultTab(new ResultTab(172, 305)), 
    settingTab(new SettingTab(982, 187, 65)) {
    std::cout << "Load data successfully!\n";
}

App::~App() {
    delete searchBar;
    searchBar = nullptr;
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

        searchBar->handleEvent(event);
        settingTab->handleEvent(event);
        resultTab->handleEvent(event);
    }
}

void App::update() {
    searchBar->update();
    resultTab->setUserInput(searchBar->getText());
    resultTab->setResult(searchBar->getSuggestions());
    settingTab->update();
}

void App::render() {
    window.clear(sf::Color::White);

    searchBar->render(window);
    resultTab->render(window);
    settingTab->render(window);

    window.display();
}