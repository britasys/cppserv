#pragma once

#ifndef __H_ISERVER__
#define __H_ISERVER__

#include <server.hpp>

#include <router/irouter.hpp>

#include <deque>

namespace __N_SERVER__
{
    class IServer : public Server
    {
    private:
    protected:
        std::deque<ROUTER> m_routers{};

    public:
        IServer() = default;
        IServer(const IServer&) = delete;
        IServer(IServer&&) = delete;
        IServer& operator = (const IServer&) = delete;
        IServer& operator = (IServer&&) = delete;
        virtual ~IServer() = default;

        void addRouter(ROUTER router) noexcept { this->m_routers.push_back(router); }
    };
} // !__N_SERVER__

#endif // !__H_ISERVER__