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


class Entity {
public:
    float X, Y;

    void Move(float xa, float ya) {
        X += xa;
        Y += ya;
    }

    virtual std::string GetName() { return "Entity"; }
};

class Player : public Entity {
private:
    std::string m_Name;

public:
    const char* Name;
    
    Player(const std::string& name)
        : m_Name(name) {}

    std::string GetName() { return m_Name; }

    void PrintName() {
        Log log;
        log.SetLevel(Log::LevelInfo);
        log.Info(Name);
    }
};

int main() {
    Log log;
    Entity* e = new Entity();
    log.Info(e->GetName().c_str());

    Player* p = new Player("Valiantlynx");
    log.Info(p->GetName().c_str());

    // problem arises if we need to call the player function as an entit
    Entity* entity = p;
    log.Info(entity->GetName().c_str()); // we excpect this to print the name of the player since a player is an entity but we are requesting for the name of the player but..
    // instead we get "Entity" printed. this is causewhen calling the method it calls the methos of the clas of whatever the type is
    // to fix this use virtual functions. trying this again after adding the virtual keyword we get correct
   
    delete e;
    delete p;
    delete entity;
    std::cin.get();
}