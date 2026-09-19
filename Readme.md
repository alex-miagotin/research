# Research

A personal engineering lab: small, self-contained experiments in **C++20**, **SDL2** game development, **WebAssembly**, and **system design**, plus idea backlogs for future projects in C++, Rust, Python and ML.

![C++20](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white)
![CMake](https://img.shields.io/badge/build-CMake%20%2B%20Ninja-064F8C?logo=cmake&logoColor=white)
![Conan](https://img.shields.io/badge/deps-Conan-6699CB?logo=conan&logoColor=white)
![SDL2](https://img.shields.io/badge/graphics-SDL2-1F2A44)
![WebAssembly](https://img.shields.io/badge/target-WebAssembly-654FF0?logo=webassembly&logoColor=white)

## Contents

- [About](#about)
- [Repository map](#repository-map)
- [Projects](#projects)
  - [Game engine](#game-engine--srcgame_engine)
  - [Game tutor](#game-tutor--srcgame_tutor)
  - [WebAssembly game](#webassembly-game--srcwasm)
  - [Instrument controller design](#instrument-controller-design--appsyntax_controller)
- [Tech stack](#tech-stack)
- [Getting started](#getting-started)
- [Repository layout](#repository-layout)
- [Idea backlogs](#idea-backlogs)
- [Developer tooling](#developer-tooling)
- [Status and conventions](#status-and-conventions)

## About

This repository is where I try things out before they become real projects. It covers three kinds of work:

- **Working code**: a 2D game engine and an ECS-based game, both in C++ on SDL2, plus a game compiled to WebAssembly.
- **Design studies**: architecture, design patterns and a code skeleton for a multithreaded C++ device-control application with an Electron UI.
- **Notes and idea backlogs**: tutorials, setup guides and project ideas that I want to keep next to the code.

## Repository map

| Area | Path | Kind | What it is |
|---|---|---|---|
| Game engine | [`src/game_engine`](src/game_engine) | Code | SDL2 engine: entities and components, tile maps, animation, camera, input, timer |
| Game tutor | [`src/game_tutor`](src/game_tutor) | Code | Step-by-step SDL2 game: ECS, collisions, scrolling tile maps, projectiles |
| WebAssembly game | [`src/wasm`](src/wasm) | Code | Tile-merging game built with Emscripten and SDL2, runs in the browser |
| Instrument controller | [`app/syntax_controller`](app/syntax_controller) | Design | Architecture, design patterns, logger and skeleton for a C++ device-control app |
| SDL2 tutorial notes | [`src/sdl2_tutor`](src/sdl2_tutor) | Notes | Lesson outline (window, textures, sprites, AABB collision, gravity) |
| Chat UI in SDL2 | [`src/sdl2_chat_ui`](src/sdl2_chat_ui) | Notes | Approach and sample code for a chat window |
| GTK+ | [`src/gtk+`](src/gtk+) | Notes | Minimal GTK 3 window examples in C and Python |
| Molecular dynamics | [`src/molecular_dunamic_simulation`](src/molecular_dunamic_simulation) | Notes | Lennard-Jones simulation approach in C++ |
| Neovim | [`nvim`](nvim) | Notes | NvChad install and configuration guide |
| Idea backlogs | root `*.md` files | Ideas | See [Idea backlogs](#idea-backlogs) |

## Projects

### Game engine · `src/game_engine`

A small 2D engine on **SDL2**, about 1,300 lines of C++.

- Entity-component-system core (`core/entity_component_system`) with a transform component
- Engine singleton with the classic `events → update → render` loop and a frame timer
- Tile maps loaded from Tiled `.tmx` files via **tinyxml** (`map/`)
- Sprite animation, camera, input handling and a 2D vector / rigid body physics layer
- Sample assets: tilesets, background and a character sprite sheet

### Game tutor · `src/game_tutor`

A game built up in small steps to learn the fundamentals, about 1,300 lines of C++. The steps are listed in its [Readme](src/game_tutor/Readme.md):

game loop, textures, frame-rate limiting, `GameObject`, tile maps, entity component system, sprites, `Vector2D`, input, AABB collision, tile components, entity groups, scrolling maps, assets manager.

### WebAssembly game · `src/wasm`

A tile-merging board game (4×4 grid, keyboard movement, tiles merge on contact) written in C++ with SDL2 and compiled to **WebAssembly** with Emscripten. It ships with an HTML shell template for running in the browser.

### Instrument controller design · `app/syntax_controller`

A design study for a modern **C++23** application that talks to laboratory hardware. It is documentation and skeleton code, not a buildable project.

| Layer | Responsibility |
|---|---|
| UI | Electron + React, talks to the backend over a TCP socket with Protocol Buffers |
| Communication | A central manager routing UI, MQTT and serial traffic |
| Application core | Instrument, device, process and consumables managers |
| Messaging | Protocol Buffers for all data exchange |

Contents: [Architecture](app/syntax_controller/Architecture.md) · [Design patterns](app/syntax_controller/design_patterns.md) (layered architecture, observer, command, state, strategy, factory, mediator, dependency injection) · [Logger and config](app/syntax_controller/logger.md) · [Code skeleton](app/syntax_controller/skeleton.md) · [Architecture diagram](app/syntax_controller/architecture_diagram.png) · [Observer diagram](app/syntax_controller/observer_pattern_diagram.svg)

## Tech stack

| Area | Tools |
|---|---|
| Language | C++20 (design studies target C++23) |
| Build | CMake, Ninja |
| Dependencies | Conan 2: `sdl`, `sdl_image`, `sdl_ttf`, `zlib`, `tinyxml` |
| Graphics | SDL2, SDL2_image, SDL2_ttf |
| Web | Emscripten (emsdk), WebAssembly |
| Editors | VS Code (clangd, CodeLLDB, CMake Tools), Neovim (NvChad) |

## Getting started

Prerequisites: a C++20 compiler, [CMake](https://cmake.org), [Ninja](https://ninja-build.org) and [Conan 2](https://conan.io).

> The commands below come from the scripts in [`scripts/`](scripts). Run them from the repository root.

### Native build (game engine and game tutor)

```bash
./scripts/install_dependencies.sh   # creates a default Conan profile if missing, installs into ./build
./scripts/build.sh                  # CMake + Ninja, Release, output in ./build
```

If Conan cannot detect your toolchain, run `conan profile detect --force`.

### WebAssembly build

1. Install the Emscripten SDK.

   **Windows**
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   git pull
   ./emsdk install latest
   ./emsdk activate latest --permanent
   emsdk_env.bat
   ```

   **Linux** (steps not yet verified)
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   git pull
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh
   ```

2. Check the toolchain with the smoke test:

   ```bash
   mkdir test-build
   emcc src/wasm/hello.cpp -o test-build/hello.html
   cd test-build
   npx lite-server        # then open hello.html
   ```

3. Build and serve the project:

   ```bash
   ./scripts/wasm_install_dependencies.sh   # Conan install using emscripten.profile
   ./scripts/wasm_build.sh                  # CMake + Ninja into ./wasm_build
   ./scripts/wasm_run.sh                    # serves the build on http://localhost:7000
   ```

## Repository layout

```
research/
├── app/
│   └── syntax_controller/      # architecture, design patterns, logger, code skeleton
├── src/
│   ├── game_engine/            # SDL2 engine (entities, tile maps, animation, camera)
│   ├── game_tutor/             # step-by-step SDL2 game with ECS and collisions
│   ├── wasm/                   # WebAssembly game and HTML template
│   ├── sdl2_tutor/             # lesson outline
│   ├── sdl2_chat_ui/           # chat UI notes
│   ├── gtk+/                   # GTK examples (C, Python)
│   └── molecular_dunamic_simulation/
├── scripts/                    # build, dependency and run helpers
├── nvim/                       # Neovim setup guide
├── .vscode/                    # recommended extensions, launch and editor settings
├── CMakeLists.txt              # root build (native targets and the Emscripten target)
├── conanfile.txt               # native dependencies
├── wasm_conanfile.txt          # WebAssembly dependencies
├── emscripten.profile          # Conan host profile for Emscripten
└── *_projects.md               # idea backlogs
```

## Idea backlogs

Project ideas I want to build later, each with a proposed folder structure and feature list:

| Backlog | Ideas |
|---|---|
| [C++ projects](C++_projects.md) | Camera stream with OpenCV, serial communication, live wallpaper, device controller |
| [Rust projects](Rust_projects.md) | CLI task manager, static site generator, URL shortener, file watcher, config reader |
| [Python projects](Python_projects.md) | Tkinter games and tools: quiz, drawing app, memory game, and more |
| [ML projects](ML_projects.md) | Image classifier, digit recognizer, sentiment analysis, price predictor, tic-tac-toe AI |
| [Dogon + Electron + gRPC](Dogon+Electron+gRPC.md) | Integration plan for a C++ gRPC backend with an Electron client |

## Developer tooling

- **VS Code** extensions are recommended in [`.vscode/extensions.json`](.vscode/extensions.json): clangd, CodeLLDB, CMake Tools, GitLens, ESLint, Jest Runner and Copilot. Dev Containers is also useful.
- **Neovim**: see the [NvChad setup guide](nvim/nvim_toutor.md).
- **Dependency graph**: `./scripts/conan_graph.sh` writes `graph.html` with the Conan dependency graph.

## Status and conventions

- This is a working notebook: the design studies and idea backlogs are drafts and will change.
- The Linux Emscripten setup steps are untested.
- The default branch is `development`.
- There is no license file yet.
