#pragma once

#ifndef __H_IROUTER__
#define __H_IROUTER__

#include <request/irequest.hpp>
#include <response/iresponse.hpp>
#include <middleware/imiddleware.hpp>

#include <memory>
#include <functional>

namespace __N_ROUTER__
{
    using ROUTER_LAMBDA = std::function<void(REQUEST, RESPONSE, MIDDLEWARE)>;

    class IRouter
    {
    private:
    protected:
        std::string m_route{"/"};
        ROUTER_LAMBDA m_lambda{};

    public:
        IRouter() = delete;
        IRouter(const IRouter&) = delete;
        IRouter(IRouter&&) = delete;
        IRouter& operator = (const IRouter&) = delete;
        IRouter& operator = (IRouter&&) = delete;
        virtual ~IRouter() = default;

        IRouter(const std::string route, ROUTER_LAMBDA lambda) noexcept : m_route{ route }, m_lambda{ lambda } {}
    };

    std::shared_ptr<IRouter>createRouter(const std::string, ROUTER_LAMBDA) noexcept;
} // !__N_ROUTER__

using ROUTER = std::shared_ptr<__N_ROUTER__::IRouter>;

#endif // !__H_IROUTER__