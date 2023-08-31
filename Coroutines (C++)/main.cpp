#include <iostream>
#include <coroutine>
#include <chrono>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <termios.h>
#include <arpa/inet.h>
#include <unistd.h>

struct tcp_awaitable
{
    explicit tcp_awaitable(const int sockfd, const char symbol)
            : sockfd_(sockfd), symbol_(symbol)
    {}

    bool await_ready() const noexcept
    {
        return false;
    }

    void await_resume() noexcept
    {}

    void await_suspend(std::coroutine_handle<> h)
    {
        std::thread m_thread = std::thread([this, h]() mutable {

            if (send(sockfd_, &symbol_, 1, 0) < 0) {
                std::cerr << "Error: Failed to send data to the server." << std::endl;
                close(sockfd_);
                h.resume();
                return;
            }

            // Receive the response from the server
            char response;
            recv(sockfd_, &response, 1, 0);

            // Print the server's response
            std::cout << "Server response: " << response << std::endl;

            h.resume();
        });
        m_thread.detach();
    }

private:
    int sockfd_;
    char symbol_;
};

struct Async
{
    struct Promise
    {
        Async get_return_object() {
            return Async(std::coroutine_handle<Promise>::from_promise(*this));
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
    Async(std::coroutine_handle<Promise> h) : coro(h) {}
    ~Async() {
        if (coro.done()) {
            coro.destroy();
        }
    }
    using promise_type = Promise;
    std::coroutine_handle<Promise> coro;
};

Async task(int sockfd, char input) {
    co_await tcp_awaitable(sockfd, input);
}

int main() {
    std::srand(std::time(nullptr));

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Failed to create socket." << std::endl;
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1234);
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Error: Invalid server address." << std::endl;
        close(sockfd);
        return 1;
    }

    if (connect(sockfd, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Error: Failed to connect to the server." << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Scan started..." << std::endl;
    char c;
    while (std::cin >> c) {
        task(sockfd, c);
    }

    close(sockfd);

    return 0;
}
