use reqwest::Error;
use serde_json::{json, Value};
// cargo run

#[tokio::main]
async fn main() -> Result<(), Error> {

    // GetBook
    let res = reqwest::get("http://localhost:9080/book/1").await?;
    assert_eq!(res.status(), 200);
    let book: Value = res.json().await?;
    assert_eq!(book["author"], "Author1");
    assert_eq!(book["id"], 1);
    assert_eq!(book["title"], "Title1");

    // CreateBook
    let new_book = json!({
        "id": 3,
        "title": "New Title",
        "author": "New Author"
    });
    let client = reqwest::Client::new();
    let res = client.post("http://localhost:9080/book/")
        .json(&new_book)
        .send()
        .await?;
    assert_eq!(res.status(), 200);
    let message: Value = res.json().await?;
    assert_eq!(message["message"], "Book created successfully");

    // UpdateBook
    let updated_book = json!({
        "title": "Updated Title",
        "author": "Updated Author"
    });
    let res = client.put("http://localhost:9080/book/3")
        .json(&updated_book)
        .send()
        .await?;
    assert_eq!(res.status(), 200);
    let message: Value = res.json().await?;
    assert_eq!(message["message"], "Book updated successfully");

    // DeleteBook
    let res = client.delete("http://localhost:9080/book/3")
        .send()
        .await?;
    assert_eq!(res.status(), 200);
    let message: Value = res.json().await?;
    assert_eq!(message["message"], "Book deleted successfully");

    Ok(())
}

