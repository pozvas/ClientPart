#pragma once
#include <iostream>
#include "Patient.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DataHandler
{
public:
	static std::string Packing(const Patient& p) {
		json j = json{ {"firstname", p.GetFirstname()}, {"lastname", p.GetLastname()}, {"patronymic", p.GetPatronymic()}, {"state", p.GetState()} };
		return j.dump();
	}

	static std::string Packing(const VIP_Patient& p) {
		json j = json{ {"firstname", p.GetFirstname()}, {"lastname", p.GetLastname()}, {"patronymic", p.GetPatronymic()}, {"state", p.GetState()}, {"money", p.GetMoney()} };
		return j.dump();;
	}

	static Patient Unpacking(const std::string& str) {
		json j = json::parse(str);
		Patient* patient;
		if (j.contains("money"))
			patient = new VIP_Patient(j.at("firstname"), j.at("lastname"), j.at("patronymic"), j.at("state"), j.at("money"));
		else
			patient = new Patient(j.at("firstname"), j.at("lastname"), j.at("patronymic"), j.at("state"));
		return *patient;
	}
};

