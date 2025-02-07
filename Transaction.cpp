#include "Transaction.h"

Transaction::Transaction()
{
}

Transaction::Transaction(unsigned int clearingNum, unsigned long long accountNum, std::string productType, std::string currency, DateCompareValue bookingDate, DateCompareValue transactionDate, DateCompareValue currencyDate, std::string refrence, std::string description, float amount, float balance)
	: clearingNum(clearingNum), accountNum(accountNum),productType(productType),currency(currency),bookingDate(bookingDate),transactionDate(transactionDate),currencyDate(currencyDate),refrence(refrence),description(description),amount(amount),balance(balance),dateCompareValue(transactionDate)
{
}

void Transaction::PrintToConsole() const
{
	std::cout << clearingNum << "-" << accountNum << ": " << productType << " => " << refrence << "(" << description << ") av " << amount << " " << currency << ", " << balance << " " << currency << " kvar." << std::endl
		<< "Booking-date:" << bookingDate.ToString()
		<< ", transaction-date:" << transactionDate.ToString()
		<< ", currency-date:" << currencyDate.ToString()
		<< std::endl;
}

bool Transaction::operator==( Transaction & other)
{
	if (other.accountNum != accountNum || other.amount != amount || 
		other.bookingDate != bookingDate|| other.clearingNum != clearingNum ||
		other.currency != currency || other.currencyDate != currencyDate||
		other.description != description || other.productType != productType ||
		other.refrence != refrence || other.transactionDate != transactionDate|| other.balance != balance)
	{
		return false;
	}
	return true;
}

bool Transaction::operator!=(Transaction& other)
{
	if (other.accountNum != accountNum || other.amount != amount ||
		other.bookingDate != bookingDate || other.clearingNum != clearingNum ||
		other.currency != currency || other.currencyDate != currencyDate ||
		other.description != description || other.productType != productType ||
		other.refrence != refrence || other.transactionDate != transactionDate || other.balance != balance)
	{
		return true;
	}
	return false;
}
