# conan install . -pr:b default -pr:h emscripten.profile -s build_type=Release -b missing -of build

# check if conan profile exists using conan profile list and grep   
if ! conan profile list | grep -q "default"; then
    echo "conan profile not found, creating default..."
    conan profile detect
fi

conan install ./wasm_conanfile.txt \
    -c tools.system.package_manager:mode=install \
    --build=missing \
    --settings=compiler.cppstd=20 \
    --output-folder=wasm_build \
    --profile:host=emscripten.profile --profile:build=default \