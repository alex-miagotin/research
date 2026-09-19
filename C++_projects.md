# C++ Pet Projects Suite

This backlog describes a set of small C++ pet projects built using modern C++23, OpenCV, serial communication, and desktop graphics utilities. Each module is self-contained and demonstrates practical features ranging from camera feeds to hardware interfacing.

---

## 📁 Folder Structure

```
cpp-pet-projects/
├── camera_stream/           # OpenCV-based live camera stream and filters
├── serial_comm/             # Serial port communication example
├── live_wallpaper/          # Desktop wallpaper effects and animations
├── device_controller/       # Simple device controller (motors, sensors)
├── utils/                   # Common utilities (logging, timing, etc.)
├── include/                 # Shared headers
├── CMakeLists.txt           # Root CMake file
└── README.md                # This file
```

---

## 🔧 Dependencies

- **C++23** (GCC / Clang)
- **CMake 3.20+**
- **Conan** (for managing dependencies)
- **OpenCV** (for vision-related modules)
- **Boost.Asio** or **libserial** (for serial communication)
- **GLFW** + **OpenGL** (for graphical rendering / wallpaper effects)

Install via Conan or your package manager:

```bash
conan install . --build=missing
```

---

## 🚀 Modules Overview

### 📷 `camera_stream/`
Live video streaming using OpenCV. Apply filters, detect motion, or stream to a window.

### 🔌 `serial_comm/`
Communicate with real or mock serial devices (Arduino, custom boards). Parse commands and simulate data.

### 🎨 `live_wallpaper/`
Animate your desktop with OpenGL shaders or real-time visualizations. Windows/Linux supported.

### ⚙️ `device_controller/`
A generic controller for simulating or interfacing with motors, sensors, etc. Can be extended with TMC drivers.

---

## 🧪 Running the Projects

To build all:

```bash
mkdir build && cd build
cmake ..
make
```

Run any executable, for example:

```bash
./camera_stream/camera_app
```

---

## 🧰 Tips

- Enable debug output using `-DDEBUG=ON`.
- Use virtual serial port pairs (e.g., `socat`) for simulating communication.
- Check out the `tests/` folder for unit tests using GoogleTest.

---

## 📦 Future Ideas

- MQTT client integration
- Web-based control panel via embedded HTTP server
- Video recorder/exporter
- Device simulation with error modes and response delays

---

## 🤝 Contributing

These are hobby projects—PRs and improvements are welcome!

