#include "scene_controller.h"

SceneController::SceneController(OBJService &obj_service)
{
    this->obj_service = obj_service;
}

void SceneController::register_endpoints(httplib::Server &server)
{
    server.Post("/scene", [](const httplib::Request &req, httplib::Response &resp)
                { 
        if (req.form.has_file("scene"))
        {
            const auto& file = req.form.get_file("scene");
        } });
}