//
// Created by DANG BA MINH on 14/5/25.
//

#ifndef SERVER_H
#define SERVER_H
class Server {
    int port;
    int socket_fd;
public:
    explicit Server(int port);
    auto start() -> void;
    auto stop() -> void;
};
#endif //SERVER_H
