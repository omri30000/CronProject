//
// Created by omrizaiman on 12/05/2021.
//

#ifndef CLIENT_CLIENTSOCKET_H
#define CLIENT_CLIENTSOCKET_H

#include "Socket.h"

class ClientSocket : private Socket
{
public:

    ClientSocket ( std::string host, int port );
    virtual ~ClientSocket(){};

    const ClientSocket& operator << (const vector<byte>& vec) const;

    const ClientSocket& operator << ( const std::string& ) const;
    const ClientSocket& operator >> ( std::string& ) const;

};

#endif //CLIENT_CLIENTSOCKET_H
