/**
Author: Shaan Verma
Date: 2020-10-18
Description: Container header file that provides a prototype to the country class. Contains static members
that can be used without instantiating an object.
**/


#ifndef CONTAINER_H
#define CONTAINER_H
#include<string>
#include<vector>
#include"Country.h"

class Container
{
    private:
        std::string filename, stat ,order, topBottom;
        std::vector<Country> database;

    public:
        Container(std::string fname, std::string fstat ,std::string forder, std::string ftopBottom);
        ~Container();

        //Comparision functions made static for use with std::sort() method
        static bool cmpNewConfirmedCases(Country country1, Country country2);
        static bool cmpNewDeaths(Country country1, Country country2);
        static bool cmpNewRecoveredCases(Country country1, Country country2);
        static bool cmpTotalConfirmedCases(Country country1, Country country2);
        static bool cmpGetTotalDeaths(Country country1, Country country2);
        static bool cmpGetTotalRecoveredCases(Country country1, Country country2);

    private:
        //Helper methods to prepare and organize data
        std::vector<std::string> separate(std::string s, std::string delimiter);
        std::vector<std::string> cleanLine(std::string s);
        void createDatabase();

    public:
        //getters and conversion methods
        void print();
        int convertToInt(std::string holder);
        std::vector<Country> getDatabase(){return database;}
        std::string getFilename(){return filename;}
        std::string getOrder(){return order;}
        std::string getStat(){return stat;}

        //Graphing methods for each metric
        void graphNewConfirmedCases();
        void graphNewDeaths();
        void graphNewRecoveredCases();
        void graphTotalConfirmedCases();
        void graphTotalDeaths();
        void graphTotalRecoveredCases();
};
#endif // CONTAINER_H
