#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>
#include <string>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class WebSocketServer {
private:
    websocket::stream<tcp::socket>* ws_;  // WebSocket member variable
    net::io_context ioc_;                // io_context for handling async I/O
    tcp::acceptor acceptor_;             // Acceptor for listening to connections
    net::executor_work_guard<net::io_context::executor_type> workGuard_; // Ensures io_context keeps running
    std::thread io_thread_;              // Separate thread for running io_context

public:
    // Constructor
    WebSocketServer() 
        : acceptor_(ioc_, tcp::endpoint(tcp::v4(), 12345)) // Bind to port 12345
        , ws_(nullptr)  // Initialize the WebSocket
        , workGuard_(net::make_work_guard(ioc_))  // Ensures io_context does not exit
    {
        // Launch io_context in a separate thread to avoid locking issues
        io_thread_ = std::thread([this]() {
            ioc_.run();
        });

        try {
            // Accept connection
            tcp::socket socket(ioc_);
            acceptor_.accept(socket);  // Blocking call, waits for connection

            // Allocate WebSocket on the heap
            ws_ = new websocket::stream<tcp::socket>(std::move(socket));

            // Perform WebSocket handshake
            ws_->accept();

            std::cout << "WebSocket server initialized and connected." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error initializing WebSocket: " << e.what() << std::endl;
        }
    }

    ~WebSocketServer() {
        workGuard_.reset(); // Allow io_context to stop
        if (io_thread_.joinable()) {
            io_thread_.join();  // Ensure the io_context thread is joined before destruction
        }
        delete ws_;  // Deallocate the WebSocket
    }

    // Method to send a message through WebSocket
    void sendMessage(const std::string& message) {
        try {
            std::cout << "Sending message: " << message << std::endl;
            ws_->write(net::buffer(message));  // Send message
        } catch (const std::exception& e) {
            std::cerr << "Error sending message: " << e.what() << std::endl;
        }
    }

    // Run the WebSocket server
    //void run() {
    //    while (true) {
    //        std::string msg = "Real-time data from App 1: " + std::to_string(rand() % 100);
    //        sendMessage(msg);
    //        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate real-time data send
    //    }
    //}
};

//int main() {
//    App1WebSocketServer server;
//    server.run();
//
//    return 0;
//}