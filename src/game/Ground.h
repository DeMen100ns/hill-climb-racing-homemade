#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include <vector>

class Ground {
private:
    const float SCALE = 25.f;

    float fade(float t);
    float lerp(float a, float b, float t);
    float grad(int hash, float x);
    float perlin1D(float x);

    std::vector<float> height;
    std::vector<int> type;
    int w;
    sf::Color color1, color2;
    float perlin_value;

public:
    Ground();
    Ground(b2WorldId worldId, int w, sf::Color color1, sf::Color color2, float perlin_value);
    Ground(const Ground& other);
    Ground& operator=(const Ground& other);

    void show(sf::RenderWindow& window, int position);
    float geth(int i);
    int get_typeh(int i);
    void reset_typeh(int i);
};
