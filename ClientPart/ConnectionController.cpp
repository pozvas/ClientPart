#include "ConnectionController.h"

ConnectionController::ConnectionController() {
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

void ConnectionController::Connect() {
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

    //ClientMessageHandler();
}

void ConnectionController::Send(const Message mes) {
    send(_connection, (char*)&mes, sizeof(Message), NULL);
}

void ConnectionController::Send(const std::string& mes) {
    int message_size = mes.length();
    send(_connection, (char*)&message_size, sizeof(int), NULL);
    send(_connection, mes.c_str(), message_size, NULL);
}

std::string ConnectionController::RecoveryString() {
    int msg_size;
    recv(_connection, (char*)&msg_size, sizeof(int), NULL);
    char* msg = new char[msg_size + 1];
    msg[msg_size] = '\0';
    recv(_connection, msg, msg_size, NULL);
    return msg;
}

LoginResponse ConnectionController::RecoveryLoginResponse() {
    LoginResponse resp;
    recv(_connection, (char*)&resp, sizeof(LoginResponse), NULL);
    return resp;
}
