#include "server.h"

#include "UserConnection.h"

using asio::ip::tcp;

Server::Server(asio::io_context &io_context) :
               io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), 1024)) {
    start_accept();
}

void Server::start_accept() {
    UserConnection::pointer new_connection = UserConnection::create(io_context_);
    acceptor_.async_accept(new_connection->socket(), std::bind(&Server::handle_accept, this,
                                                            new_connection, asio::placeholders::error));
}

void Server::handle_accept(UserConnection::pointer new_connection, const std::error_code& error) {
    if(!error) {
        new_connection->start();
    }
    start_accept();
}