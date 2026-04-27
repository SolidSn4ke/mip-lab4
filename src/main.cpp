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

    printf("Server started on port %d", port);
    server.listen("localhost", port);
}
