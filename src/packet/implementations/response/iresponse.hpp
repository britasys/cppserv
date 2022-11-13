#pragma once

#ifndef __H_IRESPONSE__
#define __H_IRESPONSE__

#include "../../ipacket.hpp"

namespace __N_PACKET__
{
    typedef enum class _response_header_status
    {
        CODE_NA,  // not available

        // informational
        CODE_100 = 100, // continue
        CODE_101 = 101, // swithing protocols
        CODE_102 = 102, // processing
        CODE_103 = 103, // early hints

        // success
        CODE_200 = 200, // ok
        CODE_201 = 201, // created
        CODE_202 = 202, // accepted
        CODE_203 = 203, // non-authoritative information
        CODE_204 = 204, // no content
        CODE_205 = 205, // reset content
        CODE_206 = 206, // partial content
        CODE_207 = 207, // multi-status
        CODE_208 = 208, // already reported
        CODE_226 = 226, // IM used

        // redirection
        CODE_300 = 300, // multiple choices
        CODE_301 = 301, // moved permanently
        CODE_302 = 302, // found (Previously "Moved temporarily")
        CODE_303 = 303, // see other
        CODE_304 = 304, // not modified
        CODE_305 = 305, // use proxy
        CODE_306 = 306, // switch proxy
        CODE_307 = 307, // temporary redirect
        CODE_308 = 308, // permanent redirect

        // client errors
        CODE_400 = 400, // bad request
        CODE_401 = 401, // unahorized
        CODE_402 = 402, // permanently required
        CODE_403 = 403, // forbidden
        CODE_404 = 404, // not found
        CODE_405 = 405, // method not allowd
        CODE_406 = 406, // not acceptable
        CODE_407 = 407, // proxy authentication required
        CODE_408 = 408, // request timeout
        CODE_409 = 409, // confilict
        CODE_410 = 410, // gone
        CODE_411 = 411, // length required
        CODE_412 = 412, // precondition failed
        CODE_413 = 413, // payload too large
        CODE_414 = 414, // url too long
        CODE_415 = 415, // unsopported media type
        CODE_416 = 416, // range not satisfiable
        CODE_417 = 417, // expectation failed
        CODE_418 = 418, // I'm teapot
        CODE_421 = 421, // misdirected request
        CODE_422 = 422, // unprocessable entity
        CODE_423 = 423, // locked
        CODE_424 = 424, // failed dependency
        CODE_425 = 425, // too early
        CODE_426 = 426, // upgrade required
        CODE_428 = 428, // precondition required
        CODE_429 = 429, // too many requests
        CODE_431 = 431, // request header fields too large
        CODE_451 = 451, // unavailable for legal reasons

        // server errors
        CODE_500 = 500, // internal serve error
        CODE_501 = 501, // not implemented
        CODE_502 = 502, // bad gateway
        CODE_503 = 503, // service unavailable
        CODE_504 = 504, // gateway timeout
        CODE_505 = 505, // HTTP version not supported
        CODE_506 = 506, // variant also negotiates
        CODE_507 = 507, // insufficient storage
        CODE_508 = 508, // loop detected
        CODE_510 = 510, // not extended
        CODE_511 = 511, // network authentication required
    } RESPONSE_HEADER_STATUS;

    class IResponse : public IPacket
    {
    private:
        RESPONSE_HEADER_STATUS m_status{ RESPONSE_HEADER_STATUS::CODE_NA };

    protected:
    public:
        IResponse() = default;
        IResponse(const IResponse&) = delete;
        IResponse(IResponse&&) = delete;
        IResponse& operator = (const IResponse&) = delete;
        IResponse& operator = (IResponse&&) = delete;
        virtual ~IResponse() = default;

        void status(const RESPONSE_HEADER_STATUS status) noexcept { this->m_status = status; }
        RESPONSE_HEADER_STATUS status() const noexcept { return this->m_status; }
    };
} // !__N_PACKET__

using RESPONSE = std::shared_ptr<__N_PACKET__::IResponse>;

#endif // !__H_IRESPONSE__