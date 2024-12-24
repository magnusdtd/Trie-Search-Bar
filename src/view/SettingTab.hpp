#ifndef SETTING_TAB_HPP
#define SETTING_TAB_HPP

#include "Base.hpp"
#include "Button.hpp"
#include "TextField.hpp"
#include "DropdownBox.hpp"
#include "Theme.hpp"
#include "./../model/CompressedTrie.hpp"

class SettingTab : public Base {
public:
    SettingTab(double x, double y, double sizeOfButton);
    ~SettingTab();
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event, CompressedTrie* &trie);
    void update();

private:
    Button *button;
    TextField *limitWordField;
    TextField *addWordField;
    TextField *removeWordField;
    Theme *theme;
};

#endif // SETTING_TAB_HPP