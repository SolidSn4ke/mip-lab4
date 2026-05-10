#include "scene_controller.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <regex>

using json = nlohmann::json;

SceneController::SceneController(OBJService& obj_service) : obj_service(obj_service), renderer() {}

void SceneController::register_endpoints(httplib::Server& server) {

    server.Post("/scene", [this](const httplib::Request& req, httplib::Response& resp) {
        try {
            if (req.form.has_file("scene") && req.form.has_file("obj")) {
                const auto& obj_file = req.form.get_file("obj");
                const auto& scene_file = req.form.get_file("scene");

                std::regex objPattern(R"(.+\.obj)", std::regex::icase);
                std::regex jsonPattern(R"(.+\.json)", std::regex::icase);
                if (std::regex_match(obj_file.filename, objPattern) &&
                    std::regex_match(scene_file.filename, jsonPattern)) {
                    // Парсить OBJ файл
                    auto triangles = obj_service.parse_obj(obj_file.content);

                    if (triangles.empty()) {
                        resp.set_content("Ошибка: OBJ файл не содержит треугольников",
                                         "text/plain");
                        resp.status = 400;
                    } else {
                        std::cout << "Parsed " << triangles.size() << " triangles" << std::endl;

                        json data = json::parse(scene_file.content);

                        renderer.camera_position =
                            Vector(data["camera"]["position"]["x"], data["camera"]["position"]["y"],
                                   data["camera"]["position"]["z"]);
                        renderer.camera_target =
                            Vector(data["camera"]["target"]["x"], data["camera"]["target"]["y"],
                                   data["camera"]["target"]["z"]);

                        for (auto& light : data["lights"]) {
                            renderer.lights.push_back(LightSource(
                                Vector(light["p1"]["x"], light["p1"]["y"], light["p1"]["z"]),
                                Vector(light["p2"]["x"], light["p2"]["y"], light["p2"]["z"]),
                                Vector(light["p3"]["x"], light["p3"]["y"], light["p3"]["z"]),
                                Color(light["color"]["r"], light["color"]["g"],
                                      light["color"]["b"])));
                        }

                        renderer.width = data["width"];
                        renderer.height = data["height"];
                        renderer.samples_per_pixel = data["spp"];

                        // Отрендерить сцену
                        std::string ppm_content = renderer.renderToString(triangles);

                        resp.set_content(ppm_content, "image/ppm");
                        resp.status = 200;
                    }
                } else {
                    resp.set_content("Принимаются только OBJ файлы", "text/plain");
                    resp.status = 400;
                }
            } else {
                resp.set_content("Файл не найден в запросе", "text/plain");
                resp.status = 400;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            resp.set_content(std::string("Ошибка сервера: ") + e.what(), "text/plain");
            resp.status = 500;
        }

        resp.set_header("Access-Control-Allow-Origin", "*");
        resp.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        resp.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        resp.set_header("Access-Control-Max-Age", "86400");
    });
}