#pragma once

#ifndef __H_CCONTROLLER__
#define __H_CCONTROLLER__

#include "../icontroller.hpp"

namespace __N_CONTROLLER__
{
    class CController : public IController
    {
    private:
        LAMBDA m_lambda{};
        MIDDLEWARE m_middleware{ nullptr };

    protected:
    public:
        CController() = default;
        CController(const CController&) = default;
        CController(CController&&) = default;
        CController& operator = (const CController&) = default;
        CController& operator = (CController&&) = default;
        virtual ~CController() = default;

        explicit CController(LAMBDA lambda, MIDDLEWARE middleware) : m_lambda{ lambda }, m_middleware{ middleware } {}

        void run(REQUEST request, RESPONSE response) noexcept final;
    };
} // !__N_CONTROLLER__

#endif // !__H_CCONTROLLER__