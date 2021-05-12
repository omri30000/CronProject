//
// Created by Omri Zaiman on 12/05/2021.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include "ClientSocket.h"
#include "SocketException.h"

class Client {
public:
    Client(int commandIdentifier, int delayFactor, bool repeat);
    void communicate(int port);


protected:
    int m_commandId;
    int m_delay;
    bool m_repeat;

    [[nodiscard]] vector<byte> createMessage() const;
    static vector<byte> castToBase256(int number) noexcept(false);
};


#endif //CLIENT_CLIENT_H
