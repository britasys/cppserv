#include "crouter.hpp"

namespace __N_ROUTER__
{    
    std::shared_ptr<IRouter>createRouter(const std::string route, ROUTER_LAMBDA lambda) noexcept
    {
        return std::make_shared<CRouter>(route, lambda);
    }
} // !__N_ROUTER__