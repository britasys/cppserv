#include "crequest.hpp"

namespace __N_PACKET__
{    
    std::shared_ptr<IPacket> createRequest() noexcept
    {
        return std::make_shared<CRequest>();
    }
} // !__N_PACKET__