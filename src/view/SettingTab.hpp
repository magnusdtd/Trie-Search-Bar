#ifndef SETTING_TAB_HPP
#define SETTING_TAB_HPP

#include "Base.hpp"
#include "Button.hpp"
#include "TextField.hpp"
#include "DropdownBox.hpp"

enum class AlgorithmType {
    Trie,
    SuffixAutomaton
    // Add more algorithms here
};

class SettingTab : public Base {
public:
    SettingTab(double x, double y, double sizeOfButton);
    ~SettingTab();
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event);
    void update();

private:
    Button *button;
    TextField *limitWordField;
    TextField *addWordField;
    TextField *removeWordField;
    DropdownBox *algorithmDropdown;
    AlgorithmType currentAlgorithm;

    void switchAlgorithm(AlgorithmType algorithm);
};

#endif // SETTING_TAB_HPP