#include "crouter.hpp"

namespace __N_ROUTER__
{

    void CRouter::route(REQUEST request, RESPONSE response) noexcept
    {
        this->m_controller->run(request, response);
    }
    
    std::shared_ptr<IRouter>createRouter(const std::string route, CONTROLLER controller) noexcept
    {
        return std::make_shared<CRouter>(route, controller);
    }
} // !__N_ROUTER__