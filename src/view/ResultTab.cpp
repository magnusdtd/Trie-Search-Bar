#include "ResultTab.hpp"

ResultTab::ResultTab(double x, double y) : Base(), scrollOffset(0), isScrolling(false) {
    position = sf::Vector2f(x, y);
    suggestionText.setFillColor(sf::Color::Black);
    suggestionText.setFont(font);
    suggestionText.setCharacterSize(24);

    if (!texture.loadFromFile("./../assets/img/result-tab.png")) {
        std::cout << "Can't load texture\n";
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);

    // Load scroll bar textures
    if (!scrollBarTexture.loadFromFile("./../assets/img/scroll-bar.png")) {
        std::cout << "Can't load scroll bar texture\n";
        exit(1);
    }
    if (!scrollBarHandleTexture.loadFromFile("./../assets/img/scroll-bar-handle.png")) {
        std::cout << "Can't load scroll bar handle texture\n";
        exit(1);
    }

    // Initialize scroll bar
    scrollBar.setTexture(scrollBarTexture);
    scrollBar.setPosition(position.x + 822, position.y + 15);

    scrollBarHandle.setTexture(scrollBarHandleTexture);
    scrollBarHandle.setPosition(position.x + 826, position.y + 20);

    scrollStep = 30;

    elapsedTime.setPosition(400, 607);
    elapsedTime.setFont(font);
    elapsedTime.setFillColor(sf::Color::Blue);
    elapsedTime.setCharacterSize(24);
}

void ResultTab::render(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(elapsedTime);

    if (userInput.empty()) {
        std::string initilizationText = "Enter your word";
        suggestionText.setString(initilizationText);
        suggestionText.setPosition(position.x + 197, position.y + 26);
        window.draw(suggestionText);
    } else if (result.empty() && !userInput.empty()) {
        std::string emptyMessage = "No word match";
        suggestionText.setString(emptyMessage);
        suggestionText.setPosition(position.x + 197, position.y + 26);
        window.draw(suggestionText);
    } else {
        size_t startIndex = static_cast<size_t>(scrollOffset / scrollStep);
        size_t endIndex = std::min(startIndex + 9, result.size());

        for (size_t i = startIndex; i < endIndex; ++i) {
            suggestionText.setString(result[i]);
            suggestionText.setPosition(position.x + 197, position.y + 24 + (i - startIndex) * 30);
            window.draw(suggestionText);
        }
    }

    window.draw(scrollBar);
    window.draw(scrollBarHandle);
}

void ResultTab::setResult(const std::vector<std::string> &result) {
    this->result = result;
    updateScrollBar();
}

void ResultTab::setUserInput(const std::string &userInput) {
    this->userInput = userInput;
    updateScrollBar();
}

void ResultTab::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (scrollBar.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            isScrolling = true;
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        isScrolling = false;
    } else if (event.type == sf::Event::MouseMoved) {
        if (isScrolling) {
            float newY = event.mouseMove.y - scrollBar.getPosition().y;
            newY = std::max(newY, 0.f);
            newY = std::min(newY, scrollBar.getGlobalBounds().height - scrollBarHandle.getGlobalBounds().height);
            scrollBarHandle.setPosition(scrollBarHandle.getPosition().x, scrollBar.getPosition().y + newY);
            scrollOffset = (newY / (scrollBar.getGlobalBounds().height - scrollBarHandle.getGlobalBounds().height)) * (result.size() * scrollStep - 300);
        }
    } else if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollOffset -= scrollStep;
        } else {
            scrollOffset += scrollStep;
        }
        scrollOffset = std::max(scrollOffset, 0.f);
        scrollOffset = std::min(scrollOffset, static_cast<float>(result.size() * scrollStep - 300));
        updateScrollBar();
    } else if (event.type == sf::Event::TextEntered) {
        scrollOffset = 0;
    }
}

void ResultTab::update(double elapsedTime)
{
    this->elapsedTime.setString(std::to_string(elapsedTime / 1000) + " seconds");
}

void ResultTab::updateScrollBar() {
    if (result.empty()) {
        scrollBarHandle.setScale(1.f, 1.f); // Set a small scale for the handle
        scrollBarHandle.setPosition(scrollBar.getPosition().x + 4, scrollBar.getPosition().y + 4); // Position it at the top
        return;
    }

    float handleHeight = std::max(50.f, std::min(scrollBar.getGlobalBounds().height, scrollBar.getGlobalBounds().height * (300.f / (result.size() * scrollStep))));
    scrollBarHandle.setScale(1.f, handleHeight / scrollBarHandle.getTexture()->getSize().y);
    float handlePosition = (scrollOffset / (result.size() * scrollStep - 300)) * (scrollBar.getGlobalBounds().height - handleHeight);
    handlePosition = std::max(handlePosition, 0.f);
    handlePosition = std::min(handlePosition, scrollBar.getGlobalBounds().height - handleHeight);
    scrollBarHandle.setPosition(scrollBarHandle.getPosition().x, scrollBar.getPosition().y + handlePosition);
}