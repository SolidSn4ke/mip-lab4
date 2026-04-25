#include "hello_controller.h"

void HelloController::register_endpoints(httplib::Server &server)
{
    server.Get("/hello", [](const httplib::Request &req, httplib::Response &resp)
               { resp.set_content("hello world\n", "text/plain"); });
}