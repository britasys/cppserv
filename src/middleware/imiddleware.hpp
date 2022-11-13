#pragma once

#ifndef __H_IMIDDLEWARE__
#define __H_IMIDDLEWARE__

#include <request/irequest.hpp>
#include <response/iresponse.hpp>

#include <memory>
#include <functional>

namespace __N_MIDDLEWARE__
{
    using MIDDLEWARE_LAMBDA = std::function<void(REQUEST, RESPONSE)>;

    class IMiddleware
    {
    private:
    protected:
    public:
        IMiddleware() = default;
        IMiddleware(const IMiddleware&) = delete;
        IMiddleware(IMiddleware&&) = delete;
        IMiddleware& operator = (const IMiddleware&) = delete;
        IMiddleware& operator = (IMiddleware&&) = delete;
        virtual ~IMiddleware() = default;
    };
} // !__N_MIDDLEWARE__

using MIDDLEWARE = std::shared_ptr<__N_MIDDLEWARE__::IMiddleware>;

#endif // !__H_IMIDDLEWARE__