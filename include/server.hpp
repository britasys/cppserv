#pragma once

#ifndef __H_SERVER__
#define __H_SERVER__

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

namespace __N_SERVER__
{
    class Server
    {
    private:
    protected:
    public:
        Server() = default;
        Server(const Server&) = delete;
        Server(Server&&) = delete;
        Server& operator = (const Server&) = delete;
        Server& operator = (Server&&) = delete;
        virtual ~Server() = default;

        virtual void addRouter(ROUTER router) noexcept = 0;
        virtual bool listen() const noexcept = 0;
    };

    CPPSERV_API Server* createServer();
} // !__N_SERVER__

#endif // !__H_SERVER__