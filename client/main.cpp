#include <iostream>
#include "asio.hpp"
#include "asio/ip/address.hpp"
#include "asio/impl/read.hpp"

// Use port 1024 and localhost IP
#define PORT 1024
#define IP_ADDR "127.0.0.1"
#define MAX_BUFFER_SIZE 512

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
        const asio::ip::address server_address = asio::ip::make_address(IP_ADDR);
        const asio::ip::tcp::endpoint server_endpoint(server_address, PORT);

        client_socket.connect(server_endpoint);
        std::cout << "Successfully connected to the server!" << '\n';

        while (1) {
            // Read user input into buffer
            std::cout << "Enter message to the server: ";
            char buffer[MAX_BUFFER_SIZE];
            std::cin.getline(buffer, 512);

            std::error_code error_code;
            size_t send_to_server = asio::write(client_socket, asio::buffer(buffer, MAX_BUFFER_SIZE));

            // Wait for response from server
            char server_buffer[MAX_BUFFER_SIZE];
            size_t received_message =  client_socket.read_some(asio::buffer(server_buffer, MAX_BUFFER_SIZE), error_code);

            // Check if the server has closed the connection or not
            if (error_code == asio::error::eof) {
                break;
            }
            // other error
            else if (error_code) {
                throw std::system_error(error_code);
            }

            server_buffer[received_message] = '\0';

            std::cout << "Server Response: " << server_buffer << '\n';
        }
    }

    catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
