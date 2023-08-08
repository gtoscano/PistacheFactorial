using System;
using System.Net.Http;
using System.Text;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

class Program
{
    static void Main(string[] args)
    {
        var client = new HttpClient();

        // GetBook
        var response = client.GetAsync("http://localhost:9080/book/1").Result;
        if (response.StatusCode != System.Net.HttpStatusCode.OK)
        {
            throw new Exception("Expected status code 200");
        }
        var book = JObject.Parse(response.Content.ReadAsStringAsync().Result);
        if ((string)book["author"] != "Author1" || (int)book["id"] != 1 || (string)book["title"] != "Title1")
        {
            throw new Exception("Book does not match expected values");
        }
        Console.WriteLine("GetBook: Successfully executed");

        // CreateBook
        var newBook = new JObject
        {
            { "id", 3 },
            { "title", "New Title" },
            { "author", "New Author" }
        };
        response = client.PostAsync("http://localhost:9080/book/",
            new StringContent(newBook.ToString(), Encoding.UTF8, "application/json")).Result;
        if (response.StatusCode != System.Net.HttpStatusCode.OK)
        {
            throw new Exception("Expected status code 200");
        }
        var message = JObject.Parse(response.Content.ReadAsStringAsync().Result);
        if ((string)message["message"] != "Book created successfully")
        {
            throw new Exception("Expected message: Book created successfully");
        }
        Console.WriteLine("CreateBook: Successfully executed");

        // UpdateBook
        var updatedBook = new JObject
        {
            { "title", "Updated Title" },
            { "author", "Updated Author" }
        };
        var request = new HttpRequestMessage
        {
            Method = HttpMethod.Put,
            RequestUri = new Uri("http://localhost:9080/book/3"),
            Content = new StringContent(updatedBook.ToString(), Encoding.UTF8, "application/json")
        };
        response = client.SendAsync(request).Result;
        if (response.StatusCode != System.Net.HttpStatusCode.OK)
        {
            throw new Exception("Expected status code 200");
        }
        message = JObject.Parse(response.Content.ReadAsStringAsync().Result);
        if ((string)message["message"] != "Book updated successfully")
        {
            throw new Exception("Expected message: Book updated successfully");
        }
        Console.WriteLine("UpdateBook: Successfully executed");

        // DeleteBook
        response = client.DeleteAsync("http://localhost:9080/book/3").Result;
        if (response.StatusCode != System.Net.HttpStatusCode.OK)
        {
            throw new Exception("Expected status code 200");
        }
        message = JObject.Parse(response.Content.ReadAsStringAsync().Result);
        if ((string)message["message"] != "Book deleted successfully")
        {
            throw new Exception("Expected message: Book deleted successfully");
        }
        Console.WriteLine("DeleteBook: Successfully executed");
    }
}

