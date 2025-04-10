✅ Logging and configuration support added:

- `Logger`: Console + optional file output with thread safety
- `Config`: Central key-value config store

You can now do:
```cpp
Logger::instance().log("System started");
Logger::instance().enableFileLogging("log.txt");

Config::instance().set("port", "/dev/ttyUSB0");
std::string port = Config::instance().get("port");
```

```
// Logger.h
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
public:
    static Logger& instance();
    void log(const std::string& message);
    void enableFileLogging(const std::string& filename);

private:
    Logger() = default;
    std::ofstream logFile;
    std::mutex mtx;
};

// Logger.cpp
#include "Logger.h"

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[LOG] " << message << std::endl;
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}

void Logger::enableFileLogging(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx);
    logFile.open(filename, std::ios::app);
}

// Config.h
#pragma once
#include <string>
#include <map>

class Config {
public:
    static Config& instance();
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key, const std::string& defaultValue = "") const;

private:
    Config() = default;
    std::map<std::string, std::string> settings;
};

// Config.cpp
#include "Config.h"

Config& Config::instance() {
    static Config config;
    return config;
}

void Config::set(const std::string& key, const std::string& value) {
    settings[key] = value;
}

std::string Config::get(const std::string& key, const std::string& defaultValue) const {
    auto it = settings.find(key);
    return (it != settings.end()) ? it->second : defaultValue;
}
```