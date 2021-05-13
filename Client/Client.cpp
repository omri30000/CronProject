//
// Created by Omri Zaiman on 12/05/2021.
//

#include <cmath>
#include "Client.h"

/*

*/
Client::Client(std::string commandIdentifier, std::string delayFactor, std::string repeat){

    if (!Client::isInputValid(commandIdentifier, delayFactor, repeat)){
        throw std::runtime_error("Invalid format/parameters. read the README.md file!");
    }

    m_commandId = std::stoi(commandIdentifier);
    m_delay = std::stoi(delayFactor);
    m_repeat = repeat == "true";
}

/*

*/
void Client::communicate(std::string ip, int port){
    try
    {
        ClientSocket client_socket ( ip, port );

        std::string reply;

        try
        {
            client_socket << this->createMessage();
            client_socket >> reply;
            std::cout << "Server> " << reply << std::endl;
            while (this->m_repeat){
                client_socket >> reply;
                std::cout << "Server> " << reply << std::endl;
            }
        }
        catch ( std::exception& e )
        {
            std::cout << "Exception was caught: " << e.what() << "\n";
        }

    }
    catch ( std::exception& e )
    {
        std::cout << "Exception was caught: " << e.what() << "\n";
    }
}

vector<byte> Client::createMessage() const {
    vector<byte> data;
    vector<byte> time = Client::castToBase256(this->m_delay);

    data.push_back(m_commandId);
    data.push_back(m_repeat ? 1 : 0);
    data.insert(data.end(), time.begin(), time.end());

    return data;
}

/*
The function will convert a number to base 256
input: an integer to be converted
output: the number in base 256
*/
vector<byte> Client::castToBase256(int number) noexcept(false){
    const int BASE = 256;
    const int BYTES_AMOUNT = 4;

    vector<byte> vec = { 0, 0, 0, 0 };

    if (number > std::pow(BASE,BYTES_AMOUNT))
    {
        throw std::runtime_error("number is over the limit of 4 bytes");
    }

    for (int i = (int)vec.size() - 1; i >= 0; i--)
    {
        vec[i] = number % BASE;
        number /= BASE;
    }

    return vec;
}

bool Client::isInputValid(std::string commandIdentifier, std::string delayFactor, std::string repeat) {

    for (char const &c : commandIdentifier) {
        if (std::isdigit(c) == 0) return false;
    }

    for (char const &c : delayFactor) {
        if (std::isdigit(c) == 0) return false;
    }

    if (!(repeat == "true" || repeat == "false"))
        return false;

    return true;
}
