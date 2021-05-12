//
// Created by omrizaiman on 12/05/2021.
//

#include "ClientSocket.h"
#include "SocketException.h"


ClientSocket::ClientSocket ( std::string host, int port )
{
    Socket::create();
    Socket::connect ( host, port );
}

const ClientSocket& ClientSocket::operator << ( const vector<byte>& vec ) const
{
    //std::cout << "vec[0]: " << (int)vec[0] << std::endl;
    //std::cout << "size: " << vec.size() << std::endl;
    Socket::send (vec);
    return *this;
}

const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    Socket::send ( s );
    return *this;
}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}


