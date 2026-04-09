#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <string>

namespace Set {
void set_text(sf::Text& text, std::string txt, float size, sf::Color color, int x, int y, float outline = 0,
              sf::Color outline_color = sf::Color::Black);

void set_image(sf::Sprite& sprite, std::array<float, 2> position, std::array<float, 2> scale = {1.f, 1.f},
               std::array<float, 4> sub_image = {-1, -1, -1, -1});

void set_rectangle(sf::RectangleShape& rectangle, std::array<float, 2> size, sf::Color color,
                   std::array<float, 2> position, float outline, sf::Color outline_color);
}  // namespace Set
