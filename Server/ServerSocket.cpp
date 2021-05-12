//
// Created by Omri Zaiman on 12/05/2021.
//

#include "ServerSocket.h"
#include "SocketException.h"

ServerSocket::ServerSocket (int port)
{
    Socket::create();
    Socket::bind (port);
    Socket::listen();
}

ServerSocket::~ServerSocket() = default;


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
    Socket::send(s);
    return *this;
}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
    if (!Socket::recv(s))
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

const ServerSocket& ServerSocket::operator >> (vector<byte>& vec) const
{
    if (!Socket::recv(vec))
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

void ServerSocket::accept (ServerSocket& sock)
{
    Socket::accept(sock);
}