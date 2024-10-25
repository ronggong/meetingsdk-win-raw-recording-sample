#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

class TCPServer {
public:
    TCPServer(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        startAccept();
    }

    void startAccept() {
        socket_ = std::make_shared<tcp::socket>(acceptor_.get_executor());

        // Start accepting connections
        acceptor_.async_accept(*socket_, 
            [this](boost::system::error_code ec) {
                if (!ec) {
                    std::cout << "Server: Accepted connection from client\n";
                    startRead();
                }
                startAccept(); // Accept another connection
            });
    }

    void startRead() {
        // Read data from client
        socket_->async_read_some(boost::asio::buffer(data_),
            [this](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Server received: " << std::string(data_, length) << "\n";
                    startRead(); // Continue reading from the client
                }
            });
    }

private:
    tcp::acceptor acceptor_;
    std::shared_ptr<tcp::socket> socket_;
    char data_[1024]; // Buffer for received data
};