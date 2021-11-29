// Hoang Nguyen

#include <iostream>
#include <exception>
#include "myDate.h"

void getPrintMode(int&);
myDate getDateClass();
int testMode();

int main()
{
    printf("-------------------------------------------------------\n");
    printf("Using default (no) parameter\n");

    myDate dateNoConstructor;
    printf("Full print: %s\n", dateNoConstructor.toString(myDate::PRINT_MODE::FULL).c_str());
    printf("Long print: %s\n", dateNoConstructor.toString(myDate::PRINT_MODE::LONG).c_str());
    printf("Month shorten print: %s\n", dateNoConstructor.toString(myDate::PRINT_MODE::MONTH_SHORTEN).c_str());
    printf("General print: %s\n", dateNoConstructor.toString(myDate::PRINT_MODE::GENERAL).c_str());
    printf("Days of Year: %s\n", dateNoConstructor.toString(myDate::PRINT_MODE::DAYSOFYEAR).c_str());

    printf("-------------------------------------------------------\n");
    printf("Using user input with parameter\n");
    int printMode;
    myDate dateWithConstructor = getDateClass();
    getPrintMode(printMode);
    printf("%s", dateWithConstructor.toString((myDate::PRINT_MODE)printMode).c_str());
    return 0;
}

myDate getDateClass()
{
    std::string userDateIn;
    myDate returnDate;
    
    
    while (!returnDate.verifyDateValid())
    {
        try {
            printf("%s", "\n\nInput Date, MM/DD/YYYY\n");
            std::cin >> userDateIn;
            returnDate = myDate(userDateIn);
        }
        catch (std::invalid_argument& err)
        {
            printf("%s", err.what());
        }
    }
    return returnDate;
}

void getPrintMode(int& in)
{
    printf("Choose Printing mode:\
          \n1) General:         11/17/2021 \
          \n2) Long:            November 17, 2021 \
          \n3) Month shorten :  17-Nov-2021 \
          \n4) Full :           Wednesday, November 17, 2021\
          \n5) Days Of Year:    Day 321 of the year 2021\n");

    std::cin >> in;
    while (!std::cin)
    {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        printf("%s", "Number from 1-5 only\n");
        std::cin >> in;
    }

    switch(in)
    {
        case (int)myDate::PRINT_MODE::GENERAL:
            break;
        case (int)myDate::PRINT_MODE::LONG:
            break;
        case (int)myDate::PRINT_MODE::MONTH_SHORTEN:
            break;
        case (int)myDate::PRINT_MODE::FULL:
            break;
        case (int)myDate::PRINT_MODE::DAYSOFYEAR:
            break;
        default:
            std::cout << "\n\n----------------------------------\nError Unknown mode\n";
            getPrintMode(in);
    }
    return;
}

int testMode()
{
    std::string con[] = {"01/01/1999", "0660199", "0sdfas/1999", "05/01/100174", "81/21/969999", "12/09/1578", "10/31/1749", "04/31/1678"\
    , "07/25/2004", "04/20/1669", "04/01/2819", "02/29/2556", "-1/21/a547", "14/07/3389", "05/01/1419"};

    myDate testDate;
    for (std::string &x: con)
    {
        try{
            testDate = myDate(x);
            printf("\n%s\n", testDate.toString(myDate::PRINT_MODE::FULL).c_str());
        }
        catch (std::invalid_argument &e)
        {
            printf("\n%s\n", e.what());
        }
    }

    return 0;
}
