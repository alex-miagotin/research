
find_package(SDL2_image)
find_package(SDL2_ttf)
find_package(SDL2)
find_package(tinyxml)

set(PROJECT_NAME game_engine)

set (
    SRC_FILES
    main.cpp
    # core
    core/engine.cpp
    # core components
    core/components/transform_component.cpp
    # core physics
    core/physics/vector2D.cpp
    # graphics
    graphics/texture_manager.cpp
    # animation
    animation/animation.cpp
    # characters
    characters/monster.cpp
    # inputs
    inputs/input.cpp
    # timer
    timer/timer.cpp
    # map
    map/tile_layer.cpp
    map/map_parser.cpp
    # camera
    camera/camera.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image sdl_ttf::sdl_ttf SDL2::SDL2main tinyxml::tinyxml)

set(MY_ASSETS_PATH "${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}_assets")
add_definitions(-DASSETS_PATH="${MY_ASSETS_PATH}")
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${MY_ASSETS_PATH}
)
add_dependencies(${PROJECT_NAME} copy_assets)
