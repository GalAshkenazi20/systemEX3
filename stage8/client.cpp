#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9034);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }
    
    std::string cmd;
    char buffer[1024];
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, cmd);
        if (cmd == "quit") break;
        cmd += "\n";
        send(sock, cmd.c_str(), cmd.size(), 0);
        int bytes = read(sock, buffer, sizeof(buffer) - 1);
        if (bytes > 0) {
            buffer[bytes] = 0;
            std::cout << buffer;
        }
    }
    close(sock);
    return 0;
}
