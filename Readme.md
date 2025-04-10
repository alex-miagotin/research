## Windows instalation
1. `git clone https://github.com/emscripten-core/emsdk.git`
2. `cd emsdk`
3. `git pull`
4. `./emsdk install latest`
5. `./emsdk activate latest --permanent`
6. `emsdk_env.bat`
7. `Restart PC` ???

## Linux instalation @TODO: not tested
1. `git clone https://github.com/emscripten-core/emsdk.git`
2. `cd emsdk`
3. `git pull`
4. `./emsdk install latest`
5. `./emsdk activate latest`
6. `source ./emsdk_env.sh`

## BUILD
##### Test build
1. `mkdir test-build`
2. `emcc src/hello.cpp -o test-build/hello.html`
3. `cd test-build`
4. `npx lite-server`
5. Open `hello.html`

##### Build
1. ``
2. `cmake -DCMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -S . -B build`
3. ``


#### Conan usefull
1. `conan profile detect --force`

#### Tools
1. `CMake Tools` - CMake support
2. `CMake` - CMake support
3. `CodeLLDB` - Debugger support
4. `clangd` - C++ support
5. `Dev Containers` - Dev container support