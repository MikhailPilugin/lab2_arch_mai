#include <iostream>
#include "../web_server/http_web_server.h"
#include "../web_server/http_request_factory.h"
#include "user_handler.h"
#include <vector>

int main(int argc, char*argv[]) 
{
    HTTPWebServer app(8080, [](const std::string &format)
    {
        database::User::init();

        std::vector<std::string> paths = { 
                "/account", 
                "/account/search",
                "/account/auth" 
            };

        return new HTTPRequestFactory(
            format, 
            "User", 
            [](const std::string &format2)
            {
                return new UserHandler(format2);
            },
            paths);
    });
    return app.run(argc, argv);
}