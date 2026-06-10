#ifndef SERVER_H
#define SERVER_H
#include "asio.hpp"
#include "UserConnection.h"

class Server {
private:
    asio::io_context &io_context_;
    asio::ip::tcp::acceptor acceptor_;
    void start_accept();
    void handle_accept(UserConnection::pointer new_connection, const std::error_code& error);
public:
    explicit Server(asio::io_context &io_context);
};



#endif //SERVER_H
