package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
)

type Book struct {
	ID     int    `json:"id"`
	Title  string `json:"title"`
	Author string `json:"author"`
}

type Message struct {
	Message string `json:"message"`
}

func main() {
	// GetBook
	resp, err := http.Get("http://localhost:9080/book/1")
	if err != nil {
		panic(err)
	}
	if resp.StatusCode != 200 {
		panic("Expected status code 200")
	}
	body, _ := ioutil.ReadAll(resp.Body)
	var book Book
	json.Unmarshal(body, &book)
	if book.Author != "Author1" || book.ID != 1 || book.Title != "Title1" {
		panic("Book does not match expected values")
	}
	fmt.Println("GetBook: Successfully executed")

	// CreateBook
	newBook := Book{ID: 3, Title: "New Title", Author: "New Author"}
	jsonBook, _ := json.Marshal(newBook)
	resp, err = http.Post("http://localhost:9080/book/", "application/json", bytes.NewBuffer(jsonBook))
	if err != nil {
		panic(err)
	}
	if resp.StatusCode != 200 {
		panic("Expected status code 200")
	}
	body, _ = ioutil.ReadAll(resp.Body)
	var message Message
	json.Unmarshal(body, &message)
	if message.Message != "Book created successfully" {
		panic("Expected message: Book created successfully")
	}
	fmt.Println("CreateBook: Successfully executed")

	// UpdateBook
	updatedBook := Book{Title: "Updated Title", Author: "Updated Author"}
	jsonBook, _ = json.Marshal(updatedBook)
	client := &http.Client{}
	req, _ := http.NewRequest(http.MethodPut, "http://localhost:9080/book/3", bytes.NewBuffer(jsonBook))
	req.Header.Set("Content-Type", "application/json")
	resp, err = client.Do(req)
	if err != nil {
		panic(err)
	}
	if resp.StatusCode != 200 {
		panic("Expected status code 200")
	}
	body, _ = ioutil.ReadAll(resp.Body)
	json.Unmarshal(body, &message)
	if message.Message != "Book updated successfully" {
		panic("Expected message: Book updated successfully")
	}
	fmt.Println("UpdateBook: Successfully executed")

	// DeleteBook
	req, _ = http.NewRequest(http.MethodDelete, "http://localhost:9080/book/3", nil)
	resp, err = client.Do(req)
	if err != nil {
		panic(err)
	}
	if resp.StatusCode != 200 {
		panic("Expected status code 200")
	}
	body, _ = ioutil.ReadAll(resp.Body)
	json.Unmarshal(body, &message)
	if message.Message != "Book deleted successfully" {
		panic("Expected message: Book deleted successfully")
	}
	fmt.Println("DeleteBook: Successfully executed")
}
