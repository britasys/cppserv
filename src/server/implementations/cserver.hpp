#pragma once

#ifndef __H_CSERVER__
#define __H_CSERVER__

#include <iserver.hpp>

namespace __N_SERVER__
{
    class CServer : public IServer
    {
    private:
    protected:
    public:
        CServer() = default;
        CServer(const CServer&) = delete;
        CServer(CServer&&) = delete;
        CServer& operator = (const CServer&) = delete;
        CServer& operator = (CServer&&) = delete;
        virtual ~CServer() = default;

        bool listen() const noexcept final;
    };
} // !__N_SERVER__

#endif // !__H_CSERVER__