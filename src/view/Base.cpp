#include "Base.hpp"

sf::Font Base::font;

Base::Base() : isHide(false)
{
    if (!font.loadFromFile("./../assets/fonts/arial.ttf")) {
        std::cerr << "Can't load font\n";
        exit(1);
    }
}

const sf::Font &Base::getFont() const
{
    return font;
}
