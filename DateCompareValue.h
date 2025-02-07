#pragma once
#include <string>
struct DateCompareValue
{
	unsigned long value;
	std::tm date;
	unsigned int Year() const;
	unsigned int Month() const;
	unsigned int Day() const;
	unsigned int GetMonthLength() const;
	unsigned int SetYearTo(unsigned int);
	unsigned int SetMonthTo(unsigned int);
	unsigned int SetDayTo(unsigned int);
	unsigned int ChangeYearTo(int);
	unsigned int ChangeMonthTo(int);
	unsigned int ChangeDayTo(int);
	unsigned int GetMonthLength(unsigned int) const;

	DateCompareValue();
	DateCompareValue(unsigned int, unsigned int, unsigned int);
	DateCompareValue(const std::tm&);
	DateCompareValue(std::string &);
	std::string ToString() const;
	DateCompareValue operator=(DateCompareValue const&);
	bool operator == (DateCompareValue const&);
	bool operator != (DateCompareValue const&);
	bool operator < (DateCompareValue const&);
	bool operator <= (DateCompareValue const&);
	bool operator > (DateCompareValue const&);
	bool operator >= (DateCompareValue const&);
};

