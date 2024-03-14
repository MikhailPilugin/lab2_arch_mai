#include <iostream>
#include "../web_server/http_web_server.h"
#include "../web_server/http_request_factory.h"
#include "conference_handler.h"
#include <vector>

int main(int argc, char*argv[]) 
{
    HTTPWebServer app(8082, [](const std::string &format)
    {
        database::Conference::init();
        std::vector<std::string> paths = { 
                "/conference", 
                "/conference/put" 
            };

        return new HTTPRequestFactory(
            format, 
            "Conference", 
            [](const std::string &format2)
            {
                return new ConferenceHandler(format2);
            },
            paths);
    });
    return app.run(argc, argv);
}