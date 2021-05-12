//
// Created by Omri Zaiman on 12/05/2021.
//

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <vector>
#include "SocketException.h"

const int MAXHOSTNAME = 200;
const int MAX_CONNECTIONS = 5;
const int MAXRECV = 6; // 6 bytes - message's size

using std::vector;
using byte = unsigned char;

class Socket
{
public:
    Socket();
    virtual ~Socket();

    // Server initialization
    void create() noexcept(false);
    void bind(int port) noexcept(false);
    void listen() const noexcept(false);
    void accept(Socket&) const noexcept(false);

    // Client initialization
    bool connect (const std::string& host, int port);

    // Data Transmission
    void send ( const std::string& ) const;
    int recv ( std::string& ) const;
    int recv ( vector<byte>& vec ) const;


    void set_non_blocking ( bool ) const;

    [[nodiscard]] bool is_valid() const { return m_sock != -1; }

private:
    const int ERROR_CODE = -1;
    int m_sock;
    sockaddr_in m_addr{};
};

#endif //SERVER_SOCKET_H
