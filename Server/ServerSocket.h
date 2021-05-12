//
// Created by omrizaiman on 12/05/2021.
//

#ifndef SERVER_SERVERSOCKET_H
#define SERVER_SERVERSOCKET_H

#include "Socket.h"

class ServerSocket : private Socket
{
public:
    explicit ServerSocket(int port);
    ServerSocket(){};
    virtual ~ServerSocket();

    const ServerSocket& operator << (const std::string&) const;
    const ServerSocket& operator >> (std::string&) const;
    const ServerSocket& operator >> (vector<byte>& vec) const;

    void accept (ServerSocket&);
};

#endif //SERVER_SERVERSOCKET_H
