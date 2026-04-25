#pragma once

#include "rest_controller.h"

class HelloController : public RestController
{

public:
    void register_endpoints(httplib::Server &server) override;
};
