#ifndef HTTPREQUESTFACTORY_H
#define HTTPREQUESTFACTORY_H

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include <iostream>
#include <vector>
#include <functional>

using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;

#include "../helper.h"

class HTTPRequestFactory: public HTTPRequestHandlerFactory
{
public:
    HTTPRequestFactory(const std::string& format, const std::string& name, const std::function<HTTPRequestHandler* (const std::string&)> handler_factory, const std::vector<std::string> paths):
        _format(format),
        _name(name),
        _handler_factory(handler_factory),
        _paths(paths)
    {
        
    }

    HTTPRequestHandler* createRequestHandler(
        const HTTPServerRequest& request)
    {
        std::cout << "Request [" << _name << "][" << request.getMethod() << "]:" << request.getURI() << std::endl;

        if (check_uri(request.getURI())) 
            return _handler_factory(_format);
        return 0;
    }

private:
    std::string _format;
    std::string _name;
    std::function<HTTPRequestHandler* (const std::string&)> _handler_factory;
    std::vector<std::string> _paths;

    bool check_uri(const std::string &uri)
    {
        for (std::string str : _paths)
        {
            if (hasSubstr(uri, str))
                return true;
        }

        return false;
    }
};

#endif