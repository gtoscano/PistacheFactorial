use reqwest::Error;
use serde_json::Value;

#[tokio::main]
async fn main() -> Result<(), Error> {
    let res = reqwest::get("http://localhost:9080/book/2").await?;
    println!("Status: {}", res.status());

    let book: Value = res.json().await?;
    println!("Book: {:?}", book);

    Ok(())
}

