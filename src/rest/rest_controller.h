#pragma once

#include <httplib.h>

class RestController
{
public:
    virtual void register_endpoints(httplib::Server &server) = 0;
};
