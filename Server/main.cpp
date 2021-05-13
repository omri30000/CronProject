//
// Created by Omri Zaiman on 12/05/2021.
//

#include "Server.h"
#include <string>

int main(){
    std::cout << "running....\n";
    Server server("127.0.0.1", 30000);
    server.serve();
    return 0;
}