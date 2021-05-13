# CronProject
Omri Zaiman's application task for Aqua Security. Client and server programs that communicates via sockets. The client provides a command line interface to register cron tasks that are executed in the server (cron engine).

The project was written in Jetbrain's Clion environment on Linux Ubuntu 20.04.1.

## How to use?
In order to use the engine, follow the instructions:
1. Modify the PORT and IP in the server and client's main.cpp files (Optional - for remote hosting) and make sure that the server is up.
2. Run the client program in the terminal using the following format: "./Client --command-id <x> --delay-factor <y> --repeat <z>". <br>
   Example: "./Client --command-id 1 --delay-factor 30 --repeat true"
    * x - number between 1 and 3, the identifier of the command.
    * y - number between 0 and 4294967296, the delay in which the server will respond (in seconds).
    * z - true/false, determines whether the response have to be repeatitive.

#### Supported commands
--comand-id 1 : Get server time <br>
--comand-id 2 : Get server OS version <br>
--comand-id 3 : Get server hosts file <br>

## Application layer protocol
### Request (client to server)
a request from a client to the server is basically a buffer of 6 bytes (with indexes 0 to 5).
* index 0 - a byte represents the command identifier.
* index 1 - a byte which determines whether the response should be repeatitive (0 - false, 1 - true).
* index 2 to 5 - 4 bytes represents the required delay (in seconds).

For example: 
<br>
![request image](/request.jpeg) 
<br>
In the request above:
* command identifier - 1
* repeat - true
* delay - 15 seconds

#### Future plans
In the near future I am planning on upgrading the protocol to consume less memory and be encrypted

### Response (server to client)
Since all the responses should provide strings, and due to time limitation, I decided to pass the string as is from the server to the client. 

#### Future plans
I would like to deliver the hosts file from the server as a file and not as a string. Than the client will be able to easily save the file in it's hard drive.

## Self-implemented thread-pool
The server is capble of communicating with a limited amount of clients simultaneously. Let N be the maximum amount of clients. When being run, the server creates N threads that can accept clients into a conversation. When there are already N active clients, the N+1th client will wait until another one will disconnect. Once disconnected, the thread that was responsible for this client will be able to take care of the new one.
