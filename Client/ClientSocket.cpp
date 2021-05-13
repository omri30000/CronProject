//
// Created by Omri Zaiman on 12/05/2021.
//

#include "ClientSocket.h"
#include "SocketException.h"

/*
A constructor of a ClientSocket object. It creates a new socket and bind it
input: the ip and port of the server
output: a new object of ClientSocket class (a conversation socket)
*/
ClientSocket::ClientSocket ( std::string host, int port )
{
    Socket::create();
    Socket::connect (host, port);
}

/*
The method is a sending operator to send data to a socket
input: the vector of bytes to send through the socket
output: a reference to this ClientSocket object
*/
const ClientSocket& ClientSocket::operator << ( const vector<byte>& vec ) const
{
    Socket::send (vec);
    return *this;
}

/*
The method is a sending operator to send data to a socket
input: the string to send through the socket
output: a reference to this ClientSocket object
*/
const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    Socket::send ( s );
    return *this;
}

/*
The method is a receiving operator to get data from a socket
input: the string to fill in with data
output: a reference to this ClientSocket object
*/
const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}


