#pragma once
#include <iostream>

enum class State {
	UNDEFIEND,
	REGULAR,
	MEDIUM,
	CRITICAL
};
class Patient
{
protected:
	std::string _firstname;
	std::string _lastname;
	std::string _patronymic;
	State _state;
public:
	Patient();
	Patient(const std::string& firstname,
		const std::string& lastname,
		const std::string& patronymic,
		State state);
	std::string GetFirstname() const;
	std::string GetLastname() const;
	std::string GetPatronymic() const;
	State GetState() const;
	bool operator>(const Patient& p) const;
	virtual ~Patient();
};

class VIP_Patient : public Patient {
private:
	size_t _moneyAmount;
public:
	VIP_Patient();
	VIP_Patient(const std::string& firstname,
		const std::string& lastname,
		const std::string& patronymic,
		State state,
		size_t moneyAmount = 100);
	size_t GetMoney() const;
	bool operator>(const VIP_Patient& p) const;
};





