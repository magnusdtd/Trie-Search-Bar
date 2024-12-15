#include "SettingTab.hpp"

SettingTab::SettingTab(double x, double y, double sizeOfButton) 
    : button(new Button(sf::Vector2f(x, y), sf::Vector2f(sizeOfButton, sizeOfButton), "OK")),
      limitWordField(new TextField(x - 118, y + 188)),
      addWordField(new TextField(x - 118, y + 188 + 52)),
      removeWordField(new TextField(x - 118, y + 188 + 52 * 2)),
      algorithmDropdown(new DropdownBox(x - 118, y + 188 + 52 * 3, {"Trie", "DAWG"})),  // Initialize the dropdown
      currentAlgorithm(AlgorithmType::Trie)
{
    position = sf::Vector2f(x - 379, y + 68);

    button->setIsHide(true);
    algorithmDropdown->setIsHide(true);

    isHide = true;

    if (!texture.loadFromFile("./../assets/img/setting-tab.png")) {
        std::cout << "Can't load texture\n";
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);

    button->setCallback([&]() -> void {
        std::cout << "Button of setting tab is pressed\n";
        isHide = !isHide;
        algorithmDropdown->isHide = !algorithmDropdown->isHide;
    });

    algorithmDropdown->setCallback([&](const std::string& selected) -> void {
        if (selected == "Trie") {
            switchAlgorithm(AlgorithmType::Trie);
        } else if (selected == "DAWG") {
            switchAlgorithm(AlgorithmType::DAWG);
        }
    });

    limitWordField->loadTextureFromFile("./../assets/img/text-box.png");
    addWordField->loadTextureFromFile("./../assets/img/text-box.png");
    removeWordField->loadTextureFromFile("./../assets/img/text-box.png");
    limitWordField->setDisBetSprTex(7, 2);
    addWordField->setDisBetSprTex(7, 2);
    removeWordField->setDisBetSprTex(7, 2);
}

SettingTab::~SettingTab()
{
    delete button;
    button = nullptr;
    delete algorithmDropdown;
    algorithmDropdown = nullptr;
    delete limitWordField;
    limitWordField = nullptr;
    delete addWordField;
    addWordField = nullptr;
    delete removeWordField;
    removeWordField = nullptr;
}

void SettingTab::render(sf::RenderWindow &window) {
    button->render(window);
    if (!isHide) {
        window.draw(sprite);
        limitWordField->render(window);
        addWordField->render(window);
        removeWordField->render(window);
        algorithmDropdown->render(window);
    }
}

void SettingTab::handleEvent(const sf::Event& event, Trie* &trie) {
    button->handleEvent(event);
    algorithmDropdown->handleEvent(event);
    limitWordField->handleEvent(event);
    addWordField->handleEvent(event);
    removeWordField->handleEvent(event);

    if (event.type == sf::Event::TextEntered && event.text.unicode == 13) {
        std::string limitWordText = limitWordField->getText();
        std::string addWordText = addWordField->getText();
        std::string removeWordText = removeWordField->getText();

        if (!limitWordText.empty() && limitWordField->getIsFocus()) {
            try {
                int limit = std::stoi(limitWordText);
                std::cout << "Set limit to " << limit << "\n";
                trie->setLimit(limit);
                limitWordField->setText(limitWordText);
                limitWordField->userInput.clear();
            } catch (...) {
                std::cout << "limitWordText is not a number\n";
            }
        }

        if (!addWordText.empty() && addWordField->getIsFocus()) {
            std::cout << "Add string: " << addWordText << "\n";
            trie->addString(addWordText);
            addWordField->setText(addWordText);
            addWordField->userInput.clear();
        }

        if (!removeWordText.empty() && removeWordField->getIsFocus()) {
            std::cout << "Remove string: " << removeWordText << "\n";
            trie->deleteString(removeWordText);
            removeWordField->setText(removeWordText);
            removeWordField->userInput.clear();
        }
    }
}

void SettingTab::update()
{
    limitWordField->update();
    addWordField->update();
    removeWordField->update();
}

void SettingTab::switchAlgorithm(AlgorithmType algorithm) {
    currentAlgorithm = algorithm;
    if (algorithm == AlgorithmType::Trie) {
        std::cout << "Switched to Trie\n";
    } else if (algorithm == AlgorithmType::DAWG) {
        std::cout << "Switched to DAWG\n";
    }
    // Add more algorithms here if needed
}