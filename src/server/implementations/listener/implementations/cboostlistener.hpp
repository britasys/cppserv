#pragma once

#ifndef __H_CBOOSTLISTENER__
#define __H_CBOOSTLISTENER__

#include "../ilistener.hpp"

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <memory>

namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
namespace beast = boost::beast;         // from <boost/beast.hpp>

namespace __N_LISTENER__
{
    // Accepts incoming connections and launches the sessions
    class CBoostListener : public std::enable_shared_from_this<CBoostListener>, public IListener
    {
    private:
        net::io_context& ioc_;
        tcp::acceptor acceptor_;

        void do_accept();
        void on_accept(beast::error_code, tcp::socket);

    protected:
    public:
        CBoostListener(net::io_context&, tcp::endpoint);

        void run();
    };
} // !__N_LISTENER__

#endif // !__H_CBOOSTLISTENER__