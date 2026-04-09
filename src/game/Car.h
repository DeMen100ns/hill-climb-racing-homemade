#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Car
{
public:
    Car();

    void Spawn(b2WorldId worldId, b2Vec2 position, float scale, float hertz, float dampingRatio, float torque);
    void Despawn();

    void SetSpeed(float speed);
    void SetTorque(float torque);
    void SetHertz(float hertz);
    void SetDampingRadio(float dampingRatio);
    void Draw(sf::RenderWindow& window);

    b2BodyId m_chassisId;
    b2BodyId m_rearWheelId;
    b2BodyId m_frontWheelId;
    b2BodyId m_bodyId;
    b2BodyId m_headId;
    b2JointId m_rearAxleId;
    b2JointId m_frontAxleId;
    b2JointId m_carbodyId;
    b2JointId m_bodyheadId;
    bool m_isSpawned;

private:
    sf::Font hud_font_;
    sf::Texture head_texture_;
    sf::Texture wheel_texture_;
    sf::Texture car_texture_;
};
