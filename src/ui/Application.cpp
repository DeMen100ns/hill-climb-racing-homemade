#include "Application.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../game/Ground.h"
#include "../game/Wheel.h"
#include "../game/Car.h"
#include "Button.h"
#include "Window.h"
#include "set.h"

using namespace std;

namespace {
const string PATH = "src/";

const int FPS = 60;
}  // namespace

Application::Application() = default;

Application& Application::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<Application>(new Application());
    }
    return *instance;
}

string Application::int_to_string(int val) {
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

Window* Application::setup_window(int state) {
    if (state == 0) {  // beginning
        sf::Font font;
        font.loadFromFile(PATH + "font/XPLOR Bold-Regular.otf");
        map<string, pair<sf::Font, sf::Text>> vtext;
        map<string, pair<sf::Texture, sf::Sprite>> vsprite;
        map<string, Button> vbutton;
        vector<string> order;

        sf::Texture background_texture;
        background_texture.loadFromFile(PATH + "image/background.jpg");
        sf::Sprite background_sprite;
        Set::set_image(background_sprite, {0, 0}, {1.f, 1.f}, {500, 200, 800, 600});
        vsprite["BACKGROUND"] = {background_texture, background_sprite};
        order.push_back("BACKGROUND");

        sf::Texture logo_texture;
        logo_texture.loadFromFile(PATH + "image/logo.png");
        sf::Sprite logo_sprite;
        Set::set_image(logo_sprite, {300, 25}, {0.52f, 0.52f});
        vsprite["LOGO"] = {logo_texture, logo_sprite};
        order.push_back("LOGO");

        sf::Texture button1_texture;
        button1_texture.loadFromFile(PATH + "image/green_button.png");
        sf::Sprite button1_sprite;
        Set::set_image(button1_sprite, {300, 180});

        sf::Text button1_text;
        Set::set_text(button1_text, "NEW GAME", 30, sf::Color::White, 325, 190);

        Button button1(font, button1_text, button1_texture, button1_sprite);
        vbutton["BUTTON1"] = button1;
        order.push_back("BUTTON1");

        sf::Texture button2_texture;
        button2_texture.loadFromFile(PATH + "image/blue_button.png");
        sf::Sprite button2_sprite;
        Set::set_image(button2_sprite, {300, 250});

        sf::Text button2_text;
        Set::set_text(button2_text, "VEHICLE", 30, sf::Color::White, 345, 260);

        Button button2(font, button2_text, button2_texture, button2_sprite);
        vbutton["BUTTON2"] = button2;
        order.push_back("BUTTON2");

        sf::Texture button3_texture;
        button3_texture.loadFromFile(PATH + "image/red_button.png");
        sf::Sprite button3_sprite;
        Set::set_image(button3_sprite, {300, 320});

        sf::Text button3_text;
        Set::set_text(button3_text, "QUIT", 30, sf::Color::White, 365, 330);

        Button button3(font, button3_text, button3_texture, button3_sprite);
        vbutton["BUTTON3"] = button3;
        order.push_back("BUTTON3");

        return (new BeginningWindow(vtext, vsprite, vbutton, order));
    } else if (state == 1) {  // vehicle
        sf::Font font, font2;
        font.loadFromFile(PATH + "font/Changa-Bold.ttf");
        font2.loadFromFile(PATH + "font/Teko-Regular.ttf");
        map<string, pair<sf::Font, sf::Text>> vtext;
        map<string, pair<sf::Texture, sf::Sprite>> vsprite;
        map<string, Button> vbutton;
        map<string, sf::RectangleShape> vrectangle;
        vector<string> order;

        ifstream fi_coin((PATH + "data/coin.txt").c_str());
        ifstream fi((PATH + "data/level.txt").c_str());

        int money, la, lb, lc, ld;

        fi_coin >> money;
        fi >> la >> lb >> lc >> ld;

        fi.close();
        fi_coin.close();

        sf::Texture garage_texture;
        garage_texture.loadFromFile(PATH + "image/garage.png");
        sf::Sprite garage_sprite;
        Set::set_image(garage_sprite, {0, 0}, {600.f / 500, 600.f / 500}, {150, 0, 682.666667f, 500});
        vsprite["GARAGE"] = {garage_texture, garage_sprite};
        order.push_back("GARAGE");

        sf::Text tune_text;
        Set::set_text(tune_text, "TUNE", 75, sf::Color::White, 330, 30);
        vtext["TUNE"] = {font2, tune_text};
        order.push_back("TUNE");

        {
            sf::RectangleShape rec1;
            Set::set_rectangle(rec1, {115, 120}, sf::Color(240, 146, 64), {100, 160}, 5, sf::Color(255, 246, 207));
            vrectangle["REC1"] = rec1;
            order.push_back("REC1");

            sf::Text money_1;
            Set::set_text(money_1, int_to_string(4000 * la), 20, sf::Color::White, 130, 289, 5);
            money_1.setStyle(sf::Text::Regular);

            sf::Texture money_texture1;
            money_texture1.loadFromFile(PATH + "image/money_button_2.png");
            sf::Sprite money_sprite1;
            Set::set_image(money_sprite1, {91, 285}, {0.51f, 0.51f});

            Button money_button1(font2, money_1, money_texture1, money_sprite1);
            vbutton["MONEY_BUTTON1"] = money_button1;
            order.push_back("MONEY_BUTTON1");

            sf::Texture engine_texture;
            engine_texture.loadFromFile(PATH + "image/engine.png");
            sf::Sprite engine_sprite;
            Set::set_image(engine_sprite, {95, 150}, {0.25f, 0.25f});
            vsprite["ENGINE"] = {engine_texture, engine_sprite};
            order.push_back("ENGINE");

            sf::Text engine_level;
            Set::set_text(engine_level, int_to_string(la) + "/10", 20, sf::Color::White, 185, 254, 2);
            engine_level.setStyle(sf::Text::Regular);
            vtext["ENGINE_LEVEL"] = {font2, engine_level};
            order.push_back("ENGINE_LEVEL");
        }

        {
            sf::RectangleShape rec2;
            Set::set_rectangle(rec2, {115, 120}, sf::Color(240, 146, 64), {250, 160}, 5, sf::Color(255, 246, 207));
            vrectangle["REC2"] = rec2;
            order.push_back("REC2");

            sf::Text money_2;
            Set::set_text(money_2, int_to_string(4000 * lb), 20, sf::Color::White, 280, 289, 5);
            money_2.setStyle(sf::Text::Regular);

            sf::Texture money_texture2;
            money_texture2.loadFromFile(PATH + "image/money_button_2.png");
            sf::Sprite money_sprite2;
            Set::set_image(money_sprite2, {241, 285}, {0.51f, 0.51f});

            Button money_button2(font2, money_2, money_texture2, money_sprite2);
            vbutton["MONEY_BUTTON2"] = money_button2;
            order.push_back("MONEY_BUTTON2");

            sf::Texture suspension_texture;
            suspension_texture.loadFromFile(PATH + "image/suspension.png");
            sf::Sprite suspension_sprite;
            Set::set_image(suspension_sprite, {245, 155}, {0.25f, 0.25f});
            vsprite["SUSPENSION"] = {suspension_texture, suspension_sprite};
            order.push_back("SUSPENSION");

            sf::Text suspension_level;
            Set::set_text(suspension_level, int_to_string(lb) + "/10", 20, sf::Color::White, 335, 254, 2);
            suspension_level.setStyle(sf::Text::Regular);
            vtext["SUSPENSION_LEVEL"] = {font2, suspension_level};
            order.push_back("SUSPENSION_LEVEL");
        }

        {
            sf::RectangleShape rec3;
            Set::set_rectangle(rec3, {115, 120}, sf::Color(240, 146, 64), {400, 160}, 5, sf::Color(255, 246, 207));
            vrectangle["REC3"] = rec3;
            order.push_back("REC3");

            sf::Text money_3;
            Set::set_text(money_3, int_to_string(lc * 4000), 20, sf::Color::White, 430, 289, 5);
            money_3.setStyle(sf::Text::Regular);

            sf::Texture money_texture3;
            money_texture3.loadFromFile(PATH + "image/money_button_2.png");
            sf::Sprite money_sprite3;
            Set::set_image(money_sprite3, {391, 285}, {0.51f, 0.51f});

            Button money_button3(font2, money_3, money_texture3, money_sprite3);
            vbutton["MONEY_BUTTON3"] = money_button3;
            order.push_back("MONEY_BUTTON3");

            sf::Texture wheel_texture;
            wheel_texture.loadFromFile(PATH + "image/wheel.png");
            sf::Sprite wheel_sprite;
            Set::set_image(wheel_sprite, {395, 155}, {0.25f, 0.25f});
            vsprite["WHEEL"] = {wheel_texture, wheel_sprite};
            order.push_back("WHEEL");

            sf::Text wheel_level;
            Set::set_text(wheel_level, int_to_string(lc) + "/10", 20, sf::Color::White, 485, 254, 2);
            wheel_level.setStyle(sf::Text::Regular);
            vtext["WHEEL_LEVEL"] = {font2, wheel_level};
            order.push_back("WHEEL_LEVEL");
        }

        {
            sf::RectangleShape rec4;
            Set::set_rectangle(rec4, {115, 120}, sf::Color(240, 146, 64), {550, 160}, 5, sf::Color(255, 246, 207));
            vrectangle["REC4"] = rec4;
            order.push_back("REC4");

            sf::Text money_4;
            Set::set_text(money_4, int_to_string(ld * 4000), 20, sf::Color::White, 580, 289, 5);
            money_4.setStyle(sf::Text::Regular);

            sf::Texture money_texture4;
            money_texture4.loadFromFile(PATH + "image/money_button_2.png");
            sf::Sprite money_sprite4;
            Set::set_image(money_sprite4, {541, 285}, {0.51f, 0.51f});

            Button money_button4(font2, money_4, money_texture4, money_sprite4);
            vbutton["MONEY_BUTTON4"] = money_button4;
            order.push_back("MONEY_BUTTON4");

            sf::Texture fwd_texture;
            fwd_texture.loadFromFile(PATH + "image/4wd.png");
            sf::Sprite fwd_sprite;
            Set::set_image(fwd_sprite, {545, 155}, {0.25f, 0.25f});
            vsprite["4WD"] = {fwd_texture, fwd_sprite};
            order.push_back("4WD");

            sf::Text fwd_level;
            Set::set_text(fwd_level, int_to_string(ld) + "/10", 20, sf::Color::White, 635, 254, 2);
            fwd_level.setStyle(sf::Text::Regular);
            vtext["4WD_LEVEL"] = {font2, fwd_level};
            order.push_back("4WD_LEVEL");
        }

        {
            sf::Text back_text;
            Set::set_text(back_text, "BACK", 30, sf::Color::White, 20, 60);

            sf::Texture back_texture;
            back_texture.loadFromFile(PATH + "image/green_button.png");
            sf::Sprite back_sprite;
            Set::set_image(back_sprite, {5, 50}, {0.55, 1});

            Button back_button(font, back_text, back_texture, back_sprite);
            vbutton["BACK_BUTTON"] = back_button;
            order.push_back("BACK_BUTTON");

            sf::Texture coins_texture;
            coins_texture.loadFromFile(PATH + "image/object.png");
            sf::Sprite coins_sprite;
            Set::set_image(coins_sprite, {10, 10}, {0.2, 0.2}, {10, 10, 130, 130});
            vsprite["COINS_IMAGE"] = {coins_texture, coins_sprite};
            order.push_back("COINS_IMAGE");

            sf::Text coins_text;
            Set::set_text(coins_text, int_to_string(money), 25, sf::Color::White, 42, 8, 5);
            vtext["COINS_TEXT"] = {font2, coins_text};
            order.push_back("COINS_TEXT");

            sf::Texture car_visual_texture;
            car_visual_texture.loadFromFile(PATH + "image/car.png");
            sf::Sprite car_visual_sprite;
            Set::set_image(car_visual_sprite, {286.5, 400});
            vsprite["CAR_VISUAL"] = {car_visual_texture, car_visual_sprite};
            order.push_back("CAR_VISUAL");

            sf::Texture wheel1_visual_texture;
            wheel1_visual_texture.loadFromFile(PATH + "image/wheel_car.png");
            sf::Sprite wheel1_visual_sprite;
            Set::set_image(wheel1_visual_sprite, {308.5, 495}, {0.5, 0.5});
            vsprite["WHEEL1_VISUAL"] = {wheel1_visual_texture, wheel1_visual_sprite};
            order.push_back("WHEEL1_VISUAL");

            sf::Texture wheel2_visual_texture;
            wheel2_visual_texture.loadFromFile(PATH + "image/wheel_car.png");
            sf::Sprite wheel2_visual_sprite;
            Set::set_image(wheel2_visual_sprite, {433.5, 495}, {0.5, 0.5});
            vsprite["WHEEL2_VISUAL"] = {wheel2_visual_texture, wheel2_visual_sprite};
            order.push_back("WHEEL2_VISUAL");
        }
        return new StorageWindow(vtext, vsprite, vbutton, vrectangle, order);
    } else if (state == 2) {  // map
        sf::Font font, font2;
        font.loadFromFile(PATH + "font/Changa-Bold.ttf");
        font2.loadFromFile(PATH + "font/Teko-Regular.ttf");
        map<string, pair<sf::Font, sf::Text>> vtext;
        map<string, pair<sf::Texture, sf::Sprite>> vsprite;
        map<string, Button> vbutton;
        map<string, sf::RectangleShape> vrectangle;
        vector<string> order;

        sf::Texture background_texture;
        background_texture.loadFromFile(PATH + "image/background.jpg");
        sf::Sprite background_sprite;
        Set::set_image(background_sprite, {0, 0}, {1.f, 1.f}, {500, 200, 800, 600});
        vsprite["BACKGROUND"] = {background_texture, background_sprite};
        order.push_back("BACKGROUND");

        sf::Text map_text;
        Set::set_text(map_text, "CHOOSE MAP", 60, sf::Color::White, 220, 30);
        vtext["MAP_TEXT"] = {font, map_text};
        order.push_back("MAP_TEXT");

        sf::Texture map1_texture;
        map1_texture.loadFromFile(PATH + "image/level_earth.png");
        sf::Sprite map1_sprite;
        Set::set_image(map1_sprite, {100, 200}, {0.12f, 0.12f});

        sf::Text map1_text;
        Set::set_text(map1_text, "EARTH", 30, sf::Color::White, 120, 160);

        Button map1_button(font, map1_text, map1_texture, map1_sprite);
        vbutton["MAP1_BUTTON"] = map1_button;
        order.push_back("MAP1_BUTTON");

        sf::Texture map2_texture;
        map2_texture.loadFromFile(PATH + "image/level_red_earth.png");
        sf::Sprite map2_sprite;
        Set::set_image(map2_sprite, {300, 200}, {0.12f, 0.12f});

        sf::Text map2_text;
        Set::set_text(map2_text, "RED EARTH", 30, sf::Color::Red, 320, 160);

        Button map2_button(font, map2_text, map2_texture, map2_sprite);
        vbutton["MAP2_BUTTON"] = map2_button;
        order.push_back("MAP2_BUTTON");

        sf::Texture map3_texture;
        map3_texture.loadFromFile(PATH + "image/level_moon.png");
        sf::Sprite map3_sprite;
        Set::set_image(map3_sprite, {500, 200}, {0.12f, 0.12f});

        sf::Text map3_text;
        Set::set_text(map3_text, "MOON", 30, sf::Color(154, 148, 147), 520, 160);

        Button map3_button(font, map3_text, map3_texture, map3_sprite);
        vbutton["MAP3_BUTTON"] = map3_button;
        order.push_back("MAP3_BUTTON");

        sf::Text back_text;
        Set::set_text(back_text, "BACK", 30, sf::Color::White, 20, 60);

        sf::Texture back_texture;
        back_texture.loadFromFile(PATH + "image/green_button.png");
        sf::Sprite back_sprite;
        Set::set_image(back_sprite, {5, 50}, {0.55, 1});

        Button back_button(font, back_text, back_texture, back_sprite);
        vbutton["BACK_BUTTON"] = back_button;
        order.push_back("BACK_BUTTON");

        return new LevelWindow(vtext, vsprite, vbutton, order);
    } else if (state >= 3 && state <= 5) {  // gameplay
        sf::Font font, font2;
        font.loadFromFile(PATH + "font/Changa-Bold.ttf");
        font2.loadFromFile(PATH + "font/Teko-Regular.ttf");
        map<string, pair<sf::Font, sf::Text>> vtext;
        map<string, pair<sf::Texture, sf::Sprite>> vsprite;
        map<string, Button> vbutton;
        map<string, sf::RectangleShape> vrectangle;
        vector<string> order;

        sf::RectangleShape fuel1;
        Set::set_rectangle(fuel1, {100, 20}, sf::Color::Transparent, {40, 20}, 5, sf::Color::Black);
        vrectangle["FUEL1"] = fuel1;
        order.push_back("FUEL1");

        if (fuel_ > 0) {
            sf::RectangleShape fuel2;
            Set::set_rectangle(fuel2, {fuel_, 20}, sf::Color::Green, {40, 20}, 0, sf::Color::Black);
            vrectangle["FUEL2"] = fuel2;
            order.push_back("FUEL2");
        }

        sf::Texture fuel;
        fuel.loadFromFile(PATH + "image/object.png");
        sf::Sprite fuel_sprite;
        Set::set_image(fuel_sprite, {10, 20}, {0.15f, 0.15f}, {200, 550, 130, 130});
        vsprite["FUEL"] = {fuel, fuel_sprite};
        order.push_back("FUEL");

        return new MapWindow(vtext, vsprite, vbutton, vrectangle, order);
    } else if (state == 6) {
        sf::Font font, font2;
        font.loadFromFile(PATH + "font/Changa-Bold.ttf");
        font2.loadFromFile(PATH + "font/Teko-Regular.ttf");
        map<string, pair<sf::Font, sf::Text>> vtext;
        map<string, pair<sf::Texture, sf::Sprite>> vsprite;
        map<string, Button> vbutton;
        map<string, sf::RectangleShape> vrectangle;
        vector<string> order;

        sf::Text back_text;
        Set::set_text(back_text, "BACK", 30, sf::Color::White, 20, 60);

        sf::Texture back_texture;
        back_texture.loadFromFile(PATH + "image/green_button.png");
        sf::Sprite back_sprite;
        Set::set_image(back_sprite, {5, 50}, {0.55, 1});

        Button back_button(font, back_text, back_texture, back_sprite);
        vbutton["BACK_BUTTON"] = back_button;
        order.push_back("BACK_BUTTON");

        sf::RectangleShape Highscore;
        Set::set_rectangle(Highscore, {500, 500}, sf::Color(135, 206, 235), {150, 50}, 5, sf::Color(255, 246, 207));
        vrectangle["HIGHSCORE"] = Highscore;
        order.push_back("HIGHSCORE");

        sf::Text highscore_text;
        Set::set_text(highscore_text, "HIGH SCORE", 70, sf::Color::White, 210, 70);
        vtext["HIGHSCORE_TEXT"] = {font, highscore_text};
        order.push_back("HIGHSCORE_TEXT");

        ifstream fi;
        if (last_ == 3) fi.open((PATH + "data/highscore_earth.txt").c_str());
        if (last_ == 4) fi.open((PATH + "data/highscore_earth_hard.txt").c_str());
        if (last_ == 5) fi.open((PATH + "data/highscore_moon.txt").c_str());

        for (int i = 0, base = 150; i < 5; ++i, base += 60) {
            int val;
            fi >> val;

            sf::Text highscore_line;
            Set::set_text(highscore_line, int_to_string(i + 1) + ". " + int_to_string(val), 50, sf::Color::White, 210,
                          base);
            vtext["HIGHSCORE_TEXT" + int_to_string(i)] = {font, highscore_line};
            order.push_back("HIGHSCORE_TEXT" + int_to_string(i));
        }

        return (new EndingWindow(vtext, vsprite, vbutton, vrectangle, order));
    }

    return new Window({}, {}, {}, {});
}

void Application::run() {
    sf::Music music;
    music.openFromFile((PATH + "data/theme.mp3").c_str());

    sf::RenderWindow window(sf::VideoMode(800, 600), "Hill Climb Racing!!");
    window.setFramerateLimit(FPS);

    float timeStep = 1.0f / FPS;
    int subStepCount = 4;

    const float SCALE = 25.f;

    float scale = 1.7f;
    Car car;

    Ground ground;
    b2WorldDef worldDef, moonDef;
    b2WorldId worldId, moonId;

    sf::Texture texturesky3, texturesky4, texturesky5;
    sf::Sprite spritesky3, spritesky4, spritesky5;
    texturesky3.loadFromFile(PATH + "image/sky.png");
    texturesky4.loadFromFile(PATH + "image/redsky.jpg");
    texturesky5.loadFromFile(PATH + "image/moon.png");
    spritesky3.setTexture(texturesky3);
    spritesky4.setTexture(texturesky4);
    spritesky5.setTexture(texturesky5);

    int la, lb, lc, ld;

    music.play();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            Window* meow = setup_window(state_);

            int val = meow->triggered(event);
            delete meow;

            if (val >= 3 && val <= 5) {
                worldDef = b2DefaultWorldDef();
                worldDef.gravity = (b2Vec2){0.0f, -9.8f};
                worldId = b2CreateWorld(&worldDef);

                moonDef = b2DefaultWorldDef();
                moonDef.gravity = (b2Vec2){0.0f, -2.f};
                moonId = b2CreateWorld(&moonDef);

                if (val == 3) ground = Ground(worldId, 1000 * static_cast<int>(SCALE), sf::Color(88, 59, 37),
                                              sf::Color::Green, 0.001f);
                if (val == 4) ground = Ground(worldId, 1000 * static_cast<int>(SCALE), sf::Color(126, 46, 31),
                                              sf::Color(154, 205, 50), 0.0015f);
                if (val == 5) ground = Ground(moonId, 1000 * static_cast<int>(SCALE), sf::Color(120, 114, 113),
                                              sf::Color(201, 201, 201), 0.001f);

                ifstream fi((PATH + "data/level.txt").c_str());
                fi >> la >> lb >> lc >> ld;
                fi.close();

                car = Car();
                car.Spawn((val <= 4 ? worldId : moonId), b2Vec2({10.f, 15.f}), scale, 6.0f - lb * 0.1f,
                          0.7f + lb * 0.3f, 200.f + la * 7.5 + ld * 7.5);
                fuel_ = 100;
            }
            if (val != -1) {
                state_ = val;
            }

            if (state_ >= 3 && state_ <= 5) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Left) {
                        car.SetSpeed((10.f + (la * 1.5f)) * 3.14);
                    } else if (event.key.code == sf::Keyboard::Right) {
                        car.SetSpeed(-(10.f + (la * 1.5f)) * 3.14);
                    } else {
                        car.SetSpeed(0);
                    }
                } else {
                    car.SetSpeed(0);
                }
            }
        }

        if (state_ == -2) break;

        window.clear(sf::Color::Black);

        if (state_ >= 3 && state_ <= 5) {
            fuel_ -= 0.05f;
            if (state_ == 3) {
                window.draw(spritesky3);
            } else if (state_ == 4) {
                window.draw(spritesky4);
            } else if (state_ == 5) {
                window.draw(spritesky5);
            }

            if (state_ <= 4) {
                b2World_Step(worldId, timeStep, subStepCount);
            } else {
                b2World_Step(moonId, timeStep, subStepCount);
            }

            b2Vec2 reer_position = b2Body_GetPosition(car.m_rearWheelId);
            b2Vec2 front_position = b2Body_GetPosition(car.m_frontWheelId);
            b2Vec2 head = b2Body_GetPosition(car.m_headId);

            int pos = static_cast<int>(front_position.x * SCALE);
            for (int p = pos - 10; p <= pos + 10; ++p) {
                int item = ground.get_typeh(p);
                if (item > 0 && front_position.y - ground.geth(static_cast<int>(front_position.x * SCALE)) < 2) {
                    if (item == 1) {
                        ifstream fi((PATH + "data/coin.txt").c_str());
                        int money;
                        fi >> money;
                        fi.close();

                        money += 10;

                        ofstream fo((PATH + "data/coin.txt").c_str());
                        fo << money;
                        fo.close();
                    }
                    if (item == 2) {
                        fuel_ = 100;
                    }
                    ground.reset_typeh(p);
                }
            }

            ground.show(window, SCALE * (reer_position.x - 5));

            car.Draw(window);

            if (fuel_ <= 0 || reer_position.x - 5 + 1 > 1000 ||
                head.y - 0.6f * scale < ground.geth(static_cast<int>(head.x * SCALE))) {
                int rec = reer_position.x - 5 + 1;
                rec = min(rec, 1000);

                ifstream fi;
                if (state_ == 3) fi.open((PATH + "data/highscore_earth.txt").c_str());
                if (state_ == 4) fi.open((PATH + "data/highscore_earth_hard.txt").c_str());
                if (state_ == 5) fi.open((PATH + "data/highscore_moon.txt").c_str());

                vector<int> high_score(5);
                for (int& i : high_score) {
                    fi >> i;
                }

                fi.close();

                ofstream fo;
                if (state_ == 3) fo.open((PATH + "data/highscore_earth.txt").c_str());
                if (state_ == 4) fo.open((PATH + "data/highscore_earth_hard.txt").c_str());
                if (state_ == 5) fo.open((PATH + "data/highscore_moon.txt").c_str());

                high_score.push_back(rec);
                sort(high_score.begin(), high_score.end(), greater<int>());
                for (int i = 0; i < 5; ++i) fo << high_score[i] << endl;

                fo.close();
                last_ = state_;
                state_ = 6;
            }
        }

        if (state_ == 6) {
            window.draw(spritesky3);
        }

        Window* meow = setup_window(state_);
        meow->show(window);
        delete meow;

        window.display();
    }
}
