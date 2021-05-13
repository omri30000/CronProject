//
// Created by omrizaiman on 12/05/2021.
//

#include "Socket.h"
#include <cerrno>
#include <fcntl.h>


Socket::Socket() : m_sock (ERROR_CODE)
{
    memset (&m_addr,0, sizeof(m_addr));
}

Socket::~Socket()
{
    if (m_sock != ERROR_CODE) ::close ( m_sock );
}

/*
The method is responsible for creating a new socket
input: none
output: none
*/
void Socket::create()
{
    this->m_sock = socket (AF_INET,SOCK_STREAM,0);

    if (m_sock == ERROR_CODE)
        throw SocketException("Could not create socket");

    // TIME_WAIT - argh
    int on = 1;
    if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == ERROR_CODE)
        throw SocketException("Could not create socket");
}

/*
The method is responsible for binding the listening sock with the IP and port that it should listen to
input: ip and port to be bound with
output: none
*/
void Socket::bind (const std::string ip, int port)
{
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    m_addr.sin_port = htons(port);

    int bind_return = ::bind (m_sock,(struct sockaddr*) &m_addr,sizeof(m_addr));

    if (bind_return == ERROR_CODE)
    {
        throw SocketException("Could not bind to port.");
    }
}

/*
The method sets this socket object in listening mode
input: none
output: none
*/
void Socket::listen() const
{
    int listen_return = ::listen (m_sock, MAX_CONNECTIONS);

    if (listen_return == ERROR_CODE)
    {
        throw SocketException("Could not listen to socket.");
    }
}

/*
When in listening mode, the method is responsible for accepting a new client
input: the new socket to accept
output: none
*/
void Socket::accept ( Socket& new_socket ) const
{
    int addr_length = sizeof ( m_addr );
    new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

    if ( new_socket.m_sock <= 0 )
        throw SocketException("Could not accept socket.");
}

/*
The method is responsible for sending data to the other entity.
input: a string to pass to the other entity
output: none
*/
void Socket::send(const std::string& s) const
{
    int status = ::send (m_sock, s.c_str(), s.size(), MSG_NOSIGNAL);
    if (status == ERROR_CODE)
    {
        throw SocketException("Could not write to socket.");
    }
}

/*
The method is responsible for sending data to the other entity.
input: a vector of bytes to pass to the other entity
output: none
*/
void Socket::send (const vector<byte>& vec) const
{
    int status = ::send(m_sock,(byte*)&vec[0], vec.size(),MSG_NOSIGNAL);
    if (status == ERROR_CODE)
    {
        throw SocketException("Could not write to socket.");
    }
}

/*
The method is responsible for receiving data from the other entity.
input: a string reference to fill with data
output: 0 for failure, positive numbers for success (the amount of bytes that was received)
*/
int Socket::recv ( std::string& s ) const
{
    char buf [ MAXRECV + 1 ];

    s = "";

    memset ( buf, 0, MAXRECV + 1 );

    int status = ::recv ( m_sock, buf, MAXRECV, 0 );

    if ( status == -1 )
    {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
        return 0;
    }
    else if ( status == 0 )
    {
        return 0;
    }
    else
    {
        s = buf;
        return status;
    }
}

/*
The method is responsible for the connection with a new entity (socket)
 using the IP address and port.
input: IP address and port of the other entity
output: none
*/
void Socket::connect ( const std::string host, const int port )
{
    if (m_sock == ERROR_CODE)
        throw SocketException("socket disconnected");

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons ( port );

    int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);

    if (status == EAFNOSUPPORT)
        throw SocketException("Address family not supported by protocol");

    status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

    if (status != 0)
        throw SocketException("Error in connection with the server");
}