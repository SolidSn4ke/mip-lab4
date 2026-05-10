#pragma once

#include "rest_controller.h"
#include "service/obj_service.h"
#include "service/scene_renderer.h"

class SceneController : public RestController {
  public:
    OBJService obj_service;
    SceneRenderer renderer;
    SceneController(OBJService& obj_service);
    void register_endpoints(httplib::Server& server) override;
};
