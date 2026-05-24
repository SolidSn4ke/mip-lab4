#include "rest/scene_controller.h"
#include "service/obj_service.h"
#include <httplib.h>
#include <iostream>

int main() {
    httplib::Server server;
    OBJService obj_service;
    SceneController controller(obj_service);
    int port = 8080;

    controller.register_endpoints(server);

    std::cout << "Server started on port " << port << std::endl;

    server.listen("localhost", port);
}
