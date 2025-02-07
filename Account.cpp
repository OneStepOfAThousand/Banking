#include "Account.h"

Account::Account()
{
}

Account::Account(std::string name, unsigned int clearingNumber, unsigned long long accountNumber) : name(name), clearingNumber(clearingNumber), accountNumber(accountNumber)
{
}

unsigned int Account::AddTransaction(Transaction & transaction)
{
	for (auto& t : transactions)
	{
		if (t == transaction)
		{
			return 1;
		}
	}
	transactions.emplace_back(transaction);
	if (lastTransactionDate<transaction.dateCompareValue) {
		lastTransactionDate = transaction.dateCompareValue;
		currentBalance = transaction.balance;
		return 2;
	}
	if (firstTransactionDate>transaction.dateCompareValue)
	{
		firstTransactionDate = transaction.dateCompareValue;
		return 3;
	}
	return 0;
}

unsigned int Account::SortTransactions()
{
	bool sorted = false;
	std::vector<Transaction>::iterator it;

	for (auto& t : transactions) {
		if (sortedTransactions.size() == 0)
		{
			sortedTransactions.push_back(t);
			continue;
		}

		sorted = false;
		it = sortedTransactions.begin();
		for (size_t i = 0; i < sortedTransactions.size(); i++)
		{
			//t is the value that needs to be added to the sorted list
			if (t.dateCompareValue > sortedTransactions[i].dateCompareValue) {
				sortedTransactions.insert(it + i, t);
				sorted = true;
				break;
			}
		}

		if (!sorted)
		{
			sortedTransactions.push_back(t);
		}
	}
	return 0;
}

unsigned int Account::MapTransactions()
{
	bool alreadyMapped = false; //Don't add again if already mapped!

	for (auto & t : transactions) //TODO, switch to sorted transactions, currently doesn't work
	{
		alreadyMapped = false;
		auto tv = mapedTransactions.find(t.dateCompareValue.value); //Transaction vector iterator
		if (tv == mapedTransactions.end()) //Null check
		{ 
			mapedTransactions.emplace(t.dateCompareValue.value, std::vector<Transaction>());//Create new transaction vector for the day
		}
		else
		{
			for (auto & mt : mapedTransactions[t.dateCompareValue.value])  //Mapped transaction
			{
				if (t == mt) //Existence check
				{
					alreadyMapped = true; //Already mapped
				}
			}
		}

		if (!alreadyMapped) //Adds if not mapped
		{
			mapedTransactions[t.dateCompareValue.value].push_back(t);
		}
	}
	return 0;
}

void Account::PrintToConsole() const
{
	std::cout << name << ", " << clearingNumber << "-" << accountNumber << ", transactions: " << transactions.size() << std::endl;
}

void Account::SaveToFile(const std::string& path)
{
}
