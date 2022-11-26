#pragma once

#ifndef __H_CPPSERV__
#define __H_CPPSERV__

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <string>
#include <deque>
#include <functional>
#include <memory>
#include <algorithm>
#include <iostream>

namespace __N_CPPSERV__
{
    namespace beast = boost::beast;         // from <boost/beast.hpp>
    namespace http = beast::http;           // from <boost/beast/http.hpp>
    namespace net = boost::asio;            // from <boost/asio.hpp>
    using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

    // Report a failure
    inline void fail(beast::error_code ec, char const* what)
    {
        std::cerr << what << ": " << ec.message() << "\n";
    }

    //******************************************************************************************
    // PACKET

    typedef struct _field
    {
        std::string name{};
        std::string value{};
        _field(std::string n, std::string v) : name{ n }, value{ v } {}
    } FIELD, * LPFIELD, ** LPPFIELD;

    typedef struct _packet
    {
        std::deque<FIELD> fields;
        std::string body;

        std::string field(std::string name) const noexcept
        {
            auto l_it = std::find_if(this->fields.begin(), this->fields.end(), [name] (const FIELD& field) { return !field.name.compare(name); });
            if (l_it == this->fields.end())
                return std::string{};
            
            return l_it->value;
        }

        void field(std::string name, std::string value) noexcept
        {
            auto l_it = std::find_if(this->fields.begin(), this->fields.end(), [name] (const FIELD& field) { return !field.name.compare(name); });
            if (l_it == this->fields.end())
                this->fields.push_back(FIELD{ name, value });
            else
                l_it->value.assign(value);
        }
    } PACKET, * LPPACKET, ** LPPPACKET;

    //******************************************************************************************
    // REQUEST

    typedef enum class _request_header_method
    {
        METHOD_NA, METHOD_GET, METHOD_HEAD, METHOD_POST, METHOD_PUT, METHOD_DELETE, METHOD_CONNECT, METHOD_OPTIONS, METHOD_TRACE, METHOD_PATCH
    } REQUEST_HEADER_METHOD;

    typedef struct _request : public _packet
    {
        REQUEST_HEADER_METHOD method{ REQUEST_HEADER_METHOD::METHOD_NA };
        std::string target;
    } REQUEST, * LPREQUEST, ** LPPREQUEST;

    //******************************************************************************************
    // RESPONSE

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

    typedef struct _response : public _packet
    {
        RESPONSE_HEADER_STATUS status{ RESPONSE_HEADER_STATUS::CODE_NA };
    } RESPONSE, * LPRESPONSE, ** LPPRESPONSE;

    //******************************************************************************************
    // CALLBACK

    using LAMBDA = std::function<bool(REQUEST&, RESPONSE&)>;

    //******************************************************************************************
    // ROUTER

    typedef struct _router
    {
        std::string route{};
        LAMBDA controller{};
        LAMBDA middleware{};

        bool run(REQUEST& request, RESPONSE& response) noexcept
        {
            if (!std::strcmp(this->route.c_str(), request.target.c_str()))
                if (this->middleware(request, response))
                    return this->controller(request, response);

            return false;
        }
    } ROUTER, * LPROUTER, ** LPPROUTER;

    //******************************************************************************************
    // HANDLER

    REQUEST_HEADER_METHOD getMethod(const http::verb method) noexcept
    {
        switch (method)
        {
            case http::verb::get        : return  REQUEST_HEADER_METHOD::METHOD_GET;
            case http::verb::head       : return  REQUEST_HEADER_METHOD::METHOD_HEAD;
            case http::verb::post       : return  REQUEST_HEADER_METHOD::METHOD_POST;
            case http::verb::put        : return  REQUEST_HEADER_METHOD::METHOD_PUT;
            case http::verb::delete_    : return  REQUEST_HEADER_METHOD::METHOD_DELETE;
            case http::verb::connect    : return  REQUEST_HEADER_METHOD::METHOD_CONNECT;
            case http::verb::options    : return  REQUEST_HEADER_METHOD::METHOD_OPTIONS;
            case http::verb::trace      : return  REQUEST_HEADER_METHOD::METHOD_TRACE;
            case http::verb::patch      : return  REQUEST_HEADER_METHOD::METHOD_PATCH;
        }

        return REQUEST_HEADER_METHOD::METHOD_NA;
    }

    REQUEST getRequest(http::request<http::string_body> request)
    {
        __N_CPPSERV__::REQUEST l_request{};
        l_request.method = getMethod(request.method());
        l_request.target.assign(request.target().data(), request.target().size());
        l_request.body.assign(request.body().data(), request.body().size());

        return l_request;
    }

