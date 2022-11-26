#include <cppserv.hpp>

#include <iostream>

using namespace __N_CPPSERV__;

int main()
{
    auto l_middleware_lambda = [](REQUEST& req, RESPONSE& res) -> bool { return true; };
    auto l_controller_lambda = [](REQUEST& req, RESPONSE& res) -> bool {
        std::cout << "Packet recieved" << std::endl;
        res.status = RESPONSE_HEADER_STATUS::CODE_200;
        res.field("content-type", "text/plain");
        res.body.assign("Hello from api");

        return true;
    };

    ROUTER l_router{};
    l_router.route.assign("/");
    l_router.controller = l_controller_lambda;
    l_router.middleware = l_middleware_lambda;

    auto l_server = SERVER{};
    l_server.routers.push_back(l_router);
    l_server.run();

    return 0;
}