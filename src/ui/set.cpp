#include "set.h"

namespace Set {
void set_text(sf::Text& text, std::string txt, float size, sf::Color color, int x, int y, float outline,
              sf::Color outline_color) {
    text.setString(txt);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setPosition(x, y);

    text.setOutlineThickness(outline);
    text.setOutlineColor(outline_color);
}

void set_image(sf::Sprite& sprite, std::array<float, 2> position, std::array<float, 2> scale,
               std::array<float, 4> sub_image) {
    if (sub_image[0] >= -0.5f) {
        sf::IntRect textureRect(sub_image[0], sub_image[1], sub_image[2], sub_image[3]);
        sprite.setTextureRect(textureRect);
    }

    sprite.setPosition(position[0], position[1]);
    sprite.setScale(scale[0], scale[1]);
}

void set_rectangle(sf::RectangleShape& rectangle, std::array<float, 2> size, sf::Color color,
                   std::array<float, 2> position, float outline, sf::Color outline_color) {
    rectangle = sf::RectangleShape(sf::Vector2f(size[0], size[1]));
    rectangle.setFillColor(color);
    rectangle.setPosition(position[0], position[1]);

    rectangle.setOutlineThickness(outline);
    rectangle.setOutlineColor(outline_color);
}
}  // namespace Set
