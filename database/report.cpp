#include "report.h"
#include "database.h"
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
    void Report::init()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Report` (`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`name` VARCHAR(256) NOT NULL,"
                        << "`type` VARCHAR(256) NOT NULL,"
                        << "`description` VARCHAR(1024) NULL,"
                        << "`author` VARCHAR(256) NOT NULL,"
                        << "PRIMARY KEY (`id`),KEY `n` (`name`));",
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

    std::vector<Report> Report::read_all()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<Report> result;
            Report a;
            select << "SELECT id, name, type, description, author FROM Report",
                into(a._id),
                into(a._name),
                into(a._type),
                into(a._description),
                into(a._author),
                range(0, 1); //  iterate over result set one row at a time

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

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    void Report::save_to_mysql()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            insert << "INSERT INTO Report (name,type,description,author) VALUES(?, ?, ?, ?)",
                use(_name),
                use(_type),
                use(_description),
                use(_author);

            insert.execute();

            Poco::Data::Statement select(session);
            select << "SELECT LAST_INSERT_ID()",
                into(_id),
                range(0, 1); //  iterate over result set one row at a time

            if (!select.done())
            {
                select.execute();
            }
            std::cout << "Inserted Report id: " << _id << std::endl;
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

    Poco::JSON::Object::Ptr Report::toJSON(bool exclude_id=false) const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        if (!exclude_id)
            root->set("id", _id);
        root->set("name", _name);
        root->set("type", _type);
        root->set("description", _description);
        root->set("author", _author);

        return root;
    }

    long Report::get_id() const { return _id; }
    const std::string &Report::get_name() const { return _name; }
    const std::string &Report::get_type() const { return _type; }
    const std::string &Report::get_description() const { return _description; }
    const std::string &Report::get_author() const { return _author; }

    long& Report::id() { return _id; }
    std::string &Report::name() { return _name; }
    std::string &Report::type() { return _type; }
    std::string &Report::description() { return _description; }
    std::string &Report::author() { return _author; }
}