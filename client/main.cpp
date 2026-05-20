#include <iostream>
#include "asio.hpp"
#include "asio/ip/address.hpp"

// Use port 1024 and localhost IP
#define PORT 1024
#define IP_ADDR "127.0.0.1"


int main(int argc, char* argv[]) {
    if (argc != 1) {
        std::cerr << "Too many arguments" << '\n';
        return 1;
    }

    try {
        // I/0 context object needed for every application using asio
        asio::io_context io_context;

        // Create TCP socket
        asio::ip::tcp::socket client_socket(io_context);

        // Use IP + PORT to create endpoint object
        asio::ip::address server_address = asio::ip::make_address(IP_ADDR);
        asio::ip::tcp::endpoint server_endpoint(server_address, PORT);

        client_socket.connect(server_endpoint);

    }

    catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
