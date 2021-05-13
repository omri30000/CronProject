//
// Created by Omri Zaiman on 12/05/2021.
//

#include "Server.h"

Server::Server(int port){
    this->listeningPort = port;
}

void Server::serve(){
    try
    {
        // Create the socket
        ServerSocket listenSock (this->listeningPort);

        while (true)
        {
            ServerSocket new_sock;
            listenSock.accept (new_sock);
            Server::communicate(new_sock);
        }
    }
    catch ( std::exception& e )
    {
        std::cerr << "Exception was caught:" << e.what() << "\nExiting.\n";
    }
}

/*

*/
void Server::communicate(ServerSocket& sock){
    try
    {
        while ( true )
        {
            vector<byte> data, time;
            std::string response;
            int secondsDelay = 0;

            std::basic_string<char> result;
            sock >> data;

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

            sock << response;

            while(data[1] != 0){
                std::this_thread::sleep_for(std::chrono::seconds(secondsDelay));
                sock << response;
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

*/
std::string Server::getHostsFile(){
    return "hosts file";
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

