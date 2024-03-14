#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Report{
        private:
            long _id;
            std::string _name;
            std::string _type;
            std::string _description;
            std::string _author;

        public:

            static Report fromJSON(const std::string & str);

            long             get_id() const;
            const std::string &get_name() const;
            const std::string &get_type() const;
            const std::string &get_description() const;
            const std::string &get_author() const;

            long&        id();
            std::string &name();
            std::string &type();
            std::string &description();
            std::string &author();

            static void init();
            static std::vector<Report> read_all();
            void save_to_mysql();

            Poco::JSON::Object::Ptr toJSON(bool exclude_id) const;

    };
}

#endif