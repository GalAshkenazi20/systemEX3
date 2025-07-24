#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>

#define PORT 9034
#define BUFFER_SIZE 1024

class ConvexHullClient {
private:
    int sock;
    struct sockaddr_in serv_addr;
    
public:
    ConvexHullClient() : sock(-1) {
        memset(&serv_addr, 0, sizeof(serv_addr));
    }
    
    ~ConvexHullClient() {
        disconnect();
    }
    
    bool connect() {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cerr << "Socket creation error" << std::endl;
            return false;
        }
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
            return false;
        }
        
        if (::connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << "Connection Failed" << std::endl;
            return false;
        }
        
        std::cout << "Connected to server on port " << PORT << std::endl;
        return true;
    }
    
    void disconnect() {
        if (sock != -1) {
            close(sock);
            sock = -1;
        }
    }
    
    void sendCommand(const std::string& command) {
        std::string commandWithNewline = command + "\n";
        send(sock, commandWithNewline.c_str(), commandWithNewline.length(), 0);
        
        char buffer[BUFFER_SIZE] = {0};
        int bytes_read = read(sock, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            std::cout << "Server response:\n" << buffer << std::endl;
        }
    }
    
    void run() {
        std::string command;
        std::cout << "Enter commands (type 'quit' to exit):" << std::endl;
        std::cout << "Available commands:" << std::endl;
        std::cout << "  Newgraph <n> <x1> <y1> <x2> <y2> ... - Create new graph with n points" << std::endl;
        std::cout << "  Newpoint <x> <y> - Add a new point" << std::endl;
        std::cout << "  Removepoint <x> <y> - Remove a point" << std::endl;
        std::cout << "  CH - Calculate convex hull" << std::endl;
        
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, command);
            
            if (command == "quit" || command == "exit") {
                break;
            }
            
            if (!command.empty()) {
                sendCommand(command);
            }
        }
    }
};

int main() {
    ConvexHullClient client;
    
    if (!client.connect()) {
        return 1;
    }
    
    client.run();
    
    return 0;
}
