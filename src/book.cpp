#include "book.hpp"
#include <nlohmann/json.hpp>
#include <fstream>


BookService::BookService(Pistache::Address addr)
    : httpEndpoint_(addr) {
    loadBooks();
}

void BookService::init(size_t thr) {
    auto opts = Pistache::Http::Endpoint::options()
        .threads(static_cast<int>(thr));
    httpEndpoint_.init(opts);
    setupRoutes();
}

void BookService::start() {
    httpEndpoint_.setHandler(router_.handler());
    httpEndpoint_.serveThreaded();
}

void BookService::shutdown() {
    httpEndpoint_.shutdown();
    saveBooks();
}

void BookService::setupRoutes() {
    using namespace Pistache::Rest;
    Routes::Post(router_, "/book", Routes::bind(&BookService::createBook, this));
    Routes::Get(router_, "/book/:id", Routes::bind(&BookService::getBook, this));
    Routes::Delete(router_, "/book/:id", Routes::bind(&BookService::deleteBook, this));
    Routes::Put(router_, "/book/:id", Routes::bind(&BookService::updateBook, this));
}

void BookService::createBook(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    // Implement this
    auto j = nlohmann::json::parse(request.body());
    Book book;
    book.id = j["id"];
    book.title = j["title"];
    book.author = j["author"];
    
    auto it = books_.find(book.id);
    if (it != books_.end()) {
        response.send(Pistache::Http::Code::Bad_Request, "Book with this ID already exists.\n");
        return;
    }

    books_[book.id] = book;
    
    nlohmann::json res;
    res["message"] = "Book created successfully";
    response.send(Pistache::Http::Code::Ok, res.dump());
}

void BookService::getBook(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    // Implement this
    auto id = request.param(":id").as<int>();

    auto it = books_.find(id);
    if (it == books_.end()) {
        response.send(Pistache::Http::Code::Not_Found, "Book not found.\n");
        return;
    }

    const Book& book = it->second;

    nlohmann::json j;
    j["id"] = book.id;
    j["title"] = book.title;
    j["author"] = book.author;

    response.send(Pistache::Http::Code::Ok, j.dump());
}

void BookService::deleteBook(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    // Implement this
    auto id = request.param(":id").as<int>();

    auto it = books_.find(id);
    if (it == books_.end()) {
        response.send(Pistache::Http::Code::Not_Found, "Book not found.\n");
        return;
    }

    books_.erase(it);
    nlohmann::json res;
    res["message"] = "Book deleted successfully";
    response.send(Pistache::Http::Code::Ok, res.dump());
}

void BookService::updateBook(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    // Implement this
    auto id = request.param(":id").as<int>();

    auto it = books_.find(id);
    if (it == books_.end()) {
        response.send(Pistache::Http::Code::Not_Found, "Book not found.\n");
        return;
    }

    auto j = nlohmann::json::parse(request.body());
    Book& book = it->second;
    book.title = j["title"];
    book.author = j["author"];

    nlohmann::json res;
    res["message"] = "Book updated successfully";
    response.send(Pistache::Http::Code::Ok, res.dump());
}

void BookService::loadBooks() {
    std::ifstream i("books.json");
    if(!i.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }
    nlohmann::json j;
    i >> j;

    for (auto& element : j) {
        int id = element["id"];
        Book book;
        book.id = id;
        book.title = element["title"];
        book.author = element["author"];
        books_[id] = book;
    }
}

void BookService::saveBooks() {
    nlohmann::json j;

    for (const auto& pair : books_) {
        const auto& book = pair.second;
        j.push_back({ {"id", book.id}, {"title", book.title}, {"author", book.author} });
    }

    std::ofstream o("books.json");
    o << j.dump(4);
}

