# Ten du an
cmake_minimum_required(VERSION 3.10)
project(SFML_Box2D_Project)

# Chon chuan C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(RUN main)

# Them thu vien SFML (duoc cai qua Homebrew)
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Them thu vien Box2D (tu thu muc local)
add_subdirectory(box2d)

# Them tep ma nguon chinh
add_executable(${RUN}
    src/${RUN}.cpp
    src/ui/Application.cpp
    src/ui/Button.cpp
    src/ui/Window.cpp
    src/ui/set.cpp
    src/game/Ground.cpp
    src/game/Car.cpp
    src/game/Wheel.cpp
)

# Lien ket cac thu vien can thiet
target_link_libraries(${RUN}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    box2d
)

# Them include directory cho Box2D
target_include_directories(${RUN} PRIVATE box2d/include)
