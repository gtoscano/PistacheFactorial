/**
 * @author : gtoscano
 * @created : 2023-08-01
 * javac Main.java
 * java Main
**/
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.http.HttpHeaders;
import org.json.JSONObject;

public class Main {
    public static void main(String[] args) throws Exception {
        HttpClient client = HttpClient.newHttpClient();

        // GetBook
        HttpRequest request = HttpRequest.newBuilder()
                .uri(new URI("http://localhost:9080/book/1"))
                .build();
        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
        if (response.statusCode() != 200) {
            throw new RuntimeException("Expected status code 200");
        }
        JSONObject book = new JSONObject(response.body());
        if (!book.getString("author").equals("Author1") ||
            book.getInt("id") != 1 ||
            !book.getString("title").equals("Title1")) {
            throw new RuntimeException("Book does not match expected values");
        }
        System.out.println("GetBook: Successfully executed");

        // CreateBook
        JSONObject newBook = new JSONObject();
        newBook.put("id", 3);
        newBook.put("title", "New Title");
        newBook.put("author", "New Author");
        request = HttpRequest.newBuilder()
                .uri(new URI("http://localhost:9080/book/"))
                .POST(HttpRequest.BodyPublishers.ofString(newBook.toString()))
                .header("Content-Type", "application/json")
                .build();
        response = client.send(request, HttpResponse.BodyHandlers.ofString());
        if (response.statusCode() != 200) {
            throw new RuntimeException("Expected status code 200");
        }
        JSONObject message = new JSONObject(response.body());
        if (!message.getString("message").equals("Book created successfully")) {
            throw new RuntimeException("Expected message: Book created successfully");
        }
        System.out.println("CreateBook: Successfully executed");

        // ... continue for UpdateBook and DeleteBook
    }
}

