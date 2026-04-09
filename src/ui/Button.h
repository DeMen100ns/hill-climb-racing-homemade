#pragma once

#include <SFML/Graphics.hpp>

class Button {
private:
    sf::Font font;
    sf::Text text;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Button();
    Button(sf::Font font, sf::Text text, sf::Texture texture, sf::Sprite sprite);
    Button(const Button& other);
    Button& operator=(const Button& other);

    void show(sf::RenderWindow& window);
    bool touch(sf::Event& event);
};
