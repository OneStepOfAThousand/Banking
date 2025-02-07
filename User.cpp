#include "User.h"

User::User()
{
	accounts = std::vector<Account>();
}

void User::SaveToFile(const std::string & directory)
{
	for (auto& a : accounts)
	{
		a.SaveToFile(directory +"/" + name);
	}
}
