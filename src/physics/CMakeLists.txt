
find_package(SDL2_image)
find_package(SDL2_ttf)
find_package(SDL2)

set(PROJECT_NAME physics)

set (
    SRC_FILES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image sdl_ttf::sdl_ttf SDL2::SDL2main)