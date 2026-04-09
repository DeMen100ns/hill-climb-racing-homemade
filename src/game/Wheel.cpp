#include "Wheel.h"

Wheel::Wheel(b2WorldId worldId, b2Vec2 position, float radius, float density, float friction, float restitution)
    : radius(radius) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    wheel = b2CreateBody(worldId, &bodyDef);

    b2Circle circleShape;
    circleShape.radius = radius;

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.friction = friction;
    shapeDef.restitution = restitution;

    b2CreateCircleShape(wheel, &shapeDef, &circleShape);
}

b2Vec2 Wheel::get_position() {
    return b2Body_GetPosition(wheel);
}

float Wheel::get_rotation() {
    return b2Rot_GetAngle(b2Body_GetRotation(wheel));
}

float Wheel::get_radius() {
    return radius;
}

b2BodyId Wheel::get_body() {
    return wheel;
}

void Wheel::show(sf::RenderWindow& window, float position) {
    sf::CircleShape ball(radius * SCALE);
    ball.setFillColor(sf::Color::Red);
    ball.setOrigin(radius * SCALE, radius * SCALE);
    ball.setPosition(position * SCALE, 600.0f - b2Body_GetPosition(wheel).y * SCALE);
    window.draw(ball);
}
