#include <iostream>
#include "asio.hpp"

// Make sure this runs fine
int main() {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.wait();
    std::cout << "5 seconds elapsed." << '\n';
    std::cout << "Hello, World!" << '\n';
    std::cout << "This is a guide on making tea" <<'\n';
    return 0;
}
