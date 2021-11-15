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

class myDate
{
	public:
		void setDate(std::string);
		// isDateValid() ????????
		bool getDateValid();
		void printDate(int);
		int getDayOfYear();

		myDate();
		myDate(std::string);
	private:
		static const std::string NUMTODAY[7];
		static const int DAYSINMONTH[13];
		static const std::string NUMTOMONTH[12];
		
		int month;
		int day;
		int year;

		// 11/15 is the 319th day of the year
		int dateOfTheYear;
		// mondey, sunday, etc...
		int dayOfTheWeek;
		bool isDateValid;
		bool isLeapYear;
};

