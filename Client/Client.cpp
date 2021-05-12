//
// Created by omrizaiman on 12/05/2021.
//

#include <cmath>
#include "Client.h"

/*

*/
Client::Client(int commandIdentifier, int delayFactor, bool repeat){
    m_commandId = commandIdentifier;
    m_delay = delayFactor;
    m_repeat = repeat;
}

/*

*/
void Client::communicate(int port){
    try
    {
        ClientSocket client_socket ( "localhost", port );

        std::string reply;

        try
        {
            client_socket << this->createMessage();
            client_socket >> reply;
            std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
            client_socket >> reply;
            std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
            client_socket >> reply;
            std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
        }
        catch ( std::exception& e )
        {
            std::cout << "Exception was caught:" << e.what() << "\n";
        }

    }
    catch ( std::exception& e )
    {
        std::cout << "Exception was caught:" << e.what() << "\n";
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

    for (int i = vec.size() - 1; i >= 0; i--)
    {
        vec[i] = number % BASE;
        number /= BASE;
    }

    return vec;
}