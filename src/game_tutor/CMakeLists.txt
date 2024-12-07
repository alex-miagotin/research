
find_package(SDL2_image)
find_package(SDL2_ttf)
find_package(SDL2)

set(PROJECT_NAME game_tutor)

set (
    SRC_FILES
    main.cpp
    # game
    game/game.cpp
    game/texture_manager.cpp
    game/game_object.cpp
    game/map.cpp
    # ecs
    game/ecs/collider_component.cpp
    game/ecs/keyboard_controller.cpp
    game/ecs/sprite_component.cpp
    game/ecs/transform_component.cpp
    game/ecs/tile_component.cpp
    # common
    game/common/vector2D.cpp
    game/common/collision.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image sdl_ttf::sdl_ttf SDL2::SDL2main)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

set(MY_RESOURCE_PATH "${CMAKE_BINARY_DIR}/resources")
add_definitions(-DRESOURCE_PATH="${MY_RESOURCE_PATH}")
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)
add_dependencies(${PROJECT_NAME} copy_resources)