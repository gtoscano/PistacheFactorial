#include <gtest/gtest.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

TEST(BookService, GetBook) {
    auto r = cpr::Get(cpr::Url{"http://localhost:9080/book/1"});
    ASSERT_EQ(r.status_code, 200); // Check status code

    // Parse the response body as JSON
    auto json = nlohmann::json::parse(r.text);
    
    // Check the values in the JSON
    ASSERT_EQ(json["author"], "Author1");
    ASSERT_EQ(json["id"], 1);
    ASSERT_EQ(json["title"], "Title1");
}

TEST(BookService, CreateBook) {
    nlohmann::json j;
    j["title"] = "Como respirar mejor";
    j["id"] = 3;
    j["author"] = "Gabriel Garcia Marquez"; 

    auto r = cpr::Post(cpr::Url{"http://localhost:9080/book/"},
                       cpr::Body{j.dump()},
                       cpr::Header{{"Content-Type", "application/json"}});

    ASSERT_EQ(r.status_code, 200); // Check status code

    // Parse the response body as JSON
    auto json = nlohmann::json::parse(r.text);

    // Check the values in the JSON
    ASSERT_EQ(json["message"], "Book created successfully");
}

TEST(BookService, UpdateBook) {
    nlohmann::json j;
    j["title"] = "Updated Title test";
    j["author"] = "Updated Author test";

    auto r = cpr::Put(cpr::Url{"http://localhost:9080/book/3"},
                      cpr::Body{j.dump()},
                      cpr::Header{{"Content-Type", "application/json"}});

    ASSERT_EQ(r.status_code, 200); // Check status code

    // Parse the response body as JSON
    auto json = nlohmann::json::parse(r.text);


    // Check the values in the JSON
    ASSERT_EQ(json["message"], "Book updated successfully");
}

TEST(BookService, DeleteBook) {
    auto r = cpr::Delete(cpr::Url{"http://localhost:9080/book/3"});
    ASSERT_EQ(r.status_code, 200); // Check status code
}
