#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <map>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

struct Book {
    int id;
    std::string title;
    std::string author;
};

class BookService {
public:
    explicit BookService(Pistache::Address addr);
    void init(size_t thr = 2);
    void start();
    void shutdown();

private:
    void setupRoutes();
    void createBook(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void getBook(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void deleteBook(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void updateBook(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void loadBooks();
    void saveBooks();

    std::map<int, Book> books_;
    Pistache::Http::Endpoint httpEndpoint_;
    Pistache::Rest::Router router_;
};

#endif

