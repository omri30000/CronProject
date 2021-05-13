//
// Created by Omri Zaiman on 12/05/2021.
//

#include "Client.h"
#include <iostream>
#include <string>

#define PORT 30000
#define IP "127.0.0.1"

enum positions {NAME, FIRST_FLAG, FIRST_PARAM, SECOND_FLAG, SECOND_PARAM, THIRD_FLAG, THIRD_PARAM};
enum cBoolean {FALSE, TRUE};
const int PARAMS_AMOUNT = 7;

int main(int argc, char** argv){

    if (argc != PARAMS_AMOUNT){
        std::cerr << "Invalid format/parameters. read the README.md file!";
        return -1;
    }
    std::string commandId(argv[FIRST_PARAM]);
    std::string delayFactor(argv[SECOND_PARAM]);
    std::string repeat(argv[THIRD_PARAM]);

    try{
        Client client(commandId, delayFactor, repeat);
        client.communicate(IP, PORT);
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
}