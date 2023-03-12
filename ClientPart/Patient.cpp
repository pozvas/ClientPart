#include "Patient.h"

Patient::Patient() : _state(State::UNDEFIEND) {}

Patient::Patient(const std::string& firstname, const std::string& lastname, const std::string& patronymic, State state)
	: _firstname(firstname), _lastname(lastname), _patronymic(patronymic), _state(state) {}

std::string Patient::GetFirstname() const { return _firstname; }

std::string Patient::GetLastname() const { return _lastname; }

std::string Patient::GetPatronymic() const { return _patronymic; }

State Patient::GetState() const { return _state; }

bool Patient::operator>(const Patient& p) const {
	if (p._state == State::CRITICAL) return false;
	else return true;
}

Patient::~Patient() {}

VIP_Patient::VIP_Patient() : Patient() {}

VIP_Patient::VIP_Patient(const std::string& firstname, const std::string& lastname, const std::string& patronymic, State state, size_t moneyAmount)
	: Patient(firstname, lastname, patronymic, state), _moneyAmount(moneyAmount) {}

size_t VIP_Patient::GetMoney() const { return _moneyAmount; }

bool VIP_Patient::operator>(const VIP_Patient& p) const {
	if (p._state == State::CRITICAL || p.GetMoney() >= this->GetMoney()) return false;
	else return true;
}
