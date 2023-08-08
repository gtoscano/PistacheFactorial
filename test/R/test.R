library(httr)
library(jsonlite)

# Run Rscript test.R

# GetBook
res <- GET("http://localhost:9080/book/1")
stopifnot(status_code(res) == 200)
book <- fromJSON(content(res, "text", encoding = "UTF-8"))
stopifnot(book$author == "Author1")
stopifnot(book$id == 1)
stopifnot(book$title == "Title1")
print("Get: successfully executed")

# CreateBook
new_book <- list(id = 3, title = "New Title", author = "New Author")
res <- POST("http://localhost:9080/book/", body = new_book, add_headers("Content-Type" = "application/json"), encode = "json")
print(res)
stopifnot(status_code(res) == 200)
message <- fromJSON(content(res, "text", encoding = "UTF-8"))
stopifnot(message$message == "Book created successfully")
print("Post: Successfully executed")

# UpdateBook
updated_book <- list(title = "Updated Title", author = "Updated Author")
res <- PUT("http://localhost:9080/book/3", body = updated_book, add_headers("Content-Type" = "application/json"), encode = "json")
stopifnot(status_code(res) == 200)
message <- fromJSON(content(res, "text", encoding = "UTF-8"))
stopifnot(message$message == "Book updated successfully")
print("Update: Successfully executed")


# DeleteBook
res <- DELETE("http://localhost:9080/book/3")
stopifnot(status_code(res) == 200)
message <- fromJSON(content(res, "text", encoding = "UTF-8"))
stopifnot(message$message == "Book deleted successfully")
print("Delete: Successfully executed")

