#include "cserver.hpp"

#include <listener/ilistener.hpp>

namespace __N_SERVER__
{
    bool CServer::listen() const noexcept
    {
        std::string address = "0.0.0.0";
        unsigned short port = 8080;
        unsigned short threads = 5;

        // Create and launch a listening port
        __N_LISTENER__::createListener(address, port, threads)->listen();
        
        return true;
    }
    
    Server* createServer()
    {
        return new CServer;
    }
} // !__N_SERVER__