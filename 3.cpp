#include <iostream>
#include <string>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void Log(const std::string& logText) = 0;
};

class FileLogger : public ILogger {
public:
    void Log(const std::string& logText) override {
        std::cout << "Log to file: " << logText << std::endl;
    }
};

class DatabaseLogger : public ILogger {
public:
    void Log(const std::string& logText) override {
        std::cout << "Log to database: " << logText << std::endl;
    }
};


class SmtpMailer {
private:
    ILogger* logger;

public:
    SmtpMailer(ILogger* logger) : logger(logger) {}

    void SendMessage(const std::string& message) {
        std::cout << "Sending message: " << message << std::endl;
        logger->Log("Message sent: " + message);
    }
};

int main() {
    FileLogger fileLogger;
    SmtpMailer mailerWithFileLogger(&fileLogger);
    mailerWithFileLogger.SendMessage("Hello with FileLogger!");

    DatabaseLogger dbLogger;
    SmtpMailer mailerWithDbLogger(&dbLogger);
    mailerWithDbLogger.SendMessage("Hello with DatabaseLogger!");

    return 0;
}