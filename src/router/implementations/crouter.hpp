#pragma once

#ifndef __H_CROUTER__
#define __H_CROUTER__

#include "../irouter.hpp"

namespace __N_ROUTER__
{
    class CRouter : public IRouter
    {
    private:
    protected:
    public:
        CRouter() = delete;
        CRouter(const CRouter&) = delete;
        CRouter(CRouter&&) = delete;
        CRouter& operator = (const CRouter&) = delete;
        CRouter& operator = (CRouter&&) = delete;
        virtual ~CRouter() = default;

        CRouter(const std::string route, ROUTER_LAMBDA lambda) noexcept : IRouter(route, lambda) {}
    };
} // !__N_ROUTER__

#endif // !__H_CROUTER__