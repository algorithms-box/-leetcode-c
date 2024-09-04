#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// 简单的 HTTP 响应
const char *http_response =
    "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, "
    "World!</h1></body></html>";

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, sizeof(buffer));

    // 发送 HTTP 响应
    write(client_socket, http_response, strlen(http_response));
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 创建 socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Could not create socket");
        return 1;
    }

    // 设置 socket 选项
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        return 1;
    }

    // 绑定 socket 到端口
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // 监听端口
    if (listen(server_socket, 10) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Listening on port %d...\n", PORT);

    // 接受连接
    while (1) {
        client_socket =
            accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            return 1;
        }

        // 处理请求
        handle_request(client_socket);
    }

    close(server_socket);
    return 0;
}