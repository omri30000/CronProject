//
// Created by Omri Zaiman on 12/05/2021.
//

#include "Server.h"

#define IP "127.0.0.1"
#define PORT 30000

int main(){
    std::cout << "running....\n";
    Server server(IP, PORT);
    server.serve();
    return 0;
}