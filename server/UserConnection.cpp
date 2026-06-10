#include "UserConnection.h"

using asio::ip::tcp;
UserConnection::UserConnection(asio::io_context &io_context) : socket_(io_context) {}

void UserConnection::start() {
    message_ = "Hello";
    asio::async_write(socket_, asio::buffer(message_), std::bind(&UserConnection::handle_write, shared_from_this(),
                      asio::placeholders::error, asio::placeholders::bytes_transferred));
}

