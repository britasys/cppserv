#include <iserver.hpp>

int main()
{
    auto l_server = __N_SERVER__::createServer();
    l_server->listen();

    return 0;
}