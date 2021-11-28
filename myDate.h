#pragma once
#include <string>

/*
January - 31 days
February - 28 days in a common year and 29 days in leap years
March - 31 days
April - 30 days
May - 31 days
June - 30 days
July - 31 days
August - 31 days
September - 30 days
October - 31 days
November - 30 days
December - 31 days
*/

/*
	general: 11/17/2021
	long: november 17, 2021
	month shorten: 17-nov-2021
	full: wednesday, november 17, 2021
*/

class myDate
{
	private:
		// declare static variables
		static const std::string NUM_TO_DAY[7];
		static const unsigned int DAYS_IN_MONTH[13];
		static const std::string NUM_TO_MONTH[13];
		// for doomsday rule
		static const int BASE_LINE_TIME[2];
		static const int DOOMSDAY_ANCHOR[4];

		// unsigned since dates don't need to be negative
		unsigned int month;
		unsigned int day;
		unsigned int year;

		// 11/15 is the 319th day of the year
		int dateOfTheYear;
		// monday, sunday, etc...
		std::string dayOfTheWeek;
		bool isDateValid;
		bool isLeapYear;

		std::string calculateDayOfWeek();
		int calculateDayOfYear();

	public:
		enum class PRINT_MODE { GENERAL=1, LONG, MONTH_SHORTEN, FULL, DAYSOFYEAR};

		void setDate(std::string);
		bool verifyDateValid();
		std::string toString(PRINT_MODE);
		int getDayOfYear();
		bool isALeapYear();

		myDate();
		myDate(std::string);
	
};

