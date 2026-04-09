#include "Button.h"

Button::Button() = default;

Button::Button(sf::Font font, sf::Text text, sf::Texture texture, sf::Sprite sprite)
    : font(font), text(text), texture(texture), sprite(sprite) {}

Button::Button(const Button& other) {
    font = other.font;
    text = other.text;
    texture = other.texture;
    sprite = other.sprite;
}

Button& Button::operator=(const Button& other) {
    if (this != &other) {
        font = other.font;
        text = other.text;
        texture = other.texture;
        sprite = other.sprite;
    }
    return *this;
}

void Button::show(sf::RenderWindow& window) {
    sprite.setTexture(texture);
    window.draw(sprite);
    text.setFont(font);
    window.draw(text);
}

bool Button::touch(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ||
        event.type == sf::Event::TouchBegan) {
        float mouseX, mouseY;
        if (event.type == sf::Event::MouseButtonPressed) {
            mouseX = event.mouseButton.x;
            mouseY = event.mouseButton.y;
        } else {
            mouseX = event.touch.x;
            mouseY = event.touch.y;
        }

        sprite.setTexture(texture);

        sf::Vector2f position = sprite.getPosition();
        sf::FloatRect bounds = sprite.getGlobalBounds();

        if (position.x <= mouseX && mouseX <= position.x + bounds.width && position.y <= mouseY &&
            mouseY <= position.y + bounds.height) {
            return true;
        }
    }
    return false;
}
