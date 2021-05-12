//
// Created by Omri Zaiman on 12/05/2021.
//

#include "Client.h"
#include <map>
#include <iostream>
#include <string>

enum positions {NAME, FIRST_FLAG, FIRST_PARAM, SECOND_FLAG, SECOND_PARAM, THIRD_FLAG, THIRD_PARAM};
enum cBoolean {FALSE, TRUE};
const int PARAMS_AMOUNT = 7;

int main(int argc, char** argv){
    std::map<std::string, int> parameters;

    if (argc != PARAMS_AMOUNT){
        std::cerr << "Invalid parameters. read the README file!";
        return -1;
    }

    parameters[std::string(argv[FIRST_FLAG])] = stoi(std::string(argv[FIRST_PARAM]));
    parameters[std::string(argv[SECOND_FLAG])] = stoi(std::string(argv[SECOND_PARAM]));
    parameters[std::string(argv[THIRD_FLAG])] = std::string(argv[THIRD_PARAM]) == "true" ? TRUE : FALSE;

    Client client(parameters[std::string(argv[FIRST_FLAG])], parameters[std::string(argv[SECOND_FLAG])],
                  parameters[std::string(argv[THIRD_FLAG])] == TRUE);

    client.communicate(30000);

    return 0;
}

//int mainly (int argc, char** argv)
//{
//    try
//    {
//        ClientSocket client_socket ( "localhost", 30000 );
//
//        std::string reply;
//
//        try
//        {
//            while(true){
//                std::string input;
//                std::cin >> input;
//                client_socket << input;
//                client_socket >> reply;
//
//                std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
//            }
//        }
//        catch ( SocketException& ) {}
//
//    }
//    catch ( std::exception& e )
//    {
//        std::cout << "Exception was caught:" << e.what() << "\n";
//    }
//
//    return 0;
//}