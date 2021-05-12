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


void Socket::bind (int port)
{
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);

    int bind_return = ::bind (m_sock,(struct sockaddr*) &m_addr,sizeof(m_addr));

    if (bind_return == ERROR_CODE)
    {
        throw SocketException("Could not bind to port.");
    }
}


void Socket::listen() const
{
    int listen_return = ::listen (m_sock, MAX_CONNECTIONS);

    if (listen_return == ERROR_CODE)
    {
        throw SocketException("Could not listen to socket.");
    }
}


void Socket::accept ( Socket& new_socket ) const
{
    int addr_length = sizeof ( m_addr );
    new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

    if ( new_socket.m_sock <= 0 )
        throw SocketException("Could not accept socket.");
}

void Socket::send (const std::string& s) const
{
    int status = ::send (m_sock, s.c_str(), s.size(), MSG_NOSIGNAL);
    if (status == ERROR_CODE)
    {
        throw SocketException("Could not write to socket.");
    }
}

void Socket::send (const vector<byte>& vec) const
{
    int status = ::send(m_sock,(byte*)&vec[0], vec.size(),MSG_NOSIGNAL);
    if (status == ERROR_CODE)
    {
        throw SocketException("Could not write to socket.");
    }
}


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


void Socket::connect ( const std::string host, const int port )
{
    if (m_sock == ERROR_CODE)
        throw SocketException("socket disconnected");

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons ( port );

    int status = inet_pton ( AF_INET, host.c_str(), &m_addr.sin_addr );

    if ( errno == EAFNOSUPPORT )
        throw SocketException("Address family not supported by protocol");

    status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

    if ( status != 0 )
        throw SocketException("Error in connection with the server");
}

void Socket::set_non_blocking(const bool b)
{
    int opts;

    opts = fcntl(m_sock, F_GETFL);

    if (opts < 0)
    {
        return;
    }

    if ( b )
        opts = ( opts | O_NONBLOCK );
    else
        opts = ( opts & ~O_NONBLOCK );

    fcntl ( m_sock,
            F_SETFL,opts );

}