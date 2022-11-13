#pragma once

#ifndef __H_IREQUEST__
#define __H_IREQUEST__

#include "../../ipacket.hpp"

namespace __N_PACKET__
{
    typedef enum class _request_header_method
    {
        NA, GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE, PATCH
    } REQUEST_HEADER_METHOD;
    
    class IRequest : public IPacket
    {
    private:
        REQUEST_HEADER_METHOD m_method{ REQUEST_HEADER_METHOD::NA };

    protected:
    public:
        IRequest() = default;
        IRequest(const IRequest&) = delete;
        IRequest(IRequest&&) = delete;
        IRequest& operator = (const IRequest&) = delete;
        IRequest& operator = (IRequest&&) = delete;
        virtual ~IRequest() = default;

        void method(const REQUEST_HEADER_METHOD method) noexcept { this->m_method = method; }
        REQUEST_HEADER_METHOD method() const noexcept { return this->m_method; }
    };
} // !__N_PACKET__

using REQUEST = std::shared_ptr<__N_PACKET__::IRequest>;

#endif // !__H_IREQUEST__