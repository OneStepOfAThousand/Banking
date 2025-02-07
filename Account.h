#pragma once
#include "Transaction.h"
#include <vector>
#include <map>
#include "DateCompareValue.h"
struct Account
{
	std::string name = "";
	unsigned int clearingNumber = 0;
	DateCompareValue firstTransactionDate = DateCompareValue();
	DateCompareValue lastTransactionDate = DateCompareValue();
	unsigned long long accountNumber = 0;
	float currentBalance = 0;
	std::vector<Transaction> transactions = std::vector<Transaction>();
	std::vector<Transaction> sortedTransactions = std::vector<Transaction>();	
	std::map<unsigned long, std::vector<Transaction>> mapedTransactions = std::map<unsigned long, std::vector<Transaction>>();
	

	Account();
	Account(std::string name, unsigned int	clearingNumber, unsigned long long accountNumber);
	unsigned int AddTransaction(Transaction & transaction);
	unsigned int SortTransactions();
	unsigned int MapTransactions();
	void PrintToConsole() const;
	void SaveToFile(const std::string & path);
};

