/**
Author: Shaan Verma
Date: 2020-10-18
Description: Country header file that provides a prototype to the country class.
**/

#ifndef COUNTRY_H
#define COUNTRY_H

#include<string>

//Class and memeber functions are explained in Country.cpp
class Country
{
    private:
        std::string countryName, twoLetterCode;
        int newConfirmedCases, newDeaths, newRecoveredCases, totalConfirmedCases, totalDeaths, totalRecoveredCases;

    public:
        Country(std::string name, std::string code, int new_confirmed_cases, int new_deaths, int new_recovered_cases, int total_confirmed_cases, int total_deaths, int total_recovered_cases);
        ~Country();

        //Getters for all attributes of a Country object.
        //Returns either a string or int depending on the metric
        std::string getCountryName(){return countryName;}
        std::string getTwoLetterCode(){return twoLetterCode;}
        int getNewConfirmedCases(){return newConfirmedCases;}
        int getNewDeaths(){return newDeaths;}
        int getNewRecoveredCases(){return newRecoveredCases;}
        int getTotalConfirmedCases(){return totalConfirmedCases;}
        int getTotalDeaths(){return totalDeaths;}
        int getTotalRecoveredCases(){return totalRecoveredCases;}
        void print();
};

#endif // COUNTRY_H
