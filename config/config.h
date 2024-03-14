#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class  Config{
    private:
        Config();
        std::string _host;
        std::string _port;
        std::string _login;
        std::string _password;
        std::string _database;

    public:
        static Config& get();

        std::string& port();
        std::string& host();
        std::string& login();
        std::string& password();
        std::string& database();

        const std::string& getPort() const ;
        const std::string& getHost() const ;
        const std::string& getLogin() const ;
        const std::string& getPassword() const ;
        const std::string& getDatabase() const ;
};

#endif