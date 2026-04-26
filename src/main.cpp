#include <httplib.h>
#include "rest/scene_controller.h"
#include "service/obj_service.h"

int main()
{
    httplib::Server server;
    OBJService obj_service;
    SceneController controller(obj_service);
    int port = 8080;

    controller.register_endpoints(server);

    server.listen("localhost", port);
}
