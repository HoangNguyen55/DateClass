#include "myDate.h"
#include <stdexcept>
#include <cmath>
#include <string>

const std::string myDate::NUM_TO_DAY[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const int myDate::DAYS_IN_MONTH[13] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//Add random element to 0th position to make the number match up, 1 = jan, etc...
const std::string myDate::NUM_TO_MONTH[13] = {"NA", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
//Saturday
const int myDate::BASE_LINE_TIME = 2000;


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

myDate::myDate(std::string dateStr)
{
	setDate(dateStr);
}

void myDate::setDate(std::string dateStr)
{
	int monthToCheck;

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

	//11 to account for the fact that array start at 0 instead of 1
	if (month > 11)
	{
		throw std::invalid_argument("Invalid month, is bigger than 12");
	}

	// Ternary operation, will calculate if year since the 2000 are divisible by 4, if yes it is a leap year
	isLeapYear = ((year - BASE_LINE_TIME) % 4 == 0) ? true : false;;

	monthToCheck = (isLeapYear && month == 2) ? DAYS_IN_MONTH[0] : DAYS_IN_MONTH[month];

	if (day > month)
	{
		char errorMsg[200];
		sprintf(errorMsg, "Invalid days, %s is the maximum days for the month of %s", std::to_string(DAYS_IN_MONTH[month]).c_str(), NUM_TO_MONTH[month].c_str());
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
			sprintf(returnStr, "%d/%d/%d", month, day, year);
			break;
		case PRINT_MODE::LONG:
			sprintf(returnStr, "%s %d, %d", NUM_TO_MONTH[month].c_str(), day, year);
			break;
		case PRINT_MODE::MONTH_SHORTEN:
			sprintf(returnStr, "%d-%s-%d", day, NUM_TO_MONTH[month].substr(0, 3).c_str(), year);
			break;
		case PRINT_MODE::FULL:
			sprintf(returnStr, "%s, %s %d, %d", NUM_TO_DAY[dayOfTheWeek].c_str(), NUM_TO_MONTH[month].c_str(), day, year);
			break;
		default:
			break;
	}
	
}


int myDate::calculateDayOfWeek()
{
	int yearSinceBase = (year - BASE_LINE_TIME - 1);
	int daySinceBase = (yearSinceBase) * 365 + floor((yearSinceBase)/ 4);
	
	daySinceBase += calculateDayOfYear();

	return daySinceBase % 7;
}

int myDate::calculateDayOfYear()
{
	int dayInMonth;
	int DaysTotalInMonth = 0;
	for (int i = 1; i < month; i++)
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