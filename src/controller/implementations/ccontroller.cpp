#include "ccontroller.hpp"

namespace __N_CONTROLLER__
{
    void CController::run(REQUEST request, RESPONSE response) noexcept
    {
        this->m_lambda(request, response);
        this->m_middleware->run(request, response);
    }

    std::shared_ptr<IController> createController(LAMBDA lambda, MIDDLEWARE middleware = __N_MIDDLEWARE__::createMiddleware([](REQUEST, RESPONSE){})) noexcept
    {
        return std::make_shared<CController>(lambda, middleware);
    }
} // !__N_CONTROLLER__