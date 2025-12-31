#define ASIO_STANDALONE
#include <asio.hpp>
#include <iostream>

int main() {
    asio::io_context io;
    std::cout << "Asio works!\n";
}

