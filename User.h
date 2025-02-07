#pragma once
#include <vector>
#include "Account.h"
struct User
{
	std::string name = "";
	std::vector<Account> accounts = std::vector<Account>();
	User();
	void SaveToFile(const std::string & directory);
};

