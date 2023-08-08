import requests
import json
import unittest

class TestBookService(unittest.TestCase):

    def test_get_book(self):
        r = requests.get("http://localhost:9080/book/1")
        self.assertEqual(r.status_code, 200)

        book = r.json()
        self.assertEqual(book["author"], "Author1")
        self.assertEqual(book["id"], 1)
        self.assertEqual(book["title"], "Title1")

    def test_create_book(self):
        new_book = {
            "id": 3,
            "title": "Como respirar mejor",
            "author": "Gabriel Garcia Marquez"
        }

        headers = {"Content-Type": "application/json"}
        r = requests.post("http://localhost:9080/book/", headers=headers, data=json.dumps(new_book))
        print(r)
        self.assertEqual(r.status_code, 200)

        response_message = r.json()
        self.assertEqual(response_message["message"], "Book created successfully")

    def test_update_book(self):
        updated_book = {
            "title": "Updated Title test",
            "author": "Updated Author test"
        }

        headers = {"Content-Type": "application/json"}
        r = requests.put("http://localhost:9080/book/3", headers=headers, data=updated_book)
        print (r)
        self.assertEqual(r.status_code, 200)

        response_message = r.json()
        self.assertEqual(response_message["message"], "Book updated successfully")

    def test_delete_book(self):
        r = requests.delete("http://localhost:9080/book/3")
        self.assertEqual(r.status_code, 200)

if __name__ == "__main__":
    unittest.main()
