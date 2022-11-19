#pragma once

#ifndef __H_IROUTER__
#define __H_IROUTER__

#include <controller/icontroller.hpp>

#include <memory>

namespace __N_ROUTER__
{
    class IRouter
    {
    private:
    protected:
    public:
        IRouter() = default;
        IRouter(const IRouter&) = default;
        IRouter(IRouter&&) = default;
        IRouter& operator = (const IRouter&) = default;
        IRouter& operator = (IRouter&&) = default;
        virtual ~IRouter() = default;

        virtual void route(REQUEST, RESPONSE) noexcept = 0;
    };

    std::shared_ptr<IRouter>createRouter(const std::string, CONTROLLER) noexcept;
} // !__N_ROUTER__

using ROUTER = std::shared_ptr<__N_ROUTER__::IRouter>;

#endif // !__H_IROUTER__