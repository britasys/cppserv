#pragma once

#ifndef __H_CMIDDLEWARE__
#define __H_CMIDDLEWARE__

#include "../imiddleware.hpp"

namespace __N_MIDDLEWARE__
{
    class CMiddleware : public IMiddleware
    {
    private:
        LAMBDA m_lambda{};

    protected:
    public:
        CMiddleware() = delete;
        CMiddleware(const CMiddleware&) = delete;
        CMiddleware(CMiddleware&&) = delete;
        CMiddleware& operator = (const CMiddleware&) = delete;
        CMiddleware& operator = (CMiddleware&&) = delete;
        virtual ~CMiddleware() = default;

        explicit CMiddleware(LAMBDA lambda) : m_lambda{ lambda } {}

        void run(REQUEST request, RESPONSE response) noexcept { this->m_lambda(request, response); }
    };
} // !__N_MIDDLEWARE__

#endif // !__H_CMIDDLEWARE__