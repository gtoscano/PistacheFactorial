#include "factorial.h"
#include <nlohmann/json.hpp>
#include <fstream>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for(int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

FactorialService::FactorialService(Pistache::Address addr)
    : httpEndpoint_(addr) {
        //add whatever you want to initialize here
}

void FactorialService::init(size_t thr) {
    auto opts = Pistache::Http::Endpoint::options()
        .threads(static_cast<int>(thr));
    httpEndpoint_.init(opts);
    setupRoutes();
}

void FactorialService::start() {
    httpEndpoint_.setHandler(router_.handler());
    httpEndpoint_.serveThreaded();
}

void FactorialService::shutdown() {
    httpEndpoint_.shutdown();
    //add what ever you want to finalize
}

void FactorialService::setupRoutes() {
    using namespace Pistache::Rest;
    Routes::Get(router_, "/factorial/:id", Routes::bind(&FactorialService::getFactorial, this));
}

void FactorialService::getFactorial(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    // Implement this
    auto n = request.param(":id").as<int>();
    auto result = factorial(n);

    nlohmann::json j;
    j["factorial"] = result;

    response.send(Pistache::Http::Code::Ok, j.dump());
}

