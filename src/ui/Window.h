#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Button.h"

class Window {
protected:
    std::map<std::string, std::pair<sf::Font, sf::Text>> vtext;
    std::map<std::string, std::pair<sf::Texture, sf::Sprite>> vsprite;
    std::map<std::string, Button> vbutton;
    std::vector<std::string> order;

public:
    Window(std::map<std::string, std::pair<sf::Font, sf::Text>> vtext,
           std::map<std::string, std::pair<sf::Texture, sf::Sprite>> vsprite,
           std::map<std::string, Button> vbutton, std::vector<std::string> order);
    virtual ~Window() = default;

    virtual void show(sf::RenderWindow& window);
    virtual int triggered(sf::Event& event);
};

class BeginningWindow : public Window {
public:
    BeginningWindow(std::map<std::string, std::pair<sf::Font, sf::Text>> vtext,
                    std::map<std::string, std::pair<sf::Texture, sf::Sprite>> vsprite,
                    std::map<std::string, Button> vbutton, std::vector<std::string> order);

    void show(sf::RenderWindow& window) override;
    int triggered(sf::Event& event) override;
};

class StorageWindow : public Window {
private:
    std::map<std::string, sf::RectangleShape> vrectangle;

public:
    StorageWindow(std::map<std::string, std::pair<sf::Font, sf::Text>> vtext,
                  std::map<std::string, std::pair<sf::Texture, sf::Sprite>> vsprite,
                  std::map<std::string, Button> vbutton, std::map<std::string, sf::RectangleShape> vrectangle,
                  std::vector<std::string> order);

    void show(sf::RenderWindow& window) override;
    int triggered(sf::Event& event) override;
};

class LevelWindow : public Window {
public:
    LevelWindow(std::map<std::string, std::pair<sf::Font, sf::Text>> vtext,
                std::map<std::string, std::pair<sf::Texture, sf::Sprite>> vsprite,
                std::map<std::string, Button> vbutton, std::vector<std::string> order);

    void show(sf::RenderWindow& window) override;
    int triggered(sf::Event& event) override;
};

class MapWindow : public Window {
private:
    std::map<std::string, sf::RectangleShape> vrectangle;

public:
    MapWindow(std::map<std::string, std::pair<sf::Font, sf::Text>> vtext,
              std::map<std::string, std::pair<sf::Texture, sf::Sprite>> vsprite,
              std::map<std::string, Button> vbutton, std::map<std::string, sf::RectangleShape> vrectangle,
              std::vector<std::string> order);

    void show(sf::RenderWindow& window) override;
    int triggered(sf::Event& event) override;
};

class EndingWindow : public Window {
private:
    std::map<std::string, sf::RectangleShape> vrectangle;

public:
    EndingWindow(std::map<std::string, std::pair<sf::Font, sf::Text>> vtext,
                 std::map<std::string, std::pair<sf::Texture, sf::Sprite>> vsprite,
                 std::map<std::string, Button> vbutton, std::map<std::string, sf::RectangleShape> vrectangle,
                 std::vector<std::string> order);

    void show(sf::RenderWindow& window) override;
    int triggered(sf::Event& event) override;
};
