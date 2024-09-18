#include <iostream>

#define LOG(x) std::cout << x << std::endl

class Log {
public:
    enum Level {
        LevelError = 0, LevelWarning, LevelInfo
    };

private:
    Level m_LogLevel = LevelInfo;

public:
    void SetLevel(Level level) {
        m_LogLevel = level;
    }

    void Error(const char* message) {
        if (m_LogLevel >= LevelError)
            std::cout << "[ERROR]: " << message << std::endl;
    }
    void Warn(const char* message) {
        if (m_LogLevel >= LevelWarning)
            std::cout << "[WARNING]: " << message << std::endl;
    }
    void Info(const char* message) {
        if (m_LogLevel >= LevelInfo)
            std::cout << "[iNFO]: " << message << std::endl;
    }

};

int main() {
    Log log;
    log.SetLevel(Log::LevelWarning);
    log.Error("Hello!");
    log.Warn("Hello!");
    log.Info("Hello!");
    std::cin.get();
}