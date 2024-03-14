#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class User{
        private:
            long _id;
            std::string _first_name;
            std::string _last_name;
            std::string _email;
            std::string _title;
            std::string _login;
            std::string _password;

        public:

            static User fromJSON(const std::string & str);

            long             get_id() const;
            const std::string &getFirstName() const;
            const std::string &getLastName() const;
            const std::string &getEmail() const;
            const std::string &getTitle() const;
            const std::string &getLogin() const;
            const std::string &getPassword() const;

            long&        id();
            std::string &firstName();
            std::string &lastName();
            std::string &email();
            std::string &title();
            std::string &login();
            std::string &password();

            static void init();
            static std::optional<User> readByLogin(std::string &login);
            static std::optional<User> readById(long id);
            static std::optional<long> logIn(std::string &login, std::string &password);
            static std::vector<User> readAll();
            static std::vector<User> search(std::string first_name,std::string last_name);
            void saveToMySQL();

            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif