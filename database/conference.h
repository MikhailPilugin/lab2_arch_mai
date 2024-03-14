#ifndef CONFERENCE_H
#define CONFERENCE_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>
#include "report.h"

namespace database
{
    class Conference{
        private:
            long _id;
            long _report_id;
            long _user_id;

        static std::vector<Conference> read_all(const std::string &where);

        public:

            static Conference fromJSON(const std::string & str);

            long getId() const;
            const long &getReportId() const;
            const long &getUser() const;

            long& id();
            long &report();
            long &user();

            static void init();
            static std::vector<Conference> readAll();
            static std::vector<Report> readAllFor(const long &id);
            void saveToMySQL();

            Poco::JSON::Object::Ptr toJSON(bool exclude_id) const;

    };
}

#endif