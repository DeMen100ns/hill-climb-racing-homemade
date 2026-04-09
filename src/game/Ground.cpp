#include "Ground.h"

#include <cassert>
#include <chrono>
#include <random>
#include <vector>

#include "../ui/set.h"

using namespace std;

namespace {
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long randint(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

sf::Texture texture_obj;
sf::Sprite coin, fuel;
}  // namespace

Ground::Ground() = default;

float Ground::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float Ground::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float Ground::grad(int hash, float x) {
    int h = hash & 15;
    float g = 1 + (h & 7);
    return ((h & 8) ? -g : g) * x;
}

float Ground::perlin1D(float x) {
    int xi = static_cast<int>(floor(x)) & 255;
    float xf = x - floor(x);
    float u = fade(xf);

    vector<int> perm = {151, 160, 137, 91,  90,  15, 131, 13, 201, 95,  96,  53, 194, 233, 7,   225,
                        140, 36,  103, 30,  69,  142, 8,   99, 37,  240, 21,  10, 23,  190, 6,   148,
                        247, 120, 234, 75,  0,   26,  197, 62, 94,  252, 219, 203, 117, 35,  11,  32,
                        57,  177, 33,  88,  237, 149, 56,  87, 174, 20,  125, 136, 171, 168, 68,  175,
                        74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158, 231, 83,  111, 229, 122,
                        60,  211, 133, 230, 220, 105, 92,  41, 55,  46,  245, 40,  244, 102, 143, 54,
                        65,  25,  63,  161, 1,   216, 80,  73, 209, 76,  132, 187, 208, 89,  18,  169,
                        200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3,   64,
                        52,  217, 226, 250, 124, 123, 5,   202, 38,  147, 118, 126, 255, 82,  85,  212,
                        207, 206, 59,  227, 47,  16,  58,  17, 182, 189, 28,  42,  223, 183, 170, 213,
                        119, 248, 152, 2,   44,  154, 163, 70, 221, 153, 101, 155, 167, 43,  172, 9,
                        129, 22,  39,  253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104,
                        218, 246, 97,  228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241,
                        81,  51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157,
                        184, 84,  204, 176, 115, 121, 50,  45, 127, 4,   150, 254, 138, 236, 205, 93,
                        222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156, 180};

    for (int i = 0; i < 256; ++i) perm.push_back(perm[i]);
    int a = perm[xi];
    int b = perm[xi + 1];

    return lerp(grad(a, xf), grad(b, xf - 1), u);
}

Ground::Ground(b2WorldId worldId, int w, sf::Color color1, sf::Color color2, float perlin_value)
    : w(w), color1(color1), color2(color2), perlin_value(perlin_value) {
    const string PATH = "src/";

    texture_obj.loadFromFile(PATH + "image/object.png");
    coin.setTexture(texture_obj);
    Set::set_image(coin, {100.f, 100.f}, {0.3f, 0.3f}, {10, 370, 130, 130});

    fuel.setTexture(texture_obj);
    Set::set_image(fuel, {100.f, 100.f}, {0.3f, 0.3f}, {200, 550, 130, 130});

    assert(w > 400);
    height.resize(w);
    type.resize(w, 0);
    for (int x = 400; x < w; ++x) {
        height[x] = (perlin1D((x - 400) * perlin_value) * 50 + 200) / SCALE;
        if (height[x] < 1e-9) height[x] = 1e-6;
        if (height[x] > 580) height[x] = 580;
        assert(height[x] > 0);
    }
    for (int x = 1000; x < w; x += 100) {
        int r = randint(0, 99);
        if (r < 30) {
            type[x] = 1;
        } else if (r >= 90) {
            type[x] = 2;
        }
    }
    for (int x = 200; x < 400; ++x) height[x] = height[400];
    for (int x = 199; x >= 0; --x) height[x] = height[x + 1] + 0.01f;

    for (int x = 0; x < w; ++x) {
        b2BodyDef groundBodyDef = b2DefaultBodyDef();
        groundBodyDef.position = (b2Vec2){float(x) / SCALE, 0.0f};
        b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
        b2Polygon groundBox = b2MakeBox(1.0f / SCALE, height[x]);
        b2ShapeDef groundShapeDef = b2DefaultShapeDef();
        b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
    }
}

Ground::Ground(const Ground& other) {
    height = other.height;
    w = other.w;
    color1 = other.color1;
    color2 = other.color2;
    perlin_value = other.perlin_value;
    type = other.type;
}

Ground& Ground::operator=(const Ground& other) {
    if (this != &other) {
        height = other.height;
        w = other.w;
        color1 = other.color1;
        color2 = other.color2;
        perlin_value = other.perlin_value;
        type = other.type;
    }
    return *this;
}

void Ground::show(sf::RenderWindow& window, int position) {
    for (int i = position; i < (position + 800); ++i) {
        if (i < 0) continue;
        if (i >= w) continue;

        sf::RectangleShape groundShape;
        groundShape.setSize(sf::Vector2f(1.0f, height[i] * SCALE));
        groundShape.setFillColor(color1);
        groundShape.setPosition(i - position, 600.0f - height[i] * SCALE);
        window.draw(groundShape);

        sf::RectangleShape groundShape2;
        groundShape2.setSize(sf::Vector2f(1.0f, 5.0f));
        groundShape2.setFillColor(color2);
        groundShape2.setPosition(i - position, 600.0f - height[i] * SCALE - 5.0f);
        window.draw(groundShape2);

        if (type[i] == 1) {
            coin.setPosition({float(i - position), 600.0f - height[i] * SCALE - 50.0f});
            window.draw(coin);
        }
        if (type[i] == 2) {
            fuel.setPosition({float(i - position), 600.0f - height[i] * SCALE - 50.0f});
            window.draw(fuel);
        }
    }
}

float Ground::geth(int i) {
    if (i >= w) return 0;
    return height[i];
}

int Ground::get_typeh(int i) {
    if (i >= w) return 0;
    return type[i];
}

void Ground::reset_typeh(int i) {
    if (i < w) type[i] = 0;
}
