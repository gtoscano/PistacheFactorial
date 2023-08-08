// main.cpp

#include "book.hpp"

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));

    BookService bookService(addr);
    bookService.init();
    bookService.start();

    getchar(); // Wait for input to stop the server

    bookService.shutdown();

    return 0;
}

