/**
Author: Shaan Verma
Date: 2020-10-18
Description: Country.cpp file that implemets the functions of the Country class
**/

#include "Country.h"
#include<iostream>

using namespace std;

/**
Country constructor
Parameters: name, code, new_confirmed_cases, new_deaths, new_recovered_cases,total_confirmed_cases,total_deaths, total_recovered_cases
Description: Takes country COVID-19 data as parameters. name and code are strings, the rest are integers.
Return: Nothing
**/
Country::Country(string name, string code, int new_confirmed_cases, int new_deaths, int new_recovered_cases, int total_confirmed_cases, int total_deaths, int total_recovered_cases)
    : countryName{name}
    , twoLetterCode{code}
    , newConfirmedCases{new_confirmed_cases}
    , newDeaths{new_deaths}
    , newRecoveredCases{new_recovered_cases}
    , totalConfirmedCases{total_confirmed_cases}
    , totalDeaths{total_deaths}
    , totalRecoveredCases{total_recovered_cases}
    {}

/**
Country destructor
Parameters: none
Description: Deconstructs a country object
Return: nothing
**/
Country::~Country(){}

/**
print function
Parameters: none
Description: Outputs a Country object's attributes to the console
Return: nothing

**/
void Country::print()
{
    cout << getCountryName() << "," << getTwoLetterCode() << "," << getNewConfirmedCases() << ","
         << getNewDeaths() << "," << getNewRecoveredCases() << "," << getTotalConfirmedCases() << ","
         << getTotalDeaths() << "," << getTotalRecoveredCases() << endl;
}
