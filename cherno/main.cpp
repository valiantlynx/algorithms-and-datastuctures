#include <iostream>
#include <string>

#define LOG(x) std::cout << x << std::endl

class Log {
public:
    enum Level {
        LevelError = 0, LevelWarning, LevelInfo
    };

    Log() {
        std::cout << "Logger initialized" << std::endl;
    }

    ~Log() {
        std::cout << "Logger Uninitialized" << std::endl;
    }

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

class Printable {
public:
    virtual std::string GetClassName() = 0;
};

class Entity : public Printable {
public:
    float X, Y;

    void Move(float xa, float ya) {
        X += xa;
        Y += ya;
    }

    virtual std::string GetName() = 0;
};

class Player : public Entity {
private:
    std::string m_Name;

public:
    const char* Name;
    
    Player(const std::string& name)
        : m_Name(name) {}

    std::string GetName() override { return m_Name; }
    
    std::string GetClassName() override { return "Player"; }

    void PrintName() {
        Log log;
        log.SetLevel(Log::LevelInfo);
        log.Info(Name);
    }
};

// we need to be guaranteed that we have a class name 
void PrintClassName(Printable* obj) {
    Log log;
    log.Info(obj->GetClassName().c_str());
}

int main() {
    Log log;

    Player* p = new Player("Valiantlynx");
    log.Info(p->GetClassName().c_str());

    std::cin.get();
    
    delete p;
}