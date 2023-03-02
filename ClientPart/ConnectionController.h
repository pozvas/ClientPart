#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h> 
#include <iostream>
#include <string>

#pragma warning(disable: 4996)

class ConnectionController
{
private:
    SOCKET _connection;
    SOCKADDR_IN _addr;

    static void ServerResponseHandler(SOCKET* connection) {
        int msg_size;
        while (true) {
            recv(*connection, (char*)&msg_size, sizeof(int), NULL);
            char* msg = new char[msg_size + 1];
            msg[msg_size] = '\0';
            recv(*connection, msg, msg_size, NULL);
            std::cout << msg << std::endl;
            delete[] msg;
        }
    }

    void ClientMessageHandler() {
        std::string msgl;
        while (true) {
            std::getline(std::cin, msgl);
            int msg_size = msgl.size();
            send(_connection, (char*)&msg_size, sizeof(int), NULL);
            send(_connection, msgl.c_str(), msg_size, NULL);
            Sleep(10);
        }
    }

public:
    ConnectionController() {
        WSAData wsaData;
        WORD DLLVersion = MAKEWORD(2, 2);
        if (WSAStartup(DLLVersion, &wsaData) != 0) {
            std::cout << "Error" << std::endl;
            exit(1);

        }

        int sizeofaddr = sizeof(_addr);
        _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        _addr.sin_port = htons(1111);
        _addr.sin_family = AF_INET;

        _connection = socket(AF_INET, SOCK_STREAM, NULL);
    }

    void Connect() {
        if (connect(_connection, (SOCKADDR*)&_addr, sizeof(_addr)) != 0) {
            std::cout << "Error: failed connect to server. \n";
            exit(1);
        }
        std::cout << "Connected to server" << std::endl;

        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerResponseHandler, &_connection, NULL, NULL);

        ClientMessageHandler();
    }

};

