# PistacheFactorial
This project leverages C++ and the RESTful-compatible Pistache framework to compute a simple factorial of a number. 

By building a server with Pistache, the clients can seamlessly communicate with the core C++ code, saving development time and ensuring uniformity across different language clients. This example acts as a practical guide for those interested in exploring the capabilities of Pistache, making it an excellent choice for developers aiming to work across multiple languages.

As a developer with a primary focus on C++, it's crucial to make the code accessible to various programming languages. Pistache, a modern and elegant HTTP and REST framework for C++, serves as the backbone of this project, enhancing its cross-language compatibility. By utilizing Pistache, we can develop a server in C++ that efficiently interacts with client codes written in various languages. This means that even though the server logic is implemented in C++, there are no barriers for users who want to consume it using different languages. This approach minimizes development time and ensures consistency across different language clients. 

## Introduction to Pistache

Pistache is a modern and elegant C++ REST framework, playing a central role in this project. It enables the factorial functionality to be consumed over HTTP and provides client implementations for various languages, including C#, Go, Java, JavaScript, Julia, Octave, Python, R, and Rust.
Why Use Pistache in This Project?

####  Web Accessibility with Multi-Language Clients: 
Pistache not only allows the C++ code to be accessed over the web but also provides ready-to-use client implementations for different programming languages, enhancing accessibility across various platforms.
####  C++ Native Development: 
Enables developers to work within a familiar C++ environment, leveraging its performance and efficiency.
####  Ease of Integration: 
Facilitates integration into existing or new C++ projects, providing a seamless way to add web accessibility.


## Why Call C++ Code from other Programming languages 
C++ is known for its high performance and efficiency, making it a preferred choice for computational tasks. However, integrating C++ code with other platforms and languages can be challenging. This is where tools like SWIG, Pistache, and third-party API frameworks come into play.

#### Using Pistache for RESTful API
- **Web Accessibility**: By wrapping C++ code in a RESTful API, Pistache allows the functionality to be accessed over the web, expanding its reach to web and mobile applications.
- **Language Independence**: Any platform that understands HTTP can interact with the C++ code, making it more versatile and widely usable.
- **Integration with Existing Systems**: Easily fits into web-based ecosystems, enabling C++ code to be part of modern web architectures.
- For RESTful client codes, please check: https://github.com/gtoscano/RestFactorialClients (it has examples in c++, c#, golang, java, julia, octave, python, R, and rust)


#### Using SWIG
- **Cross-Language Compatibility**: SWIG allows you to call C++ code from various programming languages, providing a seamless bridge between C++ and languages like Python, Java, and more.
- **Consistent Interfaces**: By generating uniform interfaces, SWIG ensures that the C++ functionality behaves consistently across different languages.
- **Development Efficiency**: Reduces the need to write redundant code for each language, saving time and effort.
- For a SWIG example, please check: https://github.com/gtoscano/SwigFactorial 


#### Using a third-party RESTful framework (i.e. FastAPI, Django)
- **Modern Web Framework**: FastAPI or Django provide a Pythonic way to call C++ code, offering modern features like type checking and automatic documentation.
- **Performance with Ease**: Combines the performance advantages of C++ with the ease and flexibility of Python, providing an efficient yet developer-friendly approach.
- **Rapid Development**: Enables quick prototyping and development, leveraging C++ for computational tasks while using Python for web handling.
- **FastAPIFactorial**: A FastAPI implementation that provides an endpoint to calculate the factorial of a given number. The project can be found [here](https://github.com/gtoscano/FastAPIFactorial).

- **DjangoFactorial**: A Django implementation using the Django REST Framework to provide a similar factorial calculation endpoint. The project can be found [here](https://github.com/gtoscano/DjangoFactorial).

- For **RESTful client codes**: Implementation of RESTful clients in several programming languages can be din [here][https://github.com/gtoscano/RestFactorialClients). Such a project has examples in c++, c#, golang, java, julia, octave, python, R, and rust.

#### Conclusion
The choice between SWIG, Pistache, and any different-language-framework depends on the specific needs and context of your project:
- For cross-language integration within traditional programming environments, SWIG may be the best choice.
- If you need to expose C++ functionality over the web and prefer a C++-based solution, Pistache provides an effective approach.
- For projects that want to leverage a modern Python web framework alongside C++, FastAPI, or Django offer a compelling option.

Each approach bridges the gap between the powerful computational capabilities of C++ and various platforms and languages, allowing developers to harness C++ efficiency while enjoying the benefits of broader accessibility and integration.


# Test using curl

```sh
curl http://localhost:8000/factorial/5

```

# Test using Python
```
import requests
import json

# The base URL of your API
url = "http://localhost:8000"

response = requests.get(f"{url}/factorial/5")
print("Factorial(5): ", response.text)
```
