#pragma once
#include "ConnectionController.h"
#include "Patient.h"
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
	void GetPatient() {
		std::cout << "dadas";
	}
};

