#include <iostream>

using namespace std;

short ReadYear()
{
    short Year = 0;
    cout << "Enter a year?\n";
    cin >> Year;
    return Year;
}

bool IsLeapYear(int Year)
{
    if (Year % 400 == 0)
    {
        return true;
    }
    else if (Year % 100 == 0)
    {
        return false;
    }
    else if (Year % 4 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    short Year = ReadYear();

    if (IsLeapYear(Year))
    {
        cout << "\nYes, Year["<<Year<<"] is a Leap Year.\n";
    }
    else
    {
        cout << "\nNo, Year ["<<Year<<"] is not a Leap Year.\n";
    }
}