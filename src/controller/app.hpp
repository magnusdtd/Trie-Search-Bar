#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include "./../view/SearchBar.hpp"
#include "./../view/ResultTab.hpp"
#include "./../view/SettingTab.hpp"
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

    sf::RenderWindow window;
    SearchBar *searchBar;
    ResultTab *resultTab;
    SettingTab *settingTab;
};

#endif // APP_HPP