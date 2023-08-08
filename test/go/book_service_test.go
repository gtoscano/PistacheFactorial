package main

// go test
import (
	"bytes"
	"encoding/json"
	"io/ioutil"
	"net/http"
	"testing"
)

type Book struct {
	ID     int    `json:"id"`
	Title  string `json:"title"`
	Author string `json:"author"`
}

func TestGetBook(t *testing.T) {
	resp, err := http.Get("http://localhost:9080/books/1")
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}

	var book Book
	err = json.Unmarshal(body, &book)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}

	if book.Author != "Updated Author" || book.ID != 1 || book.Title != "Updated Title" {
		t.Errorf("Unexpected book data")
	}
}

func TestCreateBook(t *testing.T) {
	book := Book{Title: "New Title", Author: "New Author"}
	jsonBook, _ := json.Marshal(book)

	resp, err := http.Post("http://localhost:9080/books", "application/json", bytes.NewBuffer(jsonBook))
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}

	err = json.Unmarshal(body, &book)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}

	if book.Author != "New Author" || book.Title != "New Title" {
		t.Errorf("Unexpected book data")
	}
}

// Go doesn't have a built-in function for HTTP DELETE,
// so we need to use the http.NewRequest function and http.Client.Do
func TestDeleteBook(t *testing.T) {
	req, err := http.NewRequest("DELETE", "http://localhost:9080/books/1", nil)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != 200 {
		t.Errorf("Unexpected status code")
	}
}

func TestUpdateBook(t *testing.T) {
	book := Book{Title: "Updated Title", Author: "Updated Author"}
	jsonBook, _ := json.Marshal(book)

	req, err := http.NewRequest("PUT", "http://localhost:9080/books/1", bytes.NewBuffer(jsonBook))
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}

	err = json.Unmarshal(body, &book)
	if err != nil {
		t.Fatalf("Unexpected error %s", err)
	}

	if book.Author != "Updated Author" || book.ID != 1 || book.Title != "Updated Title" {
		t.Errorf("Unexpected book data")
	}
}
