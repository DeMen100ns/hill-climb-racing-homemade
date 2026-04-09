#include <bits/stdc++.h>
#include "ui/Application.h"

using namespace std;

std::unique_ptr<Application> Application::instance = nullptr;

signed main() {
    Application& app = Application::getInstance();
    app.run();
}