    http::response<http::string_body> getResponse(RESPONSE response, http::request<http::string_body> request)
    {
        http::response<http::string_body> l_response{ (http::status)response.status, request.version() };
        l_response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        l_response.set(http::field::content_type, response.field("content-type"));
        l_response.body().assign(response.body);
        l_response.keep_alive(request.keep_alive());
        l_response.content_length(response.body.size());
        l_response.prepare_payload();

        return l_response;
    }

    // This function produces an HTTP response for the given
    // request. The type of the response object depends on the
    // contents of the request, so the interface requires the
    // caller to pass a generic lambda for receiving the response.
    template<typename Body, typename Allocator, typename Send>
    inline void handle_request(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send, std::deque<ROUTER> routers)
    {
        // Returns a bad request response
        auto const bad_request =
        [&req](beast::string_view why)
        {
            http::response<http::string_body> res{ http::status::bad_request, req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = std::string(why);
            res.prepare_payload();
            return res;
        };

        // Returns a not found response
        auto const not_found =
        [&req](beast::string_view target)
        {
            http::response<http::string_body> res{ http::status::not_found, req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = "The resource '" + std::string(target) + "' was not found.";
            res.prepare_payload();
            return res;
        };

        // Returns a server error response
        auto const server_error =
        [&req](beast::string_view what)
        {
            http::response<http::string_body> res{ http::status::internal_server_error, req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = "An error occurred: '" + std::string(what) + "'";
            res.prepare_payload();
            return res;
        };

        // Make sure we can handle the method
        //if (req.method() != http::verb::get &&
        //    req.method() != http::verb::head)
        //    return send(bad_request("Unknown HTTP-method"));

        // Request path must be absolute and not contain "..".
        if (req.target().empty() ||
            req.target()[0] != '/' ||
            req.target().find("..") != beast::string_view::npos)
            return send(bad_request("Illegal request-target"));

        //// Attempt to open the file
        //beast::error_code ec;
//
        //// Handle the case where the file doesn't exist
        //if (ec == beast::errc::no_such_file_or_directory)
        //    return send(not_found(req.target()));
//
        //// Handle an unknown error
        //if (ec)
        //    return send(server_error(ec.message()));
//
        //// Cache the size since we need it after the move
        //auto const size = body.size();

        REQUEST l_request = getRequest(req);
        RESPONSE l_response{};
        auto l_router = routers.begin();
        for (l_router; l_router != routers.end(); l_router++)
            if (l_router->run(l_request, l_response))
            {
                std::cout << l_response.body << std::endl;

                http::response<http::string_body>l_res = getResponse(l_response, req);

                // Respond to HEAD request
                //if (req.method() == http::verb::head)
                //{
                //    http::response<http::empty_body> res{http::status::ok, req.version()};
                //    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
                //    res.set(http::field::content_type, mime_type(path));
                //    //res.content_length(size);
                //    res.keep_alive(req.keep_alive());
                //    return send(std::move(res));
                //}

                // Respond to GET request
                //http::response<http::file_body> res {
                //    std::piecewise_construct,
                //    std::make_tuple(std::move(body)),
                //    std::make_tuple(http::status::ok, req.version())};

                send(std::move(l_res));
                break;
            }

        if (l_router == routers.end())
            return send(not_found(std::string{ req.target() }));
    }

    //******************************************************************************************
    // SESSION

    // Handles an HTTP server connection
    typedef struct _session : public std::enable_shared_from_this<_session>
    {
        // This is the C++11 equivalent of a generic lambda.
        // The function object is used to send an HTTP message.
        struct send_lambda
        {
            _session& self_;

            explicit send_lambda(_session& self) : self_(self) {}

            template<bool isRequest, class Body, class Fields>
            void operator () (http::message<isRequest, Body, Fields>&& msg) const
            {
                // The lifetime of the message has to extend
                // for the duration of the async operation so
                // we use a shared_ptr to manage it.
                auto sp = std::make_shared<http::message<isRequest, Body, Fields>>(std::move(msg));

                // Store a type-erased version of the shared
                // pointer in the class to keep it alive.
                self_.res_ = sp;

                // Write the response
                http::async_write(
                    self_.stream_, 
                    *sp, beast::bind_front_handler(
                        &_session::on_write,
                        self_.shared_from_this(),
                        sp->need_eof()));
            }
        };

        beast::tcp_stream stream_;
        beast::flat_buffer buffer_;
        http::request<http::string_body> req_;
        std::shared_ptr<void> res_;
        send_lambda lambda_;

        std::deque<ROUTER> m_routers{};

    public:
        // Take ownership of the stream
        _session(tcp::socket&& socket, std::deque<ROUTER> routers) : stream_(std::move(socket)), lambda_(*this), m_routers{ routers } {}

    
    // Start the asynchronous operation
    void run()
    {
        do_read();
    }

    void do_read()
    {
        // Make the request empty before reading,
        // otherwise the operation behavior is undefined.
        req_ = {};

        // Set the timeout.
        stream_.expires_after(std::chrono::seconds(30));

        // Read a request
        http::async_read(stream_, buffer_, req_,
            beast::bind_front_handler(
                &_session::on_read,
                shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        // This means they closed the connection
        if (ec == http::error::end_of_stream)
            return do_close();

        if (ec)
            return fail(ec, "read");

        // Send the response
        handle_request(std::move(req_), lambda_, this->m_routers);
    }

    void on_write(bool close, beast::error_code ec, std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");

        if (close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            return do_close();
        }

        // We're done with the response so delete it
        res_ = nullptr;

        // Read another request
        do_read();
    }

    void do_close()
    {
        // Send a TCP shutdown
        beast::error_code ec;
        stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }
    } SESSION, * LPSESSION, ** LPPSESSION;

    //******************************************************************************************
    // LISTENER

    typedef struct _listener : public std::enable_shared_from_this<_listener>
    {
        std::string m_address{ "0.0.0.0" };
        unsigned short m_port{ 8080 };
        unsigned short m_thread_num { 5 };

        std::deque<ROUTER> m_routers{};
        
        net::io_context m_ioc;
        tcp::acceptor m_acceptor;

        _listener(std::string address, unsigned short port, unsigned short thread_num, std::deque<ROUTER> routers)
        : m_ioc{ std::max<int>(1, thread_num) }, m_acceptor{ net::make_strand(this->m_ioc) }, m_address{ address }, m_port{ port }, m_thread_num{ thread_num }, m_routers{ routers }
        {            
            beast::error_code ec;
    
            this->m_thread_num = std::max<int>(1, thread_num);
            tcp::endpoint endpoint = tcp::endpoint{ net::ip::make_address(address), port };
    
            // Open the acceptor
            this->m_acceptor.open(endpoint.protocol(), ec);
            if (ec)
            {
                fail(ec, "open");
                return;
            }
    
            // Allow address reuse
            this->m_acceptor.set_option(net::socket_base::reuse_address(true), ec);
            if (ec)
            {
                fail(ec, "set_option");
                return;
            }
    
            // Bind to the server address
            this->m_acceptor.bind(endpoint, ec);
            if (ec)
            {
                fail(ec, "bind");
                return;
            }
    
            // Start listening for connections
            this->m_acceptor.listen(net::socket_base::max_listen_connections, ec);
            if (ec)
            {
                fail(ec, "listen");
                return;
            }
        }
    
        void listen() noexcept
        {
            do_accept();
    
            // Run the I/O service on the requested number of threads
            std::vector<std::thread> v;
            v.reserve(this->m_thread_num - 1);
            for(auto i = this->m_thread_num - 1; i > 0; --i)
                v.emplace_back([this] { this->m_ioc.run(); });
    
            this->m_ioc.run();
        }
    
        void do_accept()
        {
            // The new connection gets its own strand
            this->m_acceptor.async_accept(net::make_strand(this->m_ioc), beast::bind_front_handler(&_listener::on_accept, shared_from_this()));
        }
    
        void on_accept(beast::error_code ec, tcp::socket socket)
        {
            if (ec)
            {
                fail(ec, "accept");
            }
            else
            {
                // Create the session and run it
                std::make_shared<SESSION>(std::move(socket), this->m_routers)->run();
            }
    
            // Accept another connection
            do_accept();
        }
    } LISTENER, * LPLISTENER, ** LPPLISTENER;

    //******************************************************************************************
    // SERVER
    
    typedef struct _server
    {
        std::deque<__N_CPPSERV__::ROUTER> routers{};

        bool run() const noexcept
        {            
            std::string address = "0.0.0.0";
            unsigned short port = 8080;
            unsigned short threads = 5;

            // Create and launch a listening port
           std::make_shared<LISTENER>(address, port, threads, this->routers)->listen();

            return true;
        }
    } SERVER, * LPSERVER, ** LPPSERVER;

} // !__N_CPPSERV__

#endif // !__H_CPPSERV__