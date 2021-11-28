#include "myDate.h"
#include <stdexcept>
#include <cmath>
#include <string>

const std::string myDate::NUM_TO_DAY[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// Number of days per month, 0th element for feb of leap year
const unsigned int myDate::DAYS_IN_MONTH[13] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
// Add random element to 0th position to make the number match up, 1 = jan, etc...
const std::string myDate::NUM_TO_MONTH[13] = {"N/A", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
// base time to use for doomsday rule for days of week calculation
// 3rd if non leap year, 4th of leap year
const int myDate::BASE_LINE_TIME[2] = {3, 4};
const int myDate::DOOMSDAY_ANCHOR[4] = {5, 3, 2, 0};

// Default Constructor
myDate::myDate()
{
	month = 0;
	day = 0;
	year = 0;
	isDateValid = false;
	isLeapYear = false;
	dateOfTheYear = 0;
	dayOfTheWeek = "N/A";
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

	// will calculate if the year are divisible by 4, if yes it is a leap year
	if (year % 4 == 0)
	{
		isLeapYear = true;
		// if the year is not divisible by 400 set it to false
		if (year % 100 == 0 && year % 400 != 0)
		{
			isLeapYear = false;
		} 
	}
	else
	{
		isLeapYear = false;
	}

	// if year is a leap year and month is feburary value will be 29
	// else it will be whatever the days that the month have normally
	monthToCheck = (isLeapYear && month == 2) ? DAYS_IN_MONTH[0] : DAYS_IN_MONTH[month];

	if (day > monthToCheck)
	{
		char errorMsg[100];
		sprintf_s(errorMsg, "Invalid days, %d is the maximum days for the month of %s for the year %d", \
			monthToCheck, NUM_TO_MONTH[month].c_str(), year);
		throw std::invalid_argument(errorMsg);
	}
	
	dayOfTheWeek = calculateDayOfWeek();
	isDateValid = true;
}

std::string myDate::toString(PRINT_MODE mode)
{
	char returnStr[100];
	switch (mode)
	{
		case PRINT_MODE::GENERAL:
			sprintf_s(returnStr, "%d/%d/%d\n", month, day, year);
			break;
		case PRINT_MODE::LONG:
			sprintf_s(returnStr, "%s %d, %d\n", NUM_TO_MONTH[month].c_str(), day, year);
			break;
		case PRINT_MODE::MONTH_SHORTEN:
			sprintf_s(returnStr, "%d-%s-%d\n", day, NUM_TO_MONTH[month].substr(0, 3).c_str(), year);
			break;
		case PRINT_MODE::FULL:
			sprintf_s(returnStr, "%s, %s %d, %d\n", dayOfTheWeek.c_str(), NUM_TO_MONTH[month].c_str(), day, year);
			break;
		case PRINT_MODE::DAYSOFYEAR:
			sprintf_s(returnStr, "Day %d of the year %d", calculateDayOfYear(), year);
			break;
		default:
			sprintf_s(returnStr, "Error mode unknown");
			break;
	}
	return returnStr;
}


std::string myDate::calculateDayOfWeek()
{
	std::string returnStr;
	// anchor day alternate in a 400 year-cycle with a pattern of 5,3,2,0
	// getting the anchor day
	int anchor = DOOMSDAY_ANCHOR[((year - 1400)/100) % 4];
	// get the last 2 digit of the year
	int lastDigit = year % 100;
	
	// determining dooms day of the year
	// add 11 if the last digit is not even
	lastDigit += (lastDigit % 2 != 0) ? 11 : 0;
	// divide by 2
	lastDigit /= 2;
	// add 11 again if it is not even
	lastDigit += (lastDigit % 2 != 0) ? 11 : 0;
	int doomsResult = std::abs((lastDigit % 7) - 7) + anchor;

	// subtract 7 if the result is greater than or equal to 7
	doomsResult -= (doomsResult >= 7) ? 7 : 0;
	int doomsday = (isLeapYear) ? BASE_LINE_TIME[1] : BASE_LINE_TIME[0];

	int dayOfWeekResult = (calculateDayOfYear() - doomsday + doomsResult) % 7;
	if (dayOfWeekResult < 0)
	{
		returnStr = NUM_TO_DAY[7 + dayOfWeekResult];
	} 
	else
	{
		returnStr = NUM_TO_DAY[dayOfWeekResult];
	}

	return returnStr;
}

int myDate::calculateDayOfYear()
{
	int dayInMonth;
	int DaysTotalInMonth = 0;
	for (int unsigned i = 1; i < month; i++)
	{
		// ternary oparation, if the year is a leap year and the month is the 2nd month, use 29 days instead of 28
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