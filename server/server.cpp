#include "server.h"

class server{

    public:
    server(asio::io_context & io_context) 
    : io_context_(io_context) ,
    acceptor_(io_context, tcp::endpoint(tcp::v4(),1024))
    
    {
        start_accept();
    }

    private:

    void start_accept()
    {
        tcp_connection::pointer new_connection = 
         tcp_connection:: create(io_context_);

        acceptor_.async_accept(new_connection->socket(),
          std::bind(&server::handle_accept,this, new_connection,
               asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection, 
        const std::error_code& error)
    {
        if(!error)
        {
            new_connection->start();
        }

        start_accept();

    }

    
}