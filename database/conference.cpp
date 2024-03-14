#include "conference.h"
#include "database.h"
#include "report.h"
#include "../config/config.h"

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>
#include <exception>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace database
{
    void Conference::init()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Conference` (`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`reportId` INT NOT NULL,"
                        << "`userId` INT NOT NULL,"
                        << "PRIMARY KEY (`id`),"
                        << "FOREIGN KEY (`reportId`) REFERENCES Report (`id`),"
                        << "FOREIGN KEY (`userId`) REFERENCES User (`id`));",
                now;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    std::vector<Report> Conference::readAllFor(const long &id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<Report> result;
            Report a;

            std::string sql = "SELECT id, name, type, description, author FROM Report WHERE id IN (SELECT reportId FROM Conference WHERE userId=" + std::to_string(id) + ")";
            std::cout << "SQL Request: " << sql << std::endl;
            select << sql,
                into(a.id()),
                into(a.name()),
                into(a.type()),
                into(a.description()),
                into(a.author()),
                range(0, 1);

            while (!select.done())
            {
                if (select.execute())
                    result.push_back(a);
            }
            return result;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl << e.displayText() << std::endl;
            throw;
        }
    }

    std::vector<Conference> Conference::readAll()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<Conference> result;
            Conference a;

            std::string sql = "SELECT reportId, userId FROM Conference";
            std::cout << "SQL Request: " << sql << std::endl;
            select << sql,
                into(a._report_id),
                into(a._user_id),
                range(0, 1);

            while (!select.done())
            {
                if (select.execute())
                    result.push_back(a);
            }
            return result;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl << e.displayText() << std::endl;
            throw;
        }
    }

    void Conference::saveToMySQL()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            insert << "INSERT INTO Conference (reportId, userId) VALUES(?, ?)",
                use(_report_id),
                use(_user_id);

            insert.execute();

            Poco::Data::Statement select(session);
            select << "SELECT LAST_INSERT_ID()",
                into(_id),
                range(0, 1); //  iterate over result set one row at a time

            if (!select.done())
            {
                select.execute();
            }
            std::cout << "Inserted Conference id: " << _id << std::endl;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    Poco::JSON::Object::Ptr Conference::toJSON(bool exclude_id=false) const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        if (!exclude_id)
            root->set("id", _id);
        root->set("reportId", _report_id);
        root->set("userId", _user_id);

        return root;
    }

    long Conference::getId() const { return _id; }
    const long &Conference::getReportId() const { return _report_id; }
    const long &Conference::getUser() const { return _user_id; }

    long& Conference::id() { return _id; }
    long &Conference::report() { return _report_id; }
    long &Conference::user() { return _user_id; }
}