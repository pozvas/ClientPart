#pragma once
#include <iostream>
enum class State {
	REGULAR,
	MEDIUM,
	CRITICAL,
	UNDEFIEND
};
class Patient
{
protected:
	std::string _firstname;
	std::string _lastname;
	std::string _patronymic;
	State _state;
public:
	Patient() : _state(State::UNDEFIEND) {}
	Patient(const std::string& firstname,
		const std::string& lastname,
		const std::string& patronymic,
		State state) : _firstname(firstname), _lastname(lastname), _patronymic(patronymic), _state(state) {}
	std::string GetFirstname() const { return _firstname; }
	std::string GetLastname() const { return _lastname; }
	std::string GetPatronymic() const { return _patronymic; }
	State GetState() const { return _state; }
	std::string Convert();
	static Patient Reconvert(std::string str);
	bool IsNormal() {
		return true;
	}
	virtual ~Patient() {}
};

class VIP_Patient : public Patient {
private:
	size_t _moneyAmount;
public:
	VIP_Patient(const std::string& firstname,
		const std::string& lastname,
		const std::string& patronymic,
		State state,
		size_t moneyAmount = 100) : Patient(firstname, lastname, patronymic, state), _moneyAmount(moneyAmount) {
	}
	size_t GetMoney() { return _moneyAmount; }
	bool IsNormal() {
		return false;
	}
};





