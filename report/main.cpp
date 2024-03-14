#include <iostream>
#include "../web_server/http_web_server.h"
#include "../web_server/http_request_factory.h"
#include "report_handler.h"
#include <vector>

int main(int argc, char*argv[]) 
{
    HTTPWebServer app(8081, [](const std::string &format)
    {
        database::Report::init();
        std::vector<std::string> paths = { 
                "/report", 
                "/report/add" 
            };

        return new HTTPRequestFactory(
            format, 
            "Report", 
            [](const std::string &format2)
            {
                return new ReportHandler(format2);
            },
            paths);
    });
    return app.run(argc, argv);
}