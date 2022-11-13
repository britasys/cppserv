#pragma once

#ifndef __H_IPACKET__
#define __H_IPACKET__

#include <memory>
#include <string>
#include <unordered_map>

namespace __N_PACKET__
{
    using PACKET_HEADER_FIELDS = std::unordered_map<std::string, std::string>;

    typedef struct _packet_body
    {
        std::string body{};
    } PACKET_BODY, * LP_PACKET_BODY;

    class IPacket
    {
    private:
    protected:
        PACKET_HEADER_FIELDS m_fields{};
        PACKET_BODY m_body{};

    public:
        IPacket() = default;
        IPacket(const IPacket&) = delete;
        IPacket(IPacket&&) = delete;
        IPacket& operator = (const IPacket&) = delete;
        IPacket& operator = (IPacket&&) = delete;
        virtual ~IPacket() = default;

        void body(const std::string body) noexcept { this->m_body.body.assign(body); }
        std::string body()const noexcept { return this->m_body.body; }

        void field(const std::string name, const std::string value) noexcept
        {
            auto l_it = this->m_fields.find(name);
            if (this->m_fields.end() == l_it)
                this->m_fields.insert(std::make_pair(name, value));
            else
                l_it->second.assign(value);
        }

        std::string field(const std::string name) noexcept
        {
            auto l_it = this->m_fields.find(name);
            if (this->m_fields.end() == l_it)
                return std::string{};
            else
                return l_it->second;
        }
    };

    std::shared_ptr<IPacket> createRequest() noexcept;
    std::shared_ptr<IPacket> createResponse() noexcept;
} // !__N_PACKET__

using PACKET = std::shared_ptr<__N_PACKET__::IPacket>;

#endif // !__H_IPACKET__