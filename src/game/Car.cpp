#include "Car.h"

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include "../ui/set.h"

using namespace std;

namespace {
string int_to_string(int val) {
    string ans = "";
    vector<int> d;
    while (val > 0) {
        d.push_back(val % 10);
        val /= 10;
    }
    if (d.size() == 0) {
        ans = "0";
        return ans;
    }
    for (int i = 0; i < d.size(); ++i) {
        char c = d[i] + '0';
        ans += c;
        if (i % 3 == 2 && i != static_cast<int>(d.size()) - 1) ans += " ";
    }
    reverse(ans.begin(), ans.end());

    return ans;
}
}  // namespace

Car::Car() {
    const string PATH = "src/";
    m_chassisId = {};
    m_rearWheelId = {};
    m_frontWheelId = {};
    m_rearAxleId = {};
    m_frontAxleId = {};
    m_bodyId = {};
    m_headId = {};
    m_carbodyId = {};
    m_bodyheadId = {};
    m_isSpawned = false;

    hud_font_.loadFromFile(PATH + "font/Changa-Bold.ttf");
    head_texture_.loadFromFile(PATH + "image/headLarge.png");
    wheel_texture_.loadFromFile(PATH + "image/wheel_car.png");
    car_texture_.loadFromFile(PATH + "image/car.png");
}

