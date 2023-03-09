#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h> 
#include <iostream>
#include <string>
#include "DataHandler.h"

#pragma warning(disable: 4996)

class ConnectionController
{
private:
    SOCKET _connection;
    SOCKADDR_IN _addr;
    bool _logged;
    enum class Message {
        LOGIN,
        GETPATIENT,
        LOGOUT
    };
    enum class LoginResponse {
        WRONG,
        RIGHT,
        ALREADYENTER
    };

    void ClientMessageHandler() {
        while (true) {
            if (_logged) {
                std::cout << "\n1 - Give patient from queue \n2 - Logout\n";
                int buf;
                std::cin >> buf;
                switch (buf) {
                case(1): {
                    GetPatientRequestHandeler();
                } break;
                case(2): {
                    LogoutRequestHandler();
                } break;
                }

            }
            else {
                LoginRequestHandler();
            }
            Sleep(10);
        }
    }

    void GetPatientRequestHandeler() {
        Message mes = Message::GETPATIENT;
        send(_connection, (char*)&mes, sizeof(Message), NULL);
        int msg_size;
        recv(_connection, (char*)&msg_size, sizeof(int), NULL);
        char* msg = new char[msg_size + 1];
        msg[msg_size] = '\0';
        recv(_connection, msg, msg_size, NULL);
        Patient patient = DataHandler::Unpacking(msg);
        std::cout << "Patient:\nName: " << patient.GetFirstname() << std::endl;
        std::cout << "Surname: " << patient.GetLastname() << std::endl;
        std::cout << "Patronymic: " << patient.GetPatronymic() << std::endl;
        std::cout << "State: " << (patient.GetState() == State::REGULAR ? "regular\n" :
            (patient.GetState() == State::MEDIUM ? "medium\n" : "critical\n"));
        delete[] msg;
    }

    void LogoutRequestHandler() {
        Message mes = Message::LOGOUT;
        send(_connection, (char*)&mes, sizeof(Message), NULL);
        _logged = false;
        std::cout << "You logged out";
    }

    void LoginRequestHandler() {
        Message mes = Message::LOGIN;
        LoginResponse resp;
        do {
            send(_connection, (char*)&mes, sizeof(Message), NULL);
            std::cout << "Login:\n";
            std::string login;
            std::getline(std::cin, login);
            std::cout << "Password:\n";
            std::string password;
            std::getline(std::cin, password);

            int login_size = login.length();
            int password_size = password.length();
            send(_connection, (char*)&login_size, sizeof(int), NULL);
            send(_connection, login.c_str(), login_size, NULL);
            send(_connection, (char*)&password_size, sizeof(int), NULL);
            send(_connection, password.c_str(), password_size, NULL);

            recv(_connection, (char*)&resp, sizeof(LoginResponse), NULL);
            if (resp == LoginResponse::WRONG) {
                std::cout << "Login or password is wrong\n";
            }
            if (resp == LoginResponse::ALREADYENTER) {
                std::cout << "This account has already logging in\n";
            }
        } while (resp != LoginResponse::RIGHT);
        std::cout << "You logged in\n";
        _logged = true;
    }

public:
    ConnectionController() : _logged(false) {
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
        int i = 0;
        do {
            std::cout << "Connecting to server...\n";
            if (connect(_connection, (SOCKADDR*)&_addr, sizeof(_addr)) == 0)
                break;
            i++;
            if (i == 5) {
                std::cout << "Error: failed connect to server. \n";
                exit(1);
            }
            Sleep(10);
        } while (i < 5);

        std::cout << "Connected to server" << std::endl;

        ClientMessageHandler();
    }

};

