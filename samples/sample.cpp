#include <cppserv.hpp>

#include <iostream>

using namespace __N_CPPSERV__;

int main()
{
    auto l_controller_lambda = [](REQUEST& req, RESPONSE& res) -> bool {
        std::cout << "Packet recieved" << std::endl;
        res.status = RESPONSE_HEADER_STATUS::CODE_200;
        res.field("content-type", "application/json");
        res.body.assign("{\"name\":\"John\", \"age\":30, \"car\":null}");

        return true;
    };

    ROUTER l_router{};
    l_router.path.assign("/");
    l_router.controller = l_controller_lambda;

    auto l_server = SERVER<WEBSOCKET>{};
    l_server.routers.push_back(l_router);
    l_server.run();

    return 0;
}