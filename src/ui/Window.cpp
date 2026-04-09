#include "Window.h"

#include <fstream>

using namespace std;

namespace {
const string PATH = "src/";
}

Window::Window(map<string, pair<sf::Font, sf::Text>> vtext, map<string, pair<sf::Texture, sf::Sprite>> vsprite,
               map<string, Button> vbutton, vector<string> order)
    : vtext(vtext), vsprite(vsprite), vbutton(vbutton), order(order) {}

void Window::show(sf::RenderWindow& window) {
    for (string key : order) {
        if (vsprite.find(key) != vsprite.end()) {
            auto& s = vsprite[key];
            (s.second).setTexture(s.first);
            window.draw(s.second);
        } else if (vtext.find(key) != vtext.end()) {
            auto t = vtext[key];
            (t.second).setFont(t.first);
            window.draw(t.second);
        } else if (vbutton.find(key) != vbutton.end()) {
            auto b = vbutton[key];
            b.show(window);
        }
    }
}

int Window::triggered(sf::Event& event) {
    (void)event;
    return -1;
}

BeginningWindow::BeginningWindow(map<string, pair<sf::Font, sf::Text>> vtext,
                                 map<string, pair<sf::Texture, sf::Sprite>> vsprite,
                                 map<string, Button> vbutton, vector<string> order)
    : Window(vtext, vsprite, vbutton, order) {}

void BeginningWindow::show(sf::RenderWindow& window) {
    Window::show(window);
}

int BeginningWindow::triggered(sf::Event& event) {
    if (vbutton["BUTTON1"].touch(event)) return 2;
    if (vbutton["BUTTON2"].touch(event)) return 1;
    if (vbutton["BUTTON3"].touch(event)) return -2;
    return -1;
}

StorageWindow::StorageWindow(map<string, pair<sf::Font, sf::Text>> vtext,
                             map<string, pair<sf::Texture, sf::Sprite>> vsprite, map<string, Button> vbutton,
                             map<string, sf::RectangleShape> vrectangle, vector<string> order)
    : Window(vtext, vsprite, vbutton, order), vrectangle(vrectangle) {}

void StorageWindow::show(sf::RenderWindow& window) {
    for (string key : order) {
        if (vsprite.find(key) != vsprite.end()) {
            auto& s = vsprite[key];
            (s.second).setTexture(s.first);
            window.draw(s.second);
        } else if (vtext.find(key) != vtext.end()) {
            auto t = vtext[key];
            (t.second).setFont(t.first);
            window.draw(t.second);
        } else if (vbutton.find(key) != vbutton.end()) {
            auto b = vbutton[key];
            b.show(window);
        } else if (vrectangle.find(key) != vrectangle.end()) {
            window.draw(vrectangle[key]);
        }
    }
}

int StorageWindow::triggered(sf::Event& event) {
    if (vbutton["BACK_BUTTON"].touch(event)) return 0;

    ifstream fi_coin((PATH + "data/coin.txt").c_str());
    ifstream fi((PATH + "data/level.txt").c_str());

    int money, la, lb, lc, ld;

    fi_coin >> money;
    fi >> la >> lb >> lc >> ld;

    fi.close();
    fi_coin.close();

    if (vbutton["MONEY_BUTTON1"].touch(event)) {
        if (la < 10 && money >= la * 4000) {
            money -= la * 4000;
            la++;
        }
    } else if (vbutton["MONEY_BUTTON2"].touch(event)) {
        if (lb < 10 && money >= lb * 4000) {
            money -= lb * 4000;
            lb++;
        }
    } else if (vbutton["MONEY_BUTTON3"].touch(event)) {
        if (lc < 10 && money >= lc * 4000) {
            money -= lc * 4000;
            lc++;
        }
    } else if (vbutton["MONEY_BUTTON4"].touch(event)) {
        if (ld < 10 && money >= ld * 4000) {
            money -= ld * 4000;
            ld++;
        }
    }

    ofstream fo_coin((PATH + "data/coin.txt").c_str());
    ofstream fo((PATH + "data/level.txt").c_str());

    fo_coin << money << endl;
    fo << la << " " << lb << " " << lc << " " << ld << endl;

    fo.close();
    fo_coin.close();

    return -1;
}

LevelWindow::LevelWindow(map<string, pair<sf::Font, sf::Text>> vtext,
                         map<string, pair<sf::Texture, sf::Sprite>> vsprite, map<string, Button> vbutton,
                         vector<string> order)
    : Window(vtext, vsprite, vbutton, order) {}

void LevelWindow::show(sf::RenderWindow& window) {
    Window::show(window);
}

int LevelWindow::triggered(sf::Event& event) {
    if (vbutton["BACK_BUTTON"].touch(event)) return 0;
    if (vbutton["MAP1_BUTTON"].touch(event)) return 3;
    if (vbutton["MAP2_BUTTON"].touch(event)) return 4;
    if (vbutton["MAP3_BUTTON"].touch(event)) return 5;
    return -1;
}

MapWindow::MapWindow(map<string, pair<sf::Font, sf::Text>> vtext,
                     map<string, pair<sf::Texture, sf::Sprite>> vsprite, map<string, Button> vbutton,
                     map<string, sf::RectangleShape> vrectangle, vector<string> order)
    : Window(vtext, vsprite, vbutton, order), vrectangle(vrectangle) {}

void MapWindow::show(sf::RenderWindow& window) {
    for (string key : order) {
        if (vsprite.find(key) != vsprite.end()) {
            auto& s = vsprite[key];
            (s.second).setTexture(s.first);
            window.draw(s.second);
        } else if (vtext.find(key) != vtext.end()) {
            auto t = vtext[key];
            (t.second).setFont(t.first);
            window.draw(t.second);
        } else if (vbutton.find(key) != vbutton.end()) {
            auto b = vbutton[key];
            b.show(window);
        } else if (vrectangle.find(key) != vrectangle.end()) {
            window.draw(vrectangle[key]);
        }
    }
}

int MapWindow::triggered(sf::Event& event) {
    (void)event;
    return -1;
}

EndingWindow::EndingWindow(map<string, pair<sf::Font, sf::Text>> vtext,
                           map<string, pair<sf::Texture, sf::Sprite>> vsprite, map<string, Button> vbutton,
                           map<string, sf::RectangleShape> vrectangle, vector<string> order)
    : Window(vtext, vsprite, vbutton, order), vrectangle(vrectangle) {}

void EndingWindow::show(sf::RenderWindow& window) {
    for (string key : order) {
        if (vsprite.find(key) != vsprite.end()) {
            auto& s = vsprite[key];
            (s.second).setTexture(s.first);
            window.draw(s.second);
        } else if (vtext.find(key) != vtext.end()) {
            auto t = vtext[key];
            (t.second).setFont(t.first);
            window.draw(t.second);
        } else if (vbutton.find(key) != vbutton.end()) {
            auto b = vbutton[key];
            b.show(window);
        } else if (vrectangle.find(key) != vrectangle.end()) {
            window.draw(vrectangle[key]);
        }
    }
}

int EndingWindow::triggered(sf::Event& event) {
    if (vbutton["BACK_BUTTON"].touch(event)) return 0;
    return -1;
}
