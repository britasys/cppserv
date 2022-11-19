#include "cserver.hpp"

#include "./beast/beast.hpp"

using namespace __N_BEAST__;

namespace __N_SERVER__
{
    bool CServer::listen() const noexcept
    {
        // m_listener->run();
        
        auto const address = net::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(8080);
        auto const doc_root = std::make_shared<std::string>("./doc");
        auto const threads = std::max<int>(1, 5);

        // The io_context is required for all I/O
        net::io_context ioc{ threads };

        // Create and launch a listening port
        std::make_shared<listener>(
            ioc,
            tcp::endpoint{address, port},
            doc_root)->run();

        // Run the I/O service on the requested number of threads
        std::vector<std::thread> v;
        v.reserve(threads - 1);
        for(auto i = threads - 1; i > 0; --i)
            v.emplace_back(
            [&ioc]
            {
                ioc.run();
            });
        ioc.run();
        
        return true;
    }
    
    Server* createServer()
    {
        return new CServer;
    }
} // !__N_SERVER__