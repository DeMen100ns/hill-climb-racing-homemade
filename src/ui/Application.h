#pragma once

#include <memory>
#include <string>

class Window;

class Application {
private:
    static std::unique_ptr<Application> instance;
    int last_ = -1;
    int state_ = 0;
    float fuel_ = 100.0f;

    Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

public:
    static Application& getInstance();

    std::string int_to_string(int val);
    Window* setup_window(int state);
    void run();
};
