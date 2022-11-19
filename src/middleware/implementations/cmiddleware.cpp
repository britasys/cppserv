#include "cmiddleware.hpp"

namespace __N_MIDDLEWARE__
{    
    std::shared_ptr<IMiddleware> createMiddleware(LAMBDA lambda) noexcept
    {
        return std::make_shared<CMiddleware>(lambda);
    }
} // !__N_MIDDLEWARE__