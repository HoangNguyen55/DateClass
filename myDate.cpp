#include "myDate.h"
#include <stdexcept>

const std::string myDate::NUMTODAY[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const int myDate::DAYSINMONTH[13] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const std::string myDate::NUMTOMONTH[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

myDate::myDate()
{
	month = 0;
	day = 0;
	year = 0;
	isDateValid = false;
	isLeapYear = false;
	dateOfTheYear = 0;
}

myDate::myDate(std::string dateStr)
{
	setDate(dateStr);
}

void myDate::setDate(std::string dateStr)
{
	
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
	if (day > DAYSINMONTH[month])
	{
		throw std::invalid_argument("Invalid days, " + std::to_string(DAYSINMONTH[month]) + " is the maximum days for the month of " + NUMTODAY[day]);
	}

}

bool myDate::getDateValid()
{
	return isDateValid;
}

int myDate::getDayOfYear()
{
	return dateOfTheYear;
}