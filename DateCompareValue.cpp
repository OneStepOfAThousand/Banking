#include "DateCompareValue.h"
/// <summary>
/// The year of the date compare value.
/// </summary>
/// <returns></returns>
unsigned int DateCompareValue::Year() const
{
	return (unsigned int)(value >> 9);
}
/// <summary>
/// The month of the date compare Value.
/// </summary>
/// <returns></returns>
unsigned int DateCompareValue::Month() const
{
	return (unsigned int)((value >> 5) & 0b1111);
}
/// <summary>
/// The day of the date compare value.
/// </summary>
/// <returns></returns>
unsigned int DateCompareValue::Day() const
{
	return (unsigned int)(value & 0b11111);
}
/// <summary>
/// The length of the date compare value's current month.
/// </summary>
/// <returns></returns>
unsigned int DateCompareValue::GetMonthLength() const
{
	switch (Month())
	{
	case 1://January
		return 31;
	case 2://February
		return (Year() % 4) == 0 ? 29 : 28;
	case 3://March
		return 31;
	case 4://April
		return 30;
	case 5://May
		return 31;
	case 6://June
		return 30;
	case 7://July
		return 31;
	case 8://August
		return 31;
	case 9://September
		return 30;
	case 10://October
		return 31;
	case 11://November
		return 30;
	case 12://December
		return 31;
	default:
		break;
	}
}
/// <summary>
/// <para>
/// Sets the year of the date compare value.
/// </para>
/// <para>
/// OBS: Use ChangeYearTo(val) instead.
/// </para>
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
unsigned int DateCompareValue::SetYearTo(unsigned int val)
{
	date.tm_year = val;
	value &= 0b111111111;
	value |= ((unsigned long)val << 9);
	return (unsigned int)(value >> 9);
}
/// <summary>
/// <para>
/// Sets the month of the date compare value.
/// </para>
/// <para>
/// OBS: Use ChangeMonthTo(val) instead.
/// </para>
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
unsigned int DateCompareValue::SetMonthTo(unsigned int val)
{
	date.tm_mon = val;
	value &= 0b111111111111000011111;
	value |= ((unsigned long)val << 5);
	return (unsigned int)((value >> 5) & 0b111111111);
}
/// <summary>
/// <para>
/// Sets the day of the date compare value.
/// </para>
/// <para>
/// OBS: Use ChangeDayTo(val) instead.
/// </para>
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
unsigned int DateCompareValue::SetDayTo(unsigned int val)
{
	date.tm_mday = val;
	value &= 0b111111111111111100000;
	value |= ((unsigned long)val);
	return (unsigned int)(value & 0b11111);
}
/// <summary>
/// <para>
/// Changes the year of the date compare value.
/// </para>
/// <para>
/// The Change"X"To(val) functions handles out of bounds iterations by iterating the larger based values.
/// </para>
/// <para>
/// Ex: Calling ChangeDayTo(32) when Month() == 1 will iterate the month of the date compare value to 2 and the day of the date compare value to 1.
/// </para>
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
unsigned int DateCompareValue::ChangeYearTo(int val)
{
	return SetYearTo(val);
}
/// <summary>
/// <para>
/// Changes the month of the date compare value.
/// </para>
/// <para>
/// The Change"X"To(val) functions handles out of bounds iterations by iterating the larger based values.
/// </para>
/// <para>
/// Ex: Calling ChangeDayTo(32) when Month() == 1 will iterate the month of the date compare value to 2 and the day of the date compare value to 1.
/// </para>
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
unsigned int DateCompareValue::ChangeMonthTo(int val)
{
	while (val < 1)
	{
		ChangeYearTo(Year() - 1);
		val += 12;
	}
	while (val > 12)
	{
		ChangeYearTo(Year() + 1);
		val -= 12;
	}
	return SetMonthTo(val);
}
/// <summary>
/// <para>
/// Changes the day of the date compare value.
/// </para>
/// <para>
/// The Change"X"To(val) functions handles out of bounds iterations by iterating the larger based values.
/// </para>
/// <para>
/// Ex: Calling ChangeDayTo(32) when Month() == 1 will iterate the month of the date compare value to 2 and the day of the date compare value to 1.
/// </para>
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
unsigned int DateCompareValue::ChangeDayTo(int val)
{
	while (val < 0)
	{
		ChangeMonthTo(Month() - 1);
		if (Day() != 0)
		{
			val += Day();
			SetDayTo(0);
		}
		val += GetMonthLength(Month());
	}
	while (val > GetMonthLength())
	{
		if (Day() != 1)
		{
			val -= Day();
			SetDayTo(1);
		}
		if ((val >= GetMonthLength()))
		{
			val -= GetMonthLength(Month());
		}
		ChangeMonthTo(Month() + 1);
	}
	SetDayTo(val);
	return Day();
}
/// <summary>
/// Returns the length of the specified month.
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
unsigned int DateCompareValue::GetMonthLength(unsigned int val) const
{
	switch (val)
	{
	case 1://January
		return 31;
	case 2://February
		return ((Year() % 4) == 0 ? 29 : 28);
	case 3://March
		return 31;
	case 4://April
		return 30;
	case 5://May
		return 31;
	case 6://June
		return 30;
	case 7://July
		return 31;
	case 8://August
		return 31;
	case 9://September
		return 30;
	case 10://October
		return 31;
	case 11://November
		return 30;
	case 12://December
		return 31;
	default:
		break;
	}
}

DateCompareValue::DateCompareValue()
{
	value = 0;
	date = std::tm();
}

DateCompareValue::DateCompareValue(unsigned int year, unsigned int month, unsigned int day)
{
	value = (unsigned long long)day | ((unsigned long long)month << 5) | ((unsigned long long)year << 9);
	date = std::tm();
	date.tm_year = year;
	date.tm_mon = month - 1;
	date.tm_mday = day;
}

DateCompareValue::DateCompareValue(const std::tm& date) :date(date)
{
	value = (unsigned long long)date.tm_mday | ((unsigned long long)date.tm_mon << 5) | ((unsigned long long)date.tm_year << 9);
}

DateCompareValue::DateCompareValue(std::string& dateInString)
{
	SetYearTo(std::stoul(dateInString.substr(0, 4)));
	SetMonthTo(std::stoul(dateInString.substr(5, 2)));
	SetDayTo(std::stoul(dateInString.substr(8, 2)));
}

std::string DateCompareValue::ToString() const
{
	std::string val;
	val += std::to_string(Year());
	val += ":";
	val += std::to_string(Month());
	val += ":";
	val += std::to_string(Day());
	return val;
}

DateCompareValue DateCompareValue::operator=(DateCompareValue const& other)
{
	value = other.value;
	date = other.date;
	return DateCompareValue();
}

bool DateCompareValue::operator==(DateCompareValue const& other)
{
	return value == other.value;
}

bool DateCompareValue::operator!=(DateCompareValue const& other)
{
	return value != other.value;
}

bool DateCompareValue::operator<(DateCompareValue const& other)
{
	return value < other.value;
}

bool DateCompareValue::operator<=(DateCompareValue const& other)
{
	return value <= other.value;
}

bool DateCompareValue::operator>(DateCompareValue const& other)
{
	return value > other.value;
}

bool DateCompareValue::operator>=(DateCompareValue const& other)
{
	return value >= other.value;
}