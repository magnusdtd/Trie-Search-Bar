#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include "./../view/TextField.hpp"
#include "./../view/ResultTab.hpp"
#include "./../view/SettingTab.hpp"
#include "./../model/trie.hpp"
#include <unordered_map>
#include <assert.h>

class App {
public:
    App();
    ~App();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleTextEntered(const sf::Event& event);
    void updateSuggestions();


    sf::RenderWindow window;
    TextField *textField;
    Trie *trie;
    ResultTab *resultTab;
    SettingTab *settingTab;
    std::vector<std::string> suggestions;
    std::unordered_map<std::string, std::vector<std::string>> cache;  // Cache for autocomplete results
    std::string userInput;
};

#endif