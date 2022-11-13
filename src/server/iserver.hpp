#pragma once

#ifndef __H_ISERVER__
#define __H_ISERVER__

#include <router/irouter.hpp>

#include <memory>
#include <deque>

namespace __N_SERVER__
{
    class IServer
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

        virtual bool listen() const noexcept = 0;
    };

    std::shared_ptr<IServer>createServer();
} // !__N_SERVER__

using SERVER = std::shared_ptr<__N_SERVER__::IServer>;

#endif // !__H_ISERVER__