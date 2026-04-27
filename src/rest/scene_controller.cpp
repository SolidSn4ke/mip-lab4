#include "scene_controller.h"

SceneController::SceneController(OBJService& obj_service) {
    this->obj_service = obj_service;
}

void SceneController::register_endpoints(httplib::Server& server) {

    server.Post("/scene", [this](const httplib::Request& req, httplib::Response& resp) {
        if (req.form.has_file("scene")) {
            const auto& file = req.form.get_file("scene");
            std::regex objPattern(R"(.+\.obj)", std::regex::icase);
            if (std::regex_match(file.filename, objPattern)) {
                auto triangles = obj_service.parse_obj(file.content);
                resp.set_content("Успех", "text/palin");
            } else
                resp.set_content("Принимаются только OBJ файлы", "text/palin");
        }
        resp.set_header("Access-Control-Allow-Origin", "*");
        resp.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        resp.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        resp.set_header("Access-Control-Max-Age", "86400");
    });
}