void Car::Spawn(b2WorldId worldId, b2Vec2 position, float scale, float hertz, float dampingRatio, float torque) {
    assert(m_isSpawned == false);

    assert(B2_IS_NULL(m_chassisId));
    assert(B2_IS_NULL(m_frontWheelId));
    assert(B2_IS_NULL(m_rearWheelId));

    b2Polygon chassis = b2MakeBox(7.f / 3 * scale, 1.0f * scale);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.f / scale;
    shapeDef.friction = 0.2f;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Add({0.0f, 1.25f * scale}, position);
    m_chassisId = b2CreateBody(worldId, &bodyDef);
    b2CreatePolygonShape(m_chassisId, &shapeDef, &chassis);

    b2ShapeDef shapeDef2 = b2DefaultShapeDef();
    shapeDef2.density = 0.01f / scale;
    shapeDef2.friction = 0.01f;

    b2BodyDef bodyDef2 = b2DefaultBodyDef();
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.position = b2Add({0.0f, 2.55f * scale}, position);
    m_bodyId = b2CreateBody(worldId, &bodyDef2);
    b2CreatePolygonShape(m_bodyId, &shapeDef, &chassis);

    b2Circle circ = {{0.0f, 0.0f}, 7.f / 9 * scale};

    shapeDef.density = 0.01f / scale;
    shapeDef.friction = 0.01f;

    bodyDef.position = b2Add({0.0f * scale, 2.85f * scale}, position);
    m_headId = b2CreateBody(worldId, &bodyDef);
    b2CreateCircleShape(m_headId, &shapeDef, &circ);

    b2Circle circle = {{0.0f, 0.0f}, 7.f / 9 * scale};

    shapeDef.density = 8.0f / scale;
    shapeDef.friction = 2.5f;

    bodyDef.position = b2Add({-1.4f * scale, -0.05f * scale}, position);
    bodyDef.allowFastRotation = true;
    m_rearWheelId = b2CreateBody(worldId, &bodyDef);
    b2CreateCircleShape(m_rearWheelId, &shapeDef, &circle);

    bodyDef.position = b2Add({1.4f * scale, -0.05f * scale}, position);
    bodyDef.allowFastRotation = true;
    m_frontWheelId = b2CreateBody(worldId, &bodyDef);
    b2CreateCircleShape(m_frontWheelId, &shapeDef, &circle);

    b2Vec2 axis = {0.0f, 0.5f};
    b2Vec2 pivot = b2Body_GetPosition(m_rearWheelId);

    b2WheelJointDef jointDef = b2DefaultWheelJointDef();

    jointDef.bodyIdA = m_chassisId;
    jointDef.bodyIdB = m_rearWheelId;
    jointDef.localAxisA = b2Body_GetLocalVector(jointDef.bodyIdA, axis);
    jointDef.localAnchorA = b2Body_GetLocalPoint(jointDef.bodyIdA, pivot);
    jointDef.localAnchorB = b2Body_GetLocalPoint(jointDef.bodyIdB, pivot);
    jointDef.motorSpeed = 0.0f;
    jointDef.maxMotorTorque = torque;
    jointDef.enableMotor = true;
    jointDef.hertz = hertz;
    jointDef.dampingRatio = dampingRatio;
    jointDef.lowerTranslation = -0.25f * scale;
    jointDef.upperTranslation = 0.25f * scale;
    jointDef.enableLimit = true;
    m_rearAxleId = b2CreateWheelJoint(worldId, &jointDef);

    pivot = b2Body_GetPosition(m_frontWheelId);
    jointDef.bodyIdA = m_chassisId;
    jointDef.bodyIdB = m_frontWheelId;
    jointDef.localAxisA = b2Body_GetLocalVector(jointDef.bodyIdA, axis);
    jointDef.localAnchorA = b2Body_GetLocalPoint(jointDef.bodyIdA, pivot);
    jointDef.localAnchorB = b2Body_GetLocalPoint(jointDef.bodyIdB, pivot);
    jointDef.motorSpeed = 0.0f;
    jointDef.maxMotorTorque = torque / 2;
    jointDef.enableMotor = true;
    jointDef.hertz = hertz;
    jointDef.dampingRatio = dampingRatio;
    jointDef.lowerTranslation = -0.25f * scale;
    jointDef.upperTranslation = 0.25f * scale;
    jointDef.enableLimit = true;
    m_frontAxleId = b2CreateWheelJoint(worldId, &jointDef);

    b2RevoluteJointDef rjointDef = b2DefaultRevoluteJointDef();

    pivot = b2Body_GetPosition(m_chassisId);
    rjointDef.bodyIdA = m_bodyId;
    rjointDef.bodyIdB = m_chassisId;
    rjointDef.collideConnected = true;
    rjointDef.dampingRatio = dampingRatio;
    rjointDef.enableSpring = true;
    rjointDef.hertz = hertz;
    rjointDef.localAnchorA = b2Body_GetLocalPoint(rjointDef.bodyIdA, pivot);
    rjointDef.localAnchorB = b2Body_GetLocalPoint(rjointDef.bodyIdB, pivot);
    rjointDef.enableLimit = true;
    m_carbodyId = b2CreateRevoluteJoint(worldId, &rjointDef);

    pivot = b2Body_GetPosition(m_bodyId);
    rjointDef.bodyIdA = m_headId;
    rjointDef.bodyIdB = m_bodyId;
    rjointDef.collideConnected = true;
    rjointDef.dampingRatio = dampingRatio;
    rjointDef.enableSpring = true;
    rjointDef.hertz = hertz;
    rjointDef.localAnchorA = b2Body_GetLocalPoint(rjointDef.bodyIdA, pivot);
    rjointDef.localAnchorB = b2Body_GetLocalPoint(rjointDef.bodyIdB, pivot);
    rjointDef.enableLimit = true;
    m_bodyheadId = b2CreateRevoluteJoint(worldId, &rjointDef);
    m_isSpawned = true;
}

void Car::Despawn() {
    assert(m_isSpawned == true);

    b2DestroyJoint(m_rearAxleId);
    b2DestroyJoint(m_frontAxleId);
    b2DestroyJoint(m_carbodyId);
    b2DestroyJoint(m_bodyheadId);
    b2DestroyBody(m_rearWheelId);
    b2DestroyBody(m_frontWheelId);
    b2DestroyBody(m_chassisId);
    b2DestroyBody(m_bodyId);
    b2DestroyBody(m_headId);

    m_chassisId = {};
    m_rearWheelId = {};
    m_frontWheelId = {};
    m_bodyId = {};
    m_headId = {};
    m_rearAxleId = {};
    m_frontAxleId = {};
    m_carbodyId = {};
    m_bodyheadId = {};

    m_isSpawned = false;
}

void Car::SetSpeed(float speed) {
    b2WheelJoint_SetMotorSpeed(m_rearAxleId, speed);
    b2WheelJoint_SetMotorSpeed(m_frontAxleId, speed);
    b2Joint_WakeBodies(m_rearAxleId);
}

