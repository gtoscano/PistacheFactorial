using Test
# main.jl

using Pkg
Pkg.activate("MyProject")  # Activate the environment

using HTTP
using JSON
using Test

# Rest of your code




@testset "BookService" begin
    @testset "GetBook" begin
        r = HTTP.request("GET", "http://localhost:9080/book/1")
        @test HTTP.status(r) == 200

        # Parse the response body as JSON
        json = JSON.parse(String(r.body))

        # Check the values in the JSON
        @test json["author"] == "Author1"
        @test json["id"] == 1
        @test json["title"] == "Title1"
    end

    @testset "CreateBook" begin
        j = Dict("id" => 3, "title" => "New Title", "author" => "New Author")
        r = HTTP.request("POST", "http://localhost:9080/book/", [], JSON.json(j))

        @test HTTP.status(r) == 200

        # Parse the response body as JSON
        json = JSON.parse(String(r.body))

        # Check the values in the JSON
        @test json["message"] == "Book created successfully"
    end


    @testset "UpdateBook" begin
        j = Dict("title" => "Updated Title", "author" => "Updated Author")
        r = HTTP.request("PUT", "http://localhost:9080/book/3", [], JSON.json(j))

        @test HTTP.status(r) == 200

        # Parse the response body as JSON
        json = JSON.parse(String(r.body))

        # Check the values in the JSON
        @test json["message"] == "Book updated successfully"

    end

    @testset "DeleteBook" begin
        r = HTTP.request("DELETE", "http://localhost:9080/book/3")
        @test HTTP.status(r) == 200
        # Parse the response body as JSON
        json = JSON.parse(String(r.body))
        # The response body is expected to be empty for a DELETE request
        @test json["message"] == "Book deleted successfully"

        #@test isempty(String(r.body))
    end
end