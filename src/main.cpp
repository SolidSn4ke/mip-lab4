#include <httplib.h>
#include "rest/hello_controller.h"

int main()
{
    httplib::Server server;
    HelloController controller;
    int port = 8080;

    controller.register_endpoints(server);

    server.listen("localhost", port);
}
