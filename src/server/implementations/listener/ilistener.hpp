#pragma once

#ifndef __H_ILISTENER__
#define __H_ILISTENER__

#include <request/irequest.hpp>
#include <response/iresponse.hpp>

#include <memory>
#include <string>
#include <functional>

namespace __N_LISTENER__
{
    using LISTENER_LAMBDA = std::function<bool(REQUEST, RESPONSE)>;

    typedef struct _listener_init
    {
        std::string address{ "0.0.0.0" };
        unsigned short port{ 8080 };
        LISTENER_LAMBDA lambda{};
    } LISTENER_INIT, * LP_LISTENER_INIT;

    class IListener
    {
    private:
    protected:
        LISTENER_INIT m_init{};

    public:
        IListener() = default;
        IListener(const IListener&) = delete;
        IListener(IListener&&) = delete;
        IListener& operator = (const IListener&) = delete;
        IListener& operator = (IListener&&) = delete;
        virtual ~IListener() = default;

        void initialize(const LISTENER_INIT& init) noexcept { this->m_init = init; }
        
        virtual bool run() const noexcept = 0;
    };

    std::shared_ptr<IListener>createListener() noexcept;
} // !__N_LISTENER__

using LISTENER = std::shared_ptr<__N_LISTENER__::IListener>;

#endif // !__H_ILISTENER__