//
// Created by omrizaiman on 12/05/2021.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <string>
#include <iostream>
#include <chrono>
#include <map>
#include <thread>
#include <sys/utsname.h>

#include "ServerSocket.h"

class Server {
public:
    explicit Server(int port) noexcept(false);
    void serve() noexcept(false);

protected:

    int listeningPort;

    static std::string communicate(int commandId, int delay, bool repeat);

    static std::string getTime();
    static std::string getOSVersion() noexcept(false);
    static std::string getHostsFile();
};

#endif //SERVER_SERVER_H
