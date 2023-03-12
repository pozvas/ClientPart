#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h> 
#include <iostream>
#include <string>
#include "DataHandler.h"

#pragma warning(disable: 4996)


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

class ConnectionController
{
private:
    SOCKET _connection;
    SOCKADDR_IN _addr;
    
public:
    ConnectionController();
    void Connect();
    void Send(const Message mes);
    void Send(const std::string& mes);
    std::string RecoveryString();
    LoginResponse RecoveryLoginResponse();
};

