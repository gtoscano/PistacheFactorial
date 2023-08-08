using HTTP
using JSON

function get_book(id::Int)
    response = HTTP.get("http://localhost:9080/book/$id")
    if HTTP.status(response) == 200
        return JSON.parse(String(response.body))
    else
        error("Failed to get book: HTTP $(HTTP.status(response))")
    end
end

function main()
    book = get_book(1)
    println(book)
end

main()
