#pragma once
#include "ConnectionController.h"

class DoctorApplication
{
private:
	ConnectionController _conConrol;
	void Login() {
		_conConrol.Connect();
	}
public:
	DoctorApplication() {
		Login();
	}
};

