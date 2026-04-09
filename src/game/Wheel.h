#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Wheel {
private:
    const float SCALE = 25.f;
    b2BodyId wheel;
    float radius;

public:
    Wheel(b2WorldId worldId, b2Vec2 position, float radius, float density, float friction, float restitution);

    b2Vec2 get_position();
    float get_rotation();
    float get_radius();
    b2BodyId get_body();

    void show(sf::RenderWindow& window, float position);
};
