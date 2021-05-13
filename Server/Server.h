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

class Server {
public:
    explicit Server(std::string ip, int port, int clientsAmount) noexcept(false);
    void serve() noexcept(false);

protected:
    std::mutex m_mutex;
    std::condition_variable m_cv;

    std::queue<std::shared_ptr<ServerSocket>> m_connections;
    std::vector<std::shared_ptr<std::thread>> m_pool;
    int m_listeningPort;
    std::string m_ip;
    int m_threadsAmount;

    [[noreturn]] void threadFunction();
    static void communicate(std::shared_ptr<ServerSocket> sock);
    static std::string getTime();
    static std::string getOSVersion() noexcept(false);
    static std::string getHostsFile();

    static int base256ToInt(vector<byte>& vec);
};

#endif //SERVER_SERVER_H
