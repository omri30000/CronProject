//
// Created by Omri Zaiman on 12/05/2021.
//

#include "ServerSocket.h"

#include <utility>
#include "SocketException.h"

ServerSocket::ServerSocket (std::string ip, int port)
{
    Socket::create();
    Socket::bind (ip, port);
    Socket::listen();
}

ServerSocket::~ServerSocket() = default;

/*
The method is a sending operator to send data to a socket
input: the string to send through the socket
output: a reference to this ClientSocket object
*/
const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
    Socket::send(s);
    return *this;
}

/*
The method is a receiving operator to get data from a socket
input: the string to fill in with data
output: a reference to this ClientSocket object
*/
const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
    if (!Socket::recv(s))
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

/*
The method is a receiving operator to get data from a socket
input: the vector of bytes to fill in with data
output: a reference to this ClientSocket object
*/
const ServerSocket& ServerSocket::operator >> (vector<byte>& vec) const
{
    if (!Socket::recv(vec))
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

/*
When in listening mode, the method is responsible for accepting a new client
input: the new socket to accept
output: none
*/
void ServerSocket::accept (ServerSocket& sock)
{
    Socket::accept(sock);
}