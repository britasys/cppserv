#include "cserver.hpp"

namespace __N_SERVER__
{
    bool CServer::listen() const noexcept
    {
        return true;
    }
    
    std::shared_ptr<IServer>createServer()
    {
        return std::make_shared<CServer>();
    }
} // !__N_SERVER__