void Car::SetTorque(float torque) {
    b2WheelJoint_SetMaxMotorTorque(m_rearAxleId, torque);
    b2WheelJoint_SetMaxMotorTorque(m_frontAxleId, torque);
}

void Car::SetHertz(float hertz) {
    b2WheelJoint_SetSpringHertz(m_rearAxleId, hertz);
    b2WheelJoint_SetSpringHertz(m_frontAxleId, hertz);
}

void Car::SetDampingRadio(float dampingRatio) {
    b2WheelJoint_SetSpringDampingRatio(m_rearAxleId, dampingRatio);
    b2WheelJoint_SetSpringDampingRatio(m_frontAxleId, dampingRatio);
}

void Car::Draw(sf::RenderWindow& window) {
    b2Vec2 reer_position = b2Body_GetPosition(m_rearWheelId);
    b2Vec2 front_position = b2Body_GetPosition(m_frontWheelId);
    b2Vec2 car_body = b2Body_GetPosition(m_chassisId);
    b2Vec2 body = b2Body_GetPosition(m_bodyId);
    b2Vec2 head = b2Body_GetPosition(m_headId);

    float scale = 1.7f;
    float SCALE = 25.0f;

    sf::RectangleShape Body(sf::Vector2f(0.6f * scale * SCALE, 1.6f * scale * SCALE));
    Body.setFillColor(sf::Color::Blue);
    Body.setOrigin(0.3f * scale * SCALE, 0.4f * scale * SCALE);
    Body.setRotation(-b2Rot_GetAngle(b2Body_GetRotation(m_bodyId)) * 180 / acos(-1));
    Body.setPosition((body.x - reer_position.x + 5) * SCALE, 600.f - (body.y) * SCALE);
    Body.setOutlineThickness(5);
    Body.setOutlineColor(sf::Color::Black);
    window.draw(Body);

    sf::Sprite head_sprite;
    Set::set_image(head_sprite, {(5 + head.x - reer_position.x) * SCALE - 15, 600.0f - head.y * SCALE - 10});
    head_sprite.setTexture(head_texture_);
    head_sprite.setOrigin(0.6 * scale * SCALE, 0.6 * scale * SCALE);
    head_sprite.setScale(0.7f, 0.7f);
    window.draw(head_sprite);

    sf::Sprite wheel1_sprite;
    Set::set_image(wheel1_sprite, {5 * SCALE - 12, 600.0f - (reer_position.y) * SCALE});
    wheel1_sprite.setTexture(wheel_texture_);
    wheel1_sprite.setOrigin(44.5f, 44.5f);
    wheel1_sprite.setScale(0.6f, 0.6f);
    wheel1_sprite.setRotation(-b2Rot_GetAngle(b2Body_GetRotation(m_rearWheelId)) * 180 / acos(-1));
    window.draw(wheel1_sprite);

    sf::Sprite wheel2_sprite;
    Set::set_image(wheel2_sprite, {(5 + front_position.x - reer_position.x) * SCALE - 12, 600.0f - front_position.y * SCALE});
    wheel2_sprite.setTexture(wheel_texture_);
    wheel2_sprite.setOrigin(44.5f, 44.5f);
    wheel2_sprite.setScale(0.6f, 0.6f);
    wheel2_sprite.setRotation(-b2Rot_GetAngle(b2Body_GetRotation(m_frontWheelId)) * 180 / acos(-1));
    window.draw(wheel2_sprite);

    sf::Sprite car_sprite;
    Set::set_image(car_sprite, {(car_body.x - reer_position.x + 5) * SCALE - 20, 600.f - (car_body.y) * SCALE - 20});
    car_sprite.setTexture(car_texture_);
    car_sprite.setRotation(-b2Rot_GetAngle(b2Body_GetRotation(m_chassisId)) * 180 / acos(-1));
    car_sprite.setOrigin(7.f / 3 * scale * SCALE, 1.0f * scale * SCALE);
    window.draw(car_sprite);

    sf::Text meters;
    Set::set_text(meters, int_to_string(static_cast<int>(reer_position.x) - 5 + 1), 30, sf::Color::White, 700, 500, 5);
    meters.setFont(hud_font_);
    window.draw(meters);
}
