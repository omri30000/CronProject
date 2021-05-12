//
// Created by omrizaiman on 12/05/2021.
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

            try
            {
                while ( true )
                {
                    vector<byte> data;

                    std::basic_string<char> result;
                    new_sock >> data;
                    result = Server::communicate(data[0],0,false);

                    new_sock << result;
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    while(data[1] != 0){
                        new_sock << result;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }
                }
            }
            catch ( std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    catch ( std::exception& e )
    {
        std::cerr << "Exception was caught:" << e.what() << "\nExiting.\n";
    }
}

/*

*/
std::string Server::communicate(int commandId, int delay, bool repeat){
    std::string data;

    switch (commandId){
        case 1:
            data = Server::getTime();
            break;
        case 2:
            data = Server::getOSVersion();
            break;
        case 3:
            data = Server::getHostsFile();
            break;
        default:
            break;
    }

    return data;
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

