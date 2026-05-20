#include <ctime>
#include <iostream>
#include <string>
#include "asio.hpp"

using asio::ip::tcp;


int main()
{

    try 
    {

        asio::io_context io_context;

        //create server endpoint
        tcp::acceptor acceptor(
            io_context, tcp::endpoint(tcp::v4(), 1024)
        );

        while(true)
        {

            //socket for conntected io context
            tcp::socket socket(io_context);
            std::cout << "waiting for client"<< "\n";


            //wait for the client to connect
            acceptor.accept(socket);
            std::cout << "client has connected :) " << "\n";

            //message to send
            std::string message = "Hello from server\n";

            std::error_code ignored_error;

            asio::write(socket, asio::buffer(message), ignored_error);

            //read client response
            char data[512];

            size_t length = socket.read_some(asio::buffer(data));
            data[length] = '\0';
            std::cout << "client says: " << data << "\n";
            

            std::cout << "message sent" << "\n";

            //socket closes here
        }
    }

    catch(std::exception& e)
    {
        std::cerr <<e.what() <<std::endl;
    }

    return 0;
}