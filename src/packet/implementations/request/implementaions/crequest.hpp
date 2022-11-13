#pragma once

#ifndef __H_CREQUEST__
#define __H_CREQUEST__

#include "../irequest.hpp"

namespace __N_PACKET__
{
    class CRequest : public IRequest
    {
    private:
    protected:
    public:
        CRequest() = default;
        CRequest(const CRequest&) = delete;
        CRequest(CRequest&&) = delete;
        CRequest& operator = (const CRequest&) = delete;
        CRequest& operator = (CRequest&&) = delete;
        virtual ~CRequest() = default;
    };
} // !__N_PACKET__

#endif // !__H_CREQUEST__