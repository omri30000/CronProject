//
// Created by Omri Zaiman on 12/05/2021.
//

#include "Server.h"

#define IP "127.0.0.1"
#define PORT 30000
#define MAX_CLIENTS 5 // the maximum amount of clients simultaneously

int main(){
    std::cout << "running....\n";
    Server server(IP, PORT, MAX_CLIENTS);
    server.serve();
    return 0;
}