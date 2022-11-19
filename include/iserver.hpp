#pragma once

#ifndef __H_ISERVER__
#define __H_ISERVER__

#ifdef __cplusplus
    #define EXTERNC extern "C"
#else
    #define EXTERNC
#endif // !__cplusplus

#ifdef CPPSERV_EXPORTS
    #define  CPPSERV_API  EXTERNC __declspec(dllexport)
#else
    #define  CPPSERV_API  EXTERNC __declspec(dllimport)
    #pragma comment(lib, "cppserv")
#endif // !CPPSERV_EXPORTS

#include <router/irouter.hpp>

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

    CPPSERV_API IServer* createServer();
} // !__N_SERVER__

#endif // !__H_ISERVER__