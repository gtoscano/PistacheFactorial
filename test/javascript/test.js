// How to run it:
// 1. npm install node-fetch@2.6.6
// 2. run npm install node-fetch

// GetBook
(async () => {
    const fetch = (await import('node-fetch')).default;

    // GetBook
    let response = await fetch("http://localhost:9080/book/1");
    console.assert(response.status === 200, "Status does not match");
    let book = await response.json();
    console.assert(book.author === "Author1", "Author does not match");
    console.assert(book.id === 1, "ID does not match");
    console.assert(book.title === "Title1", "Title does not match");
    console.log("Get");

    // CreateBook
    let newBook = {
      id: 3,
      title: "New Title",
      author: "New Author"
    };

    response = await fetch("http://localhost:9080/book/", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(newBook),
    });

    console.assert(response.status === 200, "Status does not match");
    let message = await response.json();
    console.assert(message.message === "Book created successfully", "Unexpected message");

    // UpdateBook
    let updatedBook = {
      title: "Updated Title",
      author: "Updated Author"
    };

    response = await fetch("http://localhost:9080/book/3", {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(updatedBook),
    });

    console.assert(response.status === 200, "Status does not match");
    message = await response.json();
    console.assert(message.message === "Book updated successfully", "Unexpected message");

    // DeleteBook
    response = await fetch("http://localhost:9080/book/3", {
      method: "DELETE",
    });

    console.assert(response.status === 200, "Status does not match");
    message = await response.json();
    console.assert(message.message === "Book deleted successfully", "Unexpected message");
})();

