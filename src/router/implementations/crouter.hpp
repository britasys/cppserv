#pragma once

#ifndef __H_CROUTER__
#define __H_CROUTER__

#include "../irouter.hpp"

namespace __N_ROUTER__
{
    class CRouter : public IRouter
    {
    private:
        std::string m_route{"/"};
        CONTROLLER m_controller{ nullptr };

    protected:
    public:
        CRouter() = delete;
        CRouter(const CRouter&) = default;
        CRouter(CRouter&&) = default;
        CRouter& operator = (const CRouter&) = default;
        CRouter& operator = (CRouter&&) = default;
        virtual ~CRouter() = default;

        CRouter(const std::string route, CONTROLLER controller) noexcept :  m_route{ route }, m_controller{ controller } {}

        void route(REQUEST, RESPONSE) noexcept final;
    };
} // !__N_ROUTER__

#endif // !__H_CROUTER__