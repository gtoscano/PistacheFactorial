// main.cpp

#include "factorial.h"

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));

    FactorialService fact_service(addr);
    fact_service.init();
    fact_service.start();

    getchar(); // Wait for input to stop the server

    fact_service.shutdown();

    return 0;
}

