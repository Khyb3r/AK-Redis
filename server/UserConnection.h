#ifndef USERCONNECTION_H
#define USERCONNECTION_H
#include <memory>
#include <asio.hpp>
#include <iostream>

class UserConnection : public std::enable_shared_from_this<UserConnection> {
private:
    asio::ip::tcp::socket socket_;
    std::string message_;

    void handle_write(const std::error_code& /*error*/,
      size_t /*bytes_transferred*/) {}

public:
    typedef std::shared_ptr<UserConnection> pointer;

    explicit UserConnection(asio::io_context& io_context);

    static pointer create(asio::io_context& io_context) {
        return std::make_shared<UserConnection>(io_context);
    }

    asio::ip::tcp::socket& socket() {
        return socket_;
    }

    void start();
};


#endif //USERCONNECTION_H
