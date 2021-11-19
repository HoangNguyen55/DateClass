#include "myDate.h"
#include <stdexcept>
#include <cmath>
#include <string>

const std::string myDate::NUM_TO_DAY[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
// Number of days per month, 0th element for feb of leap year
const unsigned int myDate::DAYS_IN_MONTH[13] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
// Add random element to 0th position to make the number match up, 1 = jan, etc...
const std::string myDate::NUM_TO_MONTH[13] = {"N/A", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
// 1 jan of 1752 is Saturday
const int myDate::BASE_LINE_TIME = 1752;

// Default Constructor
myDate::myDate()
{
	month = 0;
	day = 0;
	year = 0;
	isDateValid = false;
	isLeapYear = false;
	dateOfTheYear = 0;
	dayOfTheWeek = 6;
}

// Constructor with parameter
myDate::myDate(std::string dateStr)
{
	setDate(dateStr);
}

void myDate::setDate(std::string dateStr)
{
	int monthToCheck;
	int counter = 0;
	// No return statement is use because 
	// if there were to be error the throw statement 
	// would make return statement obsolete
	isDateValid = false;

	for (; dateStr[counter]; counter++)
	{

		if (dateStr[counter] == '/')
		{
			if (counter == 2)
			{
				month = stoi(dateStr.substr(0, 2));
			}
			else if (counter == 5)
			{
				day = stoi(dateStr.substr(3, 2));
			}
			else
			{
				throw std::invalid_argument("Date format unknown '" + dateStr + "' is not 'MM/DD/YYYY'");
			}
		}
	}

	if (counter != 10)
	{
		throw std::invalid_argument("Date format unknown, unmatch characters, use 'MM/DD/YYYY'");
	}
	year = stoi(dateStr.substr(6, 4));

	if (month > 12)
	{
		throw std::invalid_argument("Invalid month, is bigger than 12");
	}

	// Ternary operation, will calculate if the year are divisible by 4, if yes it is a leap year
	isLeapYear = (year == 0) ? true : false;

	// if year is a leap year and month is feburary value will be 29
	// else it will be whatever the days that the month have normally
	monthToCheck = (isLeapYear && month == 2) ? DAYS_IN_MONTH[0] : DAYS_IN_MONTH[month];

	if (day > DAYS_IN_MONTH[month])
	{
		char errorMsg[200];
		sprintf_s(errorMsg, "Invalid days, %d is the maximum days for the month of %s for the year %d", \
			monthToCheck, NUM_TO_MONTH[month].c_str(), year);
		throw std::invalid_argument(errorMsg);
	}
	
	dayOfTheWeek = calculateDayOfWeek();
	isDateValid = true;
}

std::string myDate::toString(PRINT_MODE mode)
{
	char returnStr[50];
	switch (mode)
	{
		case PRINT_MODE::GENERAL:
			sprintf_s(returnStr, "%d/%d/%d", month, day, year);
			break;
		case PRINT_MODE::LONG:
			sprintf_s(returnStr, "%s %d, %d", NUM_TO_MONTH[month].c_str(), day, year);
			break;
		case PRINT_MODE::MONTH_SHORTEN:
			sprintf_s(returnStr, "%d-%s-%d", day, NUM_TO_MONTH[month].substr(0, 3).c_str(), year);
			break;
		case PRINT_MODE::FULL:
			sprintf_s(returnStr, "%s, %s %d, %d", NUM_TO_DAY[dayOfTheWeek].c_str(), NUM_TO_MONTH[month].c_str(), day, year);
			break;
		default:
			sprintf_s(returnStr, "Error mode unknown");
			break;
	}
	return returnStr;
}


int myDate::calculateDayOfWeek()
{

	int yearSinceBase = (year - BASE_LINE_TIME - 1);
	int daySinceBase = (yearSinceBase) * 365 + ((yearSinceBase)/ 4);
	
	daySinceBase += calculateDayOfYear();

	return daySinceBase % 7;
}

int myDate::calculateDayOfYear()
{
	int dayInMonth;
	int DaysTotalInMonth = 0;
	for (int unsigned i = 1; i < month; i++)
	{
		// if the year is a leap year and the month is the 2nd month, use 29 days instead of 28
		dayInMonth = (isLeapYear && i == 2) ? DAYS_IN_MONTH[0] : DAYS_IN_MONTH[i];

		DaysTotalInMonth += dayInMonth;
	}
	return DaysTotalInMonth + day;
}

bool myDate::verifyDateValid()
{
	return isDateValid;
}

bool myDate::isALeapYear()
{
	return isLeapYear;
}

int myDate::getDayOfYear()
{
	return dateOfTheYear;
}