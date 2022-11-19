#pragma once

#ifndef __H_ICONTROLLER__
#define __H_ICONTROLLER__

#include <request/irequest.hpp>
#include <response/iresponse.hpp>
#include <middleware/imiddleware.hpp>

#include <memory>
#include <functional>

namespace __N_CONTROLLER__
{
    using LAMBDA = std::function<void(REQUEST, RESPONSE)>;

    class IController
    {
    private:
    protected:
    public:
        IController() = default;
        IController(const IController&) = default;
        IController(IController&&) = default;
        IController& operator = (const IController&) = default;
        IController& operator = (IController&&) = default;
        virtual ~IController() = default;

        virtual void run(REQUEST, RESPONSE) noexcept = 0;
    };

    std::shared_ptr<IController> createController(LAMBDA, MIDDLEWARE) noexcept;
} // !__N_CONTROLLER__

using CONTROLLER = std::shared_ptr<__N_CONTROLLER__::IController>;

#endif // !__H_ICONTROLLER__