# cmake_minimum_required(VERSION 3.2)
# project(game)

# # add_definitions(-std=c++17)
# set (CMAKE_CXX_STANDARD 20)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# # add_executable(game src/box.cpp src/game_logic.cpp)

# find_package(emsdk)

# message("EMSDK ${EMSDK_ROOT}")
# # find_package(SDL2_image)
# # find_package(SDL2_ttf)
# # find_package(SDL2)
# # target_link_libraries(game emsdk::emsdk SDL2_image::SDL2_image sdl_ttf::sdl_ttf SDL2::SDL2main)

# # if (DEFINED EMSCRIPTEN)
# #     message("EMSCRIPTEN")

#     # set(CMAKE_CXX_COMPILER /root/.conan2/p/emsdk94273ab0a026a/p/bin/upstream/emscripten/emcc)

#     # add_executable(game src/hello.cpp)

# #     set(CMAKE_EXECUTABLE_SUFFIX ".html")
# #     set(EM_FLAGS "")
# #     set(EM_FLAGS "${EM_FLAGS} -fsanitize=address --profiling")
# #     set(EM_FLAGS "${EM_FLAGS} --preload-file ../assets@/assets/")
# #     set(EM_FLAGS "${EM_FLAGS} -O2 -g -gsource-map --source-map-base http://localhost:8080/")
# #     set(EM_FLAGS "${EM_FLAGS} -s USE_SDL=2 -s USE_SDL_TTF=2")
# #     set(EM_FLAGS "${EM_FLAGS} -s INITIAL_MEMORY=256MB -s TOTAL_MEMORY=256MB -s ALLOW_MEMORY_GROWTH=1")
# #     set_target_properties(game PROPERTIES LINK_FLAGS ${EM_FLAGS})

# #     # set(CMAKE_EXECUTABLE_SUFFIX ".wasm")
# #     # set_target_properties(game PROPERTIES COMPILE_FLAGS "-Os")
# #     # set_target_properties(game PROPERTIES LINK_FLAGS "-Os -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry ")
# # elseif()
# #     install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assets
# #         DESTINATION ${CMAKE_BINARY_DIR}/bin
# #         COMPONENT installables
# #         FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
# #         DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
# #     )
# # endif()


cmake_minimum_required(VERSION 3.0)
project(MyEmscriptenProject)

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(my_project src/game_logic.cpp src/box.cpp)
# Ensure CMake is using the Emscripten toolchain
if(EMSCRIPTEN)
    set(EMSCRIPTEN_RUNTIME "html5")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s EXPORTED_FUNCTIONS=['_main']")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")  # For optimization
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --shell-file ${CMAKE_SOURCE_DIR}/html_template/shell_minimal.html --preload-file ../assets@/assets/")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_TTF=2") # SDL2 and SDL2_ttf
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
else()
    add_subdirectory(src/mario)

    find_package(SDL2_image)
    find_package(SDL2_ttf)
    find_package(SDL2)
    target_link_libraries(my_project SDL2_image::SDL2_image sdl_ttf::sdl_ttf SDL2::SDL2main)
endif()