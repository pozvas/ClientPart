#pragma once
#include <iostream>
#include "Patient.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DataHandler
{
public:
	static std::string Packing(const Patient& p);
	static std::string Packing(const VIP_Patient& p);
	static Patient Unpacking(const std::string& str);
};

