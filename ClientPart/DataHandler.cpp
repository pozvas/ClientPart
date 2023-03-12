#include "DataHandler.h"

std::string DataHandler::Packing(const Patient& p) {
	json j = json{ {"firstname", p.GetFirstname()}, {"lastname", p.GetLastname()}, {"patronymic", p.GetPatronymic()}, {"state", p.GetState()} };
	return j.dump();
}

std::string DataHandler::Packing(const VIP_Patient& p) {
	json j = json{ {"firstname", p.GetFirstname()}, {"lastname", p.GetLastname()}, {"patronymic", p.GetPatronymic()}, {"state", p.GetState()}, {"money", p.GetMoney()} };
	return j.dump();;
}

Patient DataHandler::Unpacking(const std::string& str) {
	json j = json::parse(str);
	if (j.contains("money"))
		return VIP_Patient(j.at("firstname"), j.at("lastname"), j.at("patronymic"), j.at("state"), j.at("money"));
	else
		return Patient(j.at("firstname"), j.at("lastname"), j.at("patronymic"), j.at("state"));
}
