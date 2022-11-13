#pragma once

#ifndef __H_CRESPONSE__
#define __H_CRESPONSE__

#include "../iresponse.hpp"

namespace __N_PACKET__
{
    class CResponse : public IResponse
    {
    private:
    protected:
    public:
        CResponse() = default;
        CResponse(const CResponse&) = delete;
        CResponse(CResponse&&) = delete;
        CResponse& operator = (const CResponse&) = delete;
        CResponse& operator = (CResponse&&) = delete;
        virtual ~CResponse() = default;
    };
} // !__N_PACKET__

#endif // !__H_CRESPONSE__