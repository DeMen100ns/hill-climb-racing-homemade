# Hill Climb Racing Homemade

A C++ remake of the popular mobile game "Hill Climb Racing" by Fingersoft, built using SFML for graphics and Box2D for physics. This project is a fun way to practice C++ game development and learn how to integrate third-party libraries.

## What It Is

This project is a simple 2D hill-climbing driving game with:

- a main menu
- vehicle upgrades
- map selection
- fuel pickups
- coin collection
- highscores

## Tech Stack

- C++
- SFML 2.6
- Box2D
- CMake

## Project Structure

```text
.
├── CMakeLists.txt
├── box2d/
├── build/
├── src/
│   ├── main.cpp
│   ├── data/
│   ├── font/
│   ├── game/
│   ├── image/
│   └── ui/
└── README.md
```

## Requirements

You need:

- CMake
- a C++17 compiler
- SFML 2.6 installed on your machine

On macOS with Homebrew, SFML is typically installed with:

```bash
brew install sfml
```

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Run

After building:

```bash
./build/main
```

## Notes

- The game currently expects assets and data to be available under `src/`.
- Save data such as coins, levels, and highscores are stored in `src/data/`.
- `box2d/` is vendored into the project and built locally by CMake.

## Main Source Areas

- `src/main.cpp`: program entry point
- `src/ui/`: application flow, menus, window logic, UI helpers
- `src/game/`: car, terrain, and gameplay objects
- `src/data/`: saved data and music
- `src/image/`: textures and images
- `src/font/`: font assets

## Build Again Later

If you already configured once, rebuilding is just:

```bash
cmake --build build
```
