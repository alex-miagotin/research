cmake_minimum_required(VERSION 3.0)
project(MyEmscriptenProject)

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(wasm src/wasm/game_logic.cpp src/wasm/box.cpp)
# Ensure CMake is using the Emscripten toolchain
if(EMSCRIPTEN)
    set(EMSCRIPTEN_RUNTIME "html5")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s EXPORTED_FUNCTIONS=['_main']")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")  # For optimization
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --shell-file ${CMAKE_SOURCE_DIR}/src/wasm/html_template/shell_minimal.html --preload-file ../src/wasm/assets@/assets/")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_TTF=2") # SDL2 and SDL2_ttf
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
else()
    # game tutor ECS
    add_subdirectory(src/game_tutor)

    # game_engine
    add_subdirectory(src/game_engine)

    find_package(SDL2_image)
    find_package(SDL2_ttf)
    find_package(SDL2)
    target_link_libraries(wasm SDL2_image::SDL2_image sdl_ttf::sdl_ttf SDL2::SDL2main)
endif()