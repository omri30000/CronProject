//
// Created by Omri Zaiman on 12/05/2021.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <string>
#include <iostream>
#include <chrono>
#include <map>
#include <cmath>
#include <thread>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <fstream>
#include <queue>
#include <sys/utsname.h>

#include "ServerSocket.h"
#define threadsAmount 3

class Server {
public:
    explicit Server(int port) noexcept(false);
    void serve() noexcept(false);

protected:
    std::mutex m_mutex;
    std::condition_variable m_cv;

    std::queue<std::shared_ptr<ServerSocket>> connections;
    std::vector<std::thread*> pool;
    int listeningPort;

    [[noreturn]] void threadFunction();
    static void communicate(std::shared_ptr<ServerSocket> sock);
    static std::string getTime();
    static std::string getOSVersion() noexcept(false);
    static std::string getHostsFile();

    static int base256ToInt(vector<byte>& vec);
};

#endif //SERVER_SERVER_H
