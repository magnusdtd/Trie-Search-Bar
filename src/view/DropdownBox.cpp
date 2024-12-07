#include "DropdownBox.hpp"

DropdownBox::DropdownBox(double x, double y, const std::vector<std::string>& items)
    : isOpen(false),
      selectedItem(sf::Vector2f(x, y), sf::Vector2f(142, 34), items.empty() ? "" : items[0])
{
    selectedItem.setCallback([this]() {
        toggle();
    });
    selectedItem.buttonShape.setFillColor(sf::Color(252, 244, 187));
    selectedItem.buttonText.setFillColor(sf::Color::Black);

    double itemY = y + 35;
    for (const auto& item : items) {
        Button *button = new Button(sf::Vector2f(x, itemY), sf::Vector2f(142, 34), item);
        button->setCallback([this, item]() {
            selectItem(item);
            toggle();
        });
        button->buttonShape.setFillColor(sf::Color(252, 244, 187));
        button->buttonText.setFillColor(sf::Color::Black);
        itemList.push_back(button);
        itemY += 35;
    }
}

DropdownBox::~DropdownBox()
{
    for (Button *item : itemList) {
        delete item;
        item = nullptr;
    }
}

void DropdownBox::render(sf::RenderWindow& window) {
    selectedItem.render(window);
    if (isOpen && !isHide) {
        for (Button* &item : itemList) {
            item->render(window);
        }
    }
}

void DropdownBox::handleEvent(const sf::Event& event) {
    selectedItem.handleEvent(event);
    if (isOpen) {
        for (Button* &item : itemList) {
            item->handleEvent(event);
        }
    }
}

void DropdownBox::setCallback(std::function<void(const std::string&)> callback) {
    this->callback = callback;
}

void DropdownBox::toggle() {
    isOpen = !isOpen;
}

void DropdownBox::selectItem(const std::string& item) {
    selectedItem.setText(item);
    if (callback) {
        callback(item);
    }
}