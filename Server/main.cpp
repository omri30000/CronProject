//
// Created by Omri Zaiman on 12/05/2021.
//

#include "Server.h"
#include <string>

int main(){
    std::cout << "running....\n";
    Server server(30000);
    server.serve();
    return 0;
}

int mainly()
{
    try
    {
        // Create the socket
        ServerSocket server ( 30000 );

        while ( true )
        {

            ServerSocket new_sock;
            server.accept (new_sock);

            try
            {
                while (true)
                {
                    std::string data;
                    new_sock >> data;
                    new_sock << data;
                }
            }
            catch ( SocketException& ) {}

        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception was caught:" << e.what() << "\nExiting.\n";
    }

    return 0;
}