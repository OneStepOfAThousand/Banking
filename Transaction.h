#pragma once
#include <iostream>
#include<string>
#include "DateCompareValue.h"
struct Transaction
{
	unsigned int clearingNum = 0;
	unsigned long long accountNum = 0;
	std::string productType = "";
	std::string currency = "";
	DateCompareValue bookingDate = DateCompareValue();
	DateCompareValue transactionDate = DateCompareValue();
	DateCompareValue currencyDate = DateCompareValue();
	std::string refrence = "";
	std::string description = "";
	float amount = 0.f;
	float balance = 0.f;
	DateCompareValue dateCompareValue = DateCompareValue();

	Transaction();
	Transaction(unsigned int, unsigned long long, std::string, std::string, DateCompareValue, DateCompareValue, DateCompareValue, std::string, std::string, float, float);

	void PrintToConsole() const;

	bool operator==(Transaction & other);
	bool operator!=(Transaction& other);
};

