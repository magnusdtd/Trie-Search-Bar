#ifndef DROPDOWN_BOX_HPP
#define DROPDOWN_BOX_HPP

#include "Base.hpp"
#include "Button.hpp"
#include <functional>
#include <vector>
#include <string>

class DropdownBox : public Base {
public:
    DropdownBox(double x, double y, const std::vector<std::string>& items);
    ~DropdownBox();
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event);
    void setCallback(std::function<void(const std::string&)> callback);
    void toggle();

    friend class SettingTab;

private:
    Button selectedItem;
    std::vector<Button*> itemList;
    bool isOpen;
    std::function<void(const std::string&)> callback;

    void selectItem(const std::string& item);
};

#endif // DROPDOWN_BOX_HPP