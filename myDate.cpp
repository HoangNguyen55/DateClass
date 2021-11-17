#include "myDate.h"
#include <stdexcept>
#include <cmath>

const std::string myDate::NUM_TO_DAY[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const int myDate::DAYS_IN_MONTH[13] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const std::string myDate::NUM_TO_MONTH[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
//Saturday
const int myDate::BASE_LINE_TIME[3] = {1, 1, 2000};


myDate::myDate()
{
	month = 0;
	day = 0;
	year = 0;
	isDateValid = false;
	isLeapYear = false;
	dateOfTheYear = 0;
	dayOfTheWeek = "Saturday";
}

myDate::myDate(std::string dateStr)
{
	setDate(dateStr);
}

void myDate::setDate(std::string dateStr)
{
	isDateValid = false;
	for (int i = 0; dateStr[i]; i++)
	{

		if (dateStr[i] == '/')
		{
			if (i == 2)
			{
				month = stoi(dateStr.substr(0, 2));
			}
			else if (i == 5)
			{
				day = stoi(dateStr.substr(3, 2));
			}
			else
			{
				throw std::invalid_argument("Date format unknown '" + dateStr + "' is not 'MM/DD/YYYY'");
			}
		}
		if (i > 10)
		{
			throw std::invalid_argument("Date format unknown, too many characters, use 'MM/DD/YYYY'");
		}
	}
	year = stoi(dateStr.substr(6, 4));

	if (month > 12)
	{
		throw std::invalid_argument("Invalid month, is bigger than 12");
	}
	if (day > DAYS_IN_MONTH[month])
	{
		throw std::invalid_argument("Invalid days, " + std::to_string(DAYS_IN_MONTH[month]) + " is the maximum days for the month of " + NUM_TO_DAY[day]);
	}

	isLeapYear = ((year - BASE_LINE_TIME[2]) % 4 == 0) ? true : false;;
	dayOfTheWeek = calculateDayOfWeek();
	isDateValid = true;
}

std::string myDate::calculateDayOfWeek()
{
	int dayInMonth;
	int yearSinceBase = (year - BASE_LINE_TIME[2]);
	int daySinceBase = (yearSinceBase-1) * 365 + floor((yearSinceBase -1)/ 4);
	for (int i = 1; i < month; i++)
	{

	}
}

bool myDate::verifyDateValid()
{
	return isDateValid;
}

int myDate::getDayOfYear()
{
	return dateOfTheYear;
}