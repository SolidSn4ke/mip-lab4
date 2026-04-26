#include "rest/scene_controller.h"
#include "service/obj_service.h"
#include <httplib.h>

int main() {
    std::cout << "Started" << std::endl;

    httplib::Server server;
    OBJService obj_service;
    SceneController controller(obj_service);
    int port = 8080;

    controller.register_endpoints(server);

    server.listen("localhost", port);
}
