#include "SettingTab.hpp"

SettingTab::SettingTab(double x, double y, double sizeOfButton) 
    : button(new Button(sf::Vector2f(x, y), sf::Vector2f(sizeOfButton, sizeOfButton), "OK")),
      limitWordField(new TextField(x - 118, y + 188)),
      addWordField(new TextField(x - 118, y + 188 + 52)),
      removeWordField(new TextField(x - 118, y + 188 + 52 * 2)),
      algorithmDropdown(new DropdownBox(x - 118, y + 188 + 52 * 3, {"Trie", "SuffixAutomaton"})),  // Initialize the dropdown
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
        } else if (selected == "SuffixAutomaton") {
            switchAlgorithm(AlgorithmType::SuffixAutomaton);
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

void SettingTab::handleEvent(const sf::Event& event) {
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
                // Call set limit function based on current algorithm
                if (currentAlgorithm == AlgorithmType::Trie) {
                    // Set limit for Trie
                } else if (currentAlgorithm == AlgorithmType::SuffixAutomaton) {
                    // Set limit for SuffixAutomaton
                }
            } catch (...) {
                std::cout << "limitWordText is not a number\n";
            }
            limitWordField->setText("");
        }

        if (!addWordText.empty() && addWordField->getIsFocus()) {
            std::cout << "Add string: " << addWordText << "\n";
            // Call add string function based on current algorithm
            if (currentAlgorithm == AlgorithmType::Trie) {
                // Add string to Trie
            } else if (currentAlgorithm == AlgorithmType::SuffixAutomaton) {
                // Add string to SuffixAutomaton
            }
            addWordField->setText("");
        }

        if (!removeWordText.empty() && removeWordField->getIsFocus()) {
            std::cout << "Remove string: " << removeWordText << "\n";
            // Call remove string function based on current algorithm
            if (currentAlgorithm == AlgorithmType::Trie) {
                // Remove string from Trie
            } else if (currentAlgorithm == AlgorithmType::SuffixAutomaton) {
                // Remove string from SuffixAutomaton
            }
            removeWordField->setText("");
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
    } else if (algorithm == AlgorithmType::SuffixAutomaton) {
        std::cout << "Switched to SuffixAutomaton\n";
    }
    // Add more algorithms here if needed
}