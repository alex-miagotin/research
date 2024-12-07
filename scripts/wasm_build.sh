cmake -S . -B wasm_build -G Ninja -DCMAKE_TOOLCHAIN_FILE=./build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release 
cmake --build ./wasm_build