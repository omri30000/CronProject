//
// Created by Omri Zaiman on 12/05/2021.
//
#include "Server.h"

Server::Server(std::string ip, int port, int clientsAmount){
    this->m_threadsAmount = clientsAmount;
    this->m_listeningPort = port;
    this->m_ip = ip;

    //initialize thread m_pool
    for(int i = 0; i < this->m_threadsAmount; i++){
        std::shared_ptr<std::thread> pNewThread = std::make_shared<std::thread>(&Server::threadFunction, this);
        this->m_pool.push_back(pNewThread);
        pNewThread->detach();
    }
}

/*
This method is a starter for the server. when being called, the server becomes available for clients
input: none
output: none
*/
void Server::serve(){
    try
    {
        // Create the socket
        ServerSocket listenSock (this->m_ip, this->m_listeningPort);

        while (true)
        {
            std::shared_ptr<ServerSocket> pNewSock;
            pNewSock = std::make_shared<ServerSocket>();
            listenSock.accept (*pNewSock);

            {
                std::lock_guard<std::mutex> lock(m_mutex);
                this->m_connections.push(pNewSock);
            }

            this->m_cv.notify_one();
        }
    }
    catch ( std::exception& e )
    {
        std::cerr << "Exception was caught:" << e.what() << "\nExiting.\n";
    }
}

/*
the method is responsible for communication of the server with a single client (via given socket)
input: the conversation socket with the client
output: none
*/
void Server::communicate(std::shared_ptr<ServerSocket> sock){
    try
    {
        while (true)
        {
            vector<byte> data, time;
            std::string response;
            int secondsDelay = 0;

            std::basic_string<char> result;
            *sock >> data;

            time = {data.begin() + 2, data.end()};
            secondsDelay = base256ToInt(time);

            switch (data[0]){
                case 1:
                    response = Server::getTime();
                    break;
                case 2:
                    response = Server::getOSVersion();
                    break;
                case 3:
                    response = Server::getHostsFile();
                    break;
                default:
                    break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(secondsDelay));
            *sock << response;

            while(data[1] != 0){
                std::this_thread::sleep_for(std::chrono::seconds(secondsDelay));
                *sock << response;
            }
        }
    }
    catch ( std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

/*
The method will find the server's time
input: none
output: string represents the server's time
*/
std::string Server::getTime(){
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return ctime(&now);
}

/*
The method will find the server's OS version
input: none
output: a string represents the OS version
*/
std::string Server::getOSVersion(){
    struct utsname name{};

    if(uname(&name)){
        throw std::runtime_error("Could not detect OS version");
    }

    return std::string(name.version);
}

/*
The method will read the content of the machine's hosts file
input: none
output: the content of the server's hosts file
*/
std::string Server::getHostsFile(){
    std::ifstream ifs("/etc/hosts");
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );


    return content;
}

/*
The static method will help casting a bytes' vector into an integer
input: a vector of bytes
output: the integer that is represented in the given vector
*/
int Server::base256ToInt(vector<byte> &vec) {
    const int BASE = 256;
    const int BYTES_AMOUNT = 4;
    int time = 0;

    for (int i = 0; i < BYTES_AMOUNT; i++){
        time += (int)std::pow(BASE,BYTES_AMOUNT - 1 - i) * (int)vec[i];
    }

    return time;
}

/*
This is a working thread belongs to the thread pool (worker). it waits until there is a job to do.
input: none
output: none
*/
[[noreturn]] void Server::threadFunction() {
    while (true){
        std::unique_lock<std::mutex> lock(m_mutex);
        if (this->m_connections.empty()){
            m_cv.wait(lock);
        }

        std::shared_ptr<ServerSocket> sock = this->m_connections.front();
        this->m_connections.pop();
        lock.unlock();
        communicate(sock);
    }
}

