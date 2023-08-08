% Get a book
getBookEndpoint = 'http://localhost:9080/book/1';
[status, output] = system(sprintf('curl -s -X GET %s', getBookEndpoint));
disp('Get a Book');
disp(output);

% Add a book
addBookEndpoint = 'http://localhost:9080/book';
newBook = '{"id": 3, "title": "New Title", "author": "New Author"}';
[status, output] = system(sprintf('curl -s -X POST -H "Content-Type: application/json" -d ''%s'' %s', newBook, addBookEndpoint));
disp('Add a Book');
disp(output);


% Update a book
updateBookEndpoint = 'http://localhost:9080/book/3';
updatedBook = '{"id": 1, "title": "Updated Title", "author": "Updated Author"}';
[status, output] = system(sprintf('curl -s -X PUT -H "Content-Type: application/json" -d ''%s'' %s', updatedBook, updateBookEndpoint));
disp('Update a Book');
disp(output)

% Delete a book
deleteBookEndpoint = 'http://localhost:9080/book/3';
[status, output] = system(sprintf('curl -s -X DELETE %s', deleteBookEndpoint));
disp('Delete a Book');
disp(output)

