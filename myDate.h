#pragma once
#include <string>

/*
January – 31 days
February – 28 days in a common year and 29 days in leap years
March – 31 days
April – 30 days
May – 31 days
June – 30 days
July – 31 days
August – 31 days
September – 30 days
October – 31 days
November – 30 days
December – 31 days
*/

/*
	general: 11/17/2021
	long: november 17, 2021
	month shorten: 17-nov-2021
	full: wednesday, november 17, 2021
*/

class myDate
{
	public:
		static enum PRINT_MODE { GENERAL, LONG, MONTH_SHORTEN, FULL };

		void setDate(std::string);
		bool verifyDateValid();
		void toString(int);
		int getDayOfYear();
		bool isALeapYear();

		myDate();
		myDate(std::string);
	private:
		static const std::string NUM_TO_DAY[7];
		static const int DAYS_IN_MONTH[13];
		static const std::string NUM_TO_MONTH[12];
		//MM DD YYYY
		static const int BASE_LINE_TIME[3];

		int month;
		int day;
		int year;

		// 11/15 is the 319th day of the year
		int dateOfTheYear;
		// mondy, sunday, etc...
		std::string dayOfTheWeek;
		bool isDateValid;
		bool isLeapYear;

		std::string calculateDayOfWeek();
};

