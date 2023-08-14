#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <string>
#include <map>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

struct Factorial {
    unsigned long long fact;
};

class FactorialService {
public:
    explicit FactorialService(Pistache::Address addr);
    void init(size_t thr = 2);
    void start();
    void shutdown();

private:
    void setupRoutes();
    void getFactorial(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    Pistache::Http::Endpoint httpEndpoint_;
    Pistache::Rest::Router router_;
};

#endif

