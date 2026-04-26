#pragma once

#include "rest_controller.h"
#include "service/obj_service.h"

class SceneController : public RestController {
  public:
    OBJService obj_service;
    SceneController(OBJService& obj_service);
    void register_endpoints(httplib::Server& server) override;
};
