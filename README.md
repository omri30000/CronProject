# CronProject
Omri Zaiman's application task for Aqua Security. Client and server programs that communicates via sockets. The client provides a command line interface to register cron tasks that are executed in the server (cron engine).

## How to use?
In order to use the engine, follow the instructions:
1. Make sure that the configuration files of the server and client are modified and the server is up.
2. Run the client program in the terminal using the following format: "./Client --command-id <x> --delay-factor <y> --repeat <z>". <br>
   Example: "./Client --command-id 1 --delay-factor 30 --repeat true"
    * x - number between 1 and 3, the identifier of the command.
    * y - number between 0 and 4294967296, the delay in which the server will respond (in seconds).
    * z - true/false, determines whether the response have to be repeatitive.



## UML
add photo

## Application layer protocol
describe

## Self-implemented thread-pool
The server is capble of communicating with a limited amount of clients simultaneously, that amount can be modified via the server's configuration file. let N be the maximum amount of clients. When being run, the server creates N threads that can accept clients into a conversation. When there are already N active clients, the N+1th client will wait until another one will disconnect. Once disconnected, the thread that was responsible for this client will be able to take care of the new one.

## Beyond requirements features
* Configuration files written in JSON.
* default parameters.
