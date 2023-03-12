#include "DoctorApplication.h"

void DoctorApplication::Working() {
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

void DoctorApplication::GetPatientRequestHandeler() {
    Message mes = Message::GETPATIENT;
    _conConrol.Send(mes);
    int msg_size;
    std::string jsonPatient = _conConrol.RecoveryString();
    try {
        Patient patient = DataHandler::Unpacking(jsonPatient);
        std::cout << "Patient:\nName: " << patient.GetFirstname() << std::endl;
        std::cout << "Surname: " << patient.GetLastname() << std::endl;
        std::cout << "Patronymic: " << patient.GetPatronymic() << std::endl;
        std::cout << "State: " << (patient.GetState() == State::REGULAR ? "regular\n" :
            (patient.GetState() == State::MEDIUM ? "medium\n" : "critical\n"));
    }
    catch (nlohmann::json_abi_v3_11_2::detail::parse_error) {
        std::cout << jsonPatient << std::endl;
    }
}

void DoctorApplication::LogoutRequestHandler() {
    Message mes = Message::LOGOUT;
    _conConrol.Send(mes);
    _logged = false;
    std::cout << "You logged out\n";
}

void DoctorApplication::LoginRequestHandler() {
    Message mes = Message::LOGIN;
    LoginResponse resp;
    do {
        _conConrol.Send(mes);
        std::cout << "Login:\n";
        std::string login;
        std::getline(std::cin, login);
        std::cout << "Password:\n";
        std::string password;
        std::getline(std::cin, password);
        if (password == "") password = " ";
        _conConrol.Send(login);
        _conConrol.Send(password);

        resp = _conConrol.RecoveryLoginResponse();
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

DoctorApplication::DoctorApplication() : _logged(false) {
    _conConrol.Connect();
    Working();
}
