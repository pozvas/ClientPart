#pragma once
#include "ConnectionController.h"

class DoctorApplication
{
private:
	ConnectionController _conConrol;
    bool _logged;

    void Working();
    void GetPatientRequestHandeler();
    void LogoutRequestHandler();
    void LoginRequestHandler();
public:
    DoctorApplication();
};

