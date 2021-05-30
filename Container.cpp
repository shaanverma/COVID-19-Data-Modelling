/**
Author: Shaan Verma
Date: 2020-10-18
Description: Container.cpp file that implements the functions of the Container class.
Organizes and cleans data from a CSV file and creates a vector of country objects to
be used to create graphs.
**/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include "Container.h"

using namespace std;

/**
Container constructor
Parameters: fname,fstat,forder
Description: Creates a database of countries by calling a member function. Database is a vector of country objects.
Depending on fstat input, outputs a graph to the console
Return: none
**/
Container::Container(string fname, string fstat, string forder, string ftopBottom) : filename{fname}, stat{fstat} ,order{forder},topBottom{ftopBottom} ,database{}
{
    createDatabase();
    if (fstat == "new confirmed cases") {graphNewConfirmedCases();}
    if (fstat == "new deaths") {graphNewDeaths();}
    if (fstat == "new recovered cases") {graphNewRecoveredCases();}
    if (fstat == "total confirmed cases") {graphTotalConfirmedCases();}
    if (fstat == "total deaths") {graphTotalDeaths();}
    if (fstat == "total recovered cases") {graphTotalRecoveredCases();}
}

/**
Container destructor
Parameters: none
Description:
Return:
**/
Container::~Container()
{}

/**
operator
Parameters:x, y
Description: Overloads the * operator so that a string can be multiplied by an integer.
Return: holder - String representation of the multiplied string
**/
string operator *(float x, string y)
{
    string holder;
    for(int i=0;i<x;i++)
    {
        holder = holder + y;
    }
    return holder;
}

/**
Name: cmpNewConfirmedCases
Parameters: country 1, country 2
Description: Compares the new confimed cases of two country objects using greater than.
Return: A boolean value
**/
bool Container::cmpNewConfirmedCases(Country country1, Country country2)
{
    return country1.getNewConfirmedCases() > country2.getNewConfirmedCases();
}

/**
Name: cmpNewDeaths
Parameters: country 1, country 2
Description: Compares the new deaths of two country objects using greater than.
Return: A boolean value.
**/
bool Container::cmpNewDeaths(Country country1, Country country2)
{
    return country1.getNewDeaths() > country2.getNewDeaths();
}

/**
Name: cmpNewRecoveredCases
Parameters: country 1, country 2
Description: Compares the new recovered cases of two country objects using greater than.
Return: A boolean value
**/
bool Container::cmpNewRecoveredCases(Country country1, Country country2)
{
    return country1.getNewRecoveredCases() > country2.getNewRecoveredCases();
}

/**
Name: cmpTotalConfirmedCases
Parameters: country 1, country 2
Description: Compares the total confirmed cases of two country objects using greater than.
Return: A boolean value
**/
bool Container::cmpTotalConfirmedCases(Country country1, Country country2)
{
    return country1.getTotalConfirmedCases() > country2.getTotalConfirmedCases();
}

/**
Name: cmpGetTotalDeaths
Parameters: country 1, country 2
Description: Compares the total deaths of two country objects using greater than.
Return: A boolean value
**/
bool Container::cmpGetTotalDeaths(Country country1, Country country2)
{
    return country1.getTotalDeaths() > country2.getTotalDeaths();
}

/**
Name: cmpGetTotalRecoveredCases
Parameters: country 1, country 2
Description: Compares the total recovered cases of two country objects using greater than.
Return: A boolean value
**/
bool Container::cmpGetTotalRecoveredCases(Country country1, Country country2)
{
    return country1.getTotalRecoveredCases() > country2.getTotalRecoveredCases();
}

/**
separate
Parameters: s, delimeter
Description: Takes two input strings. s is the string to be delimited, and delimeter is the string that we will
use as a separator. Separated tokens are placed into a vector
Return: The vector holder
**/
vector<string> Container::separate(string s, string delimiter)
{
    vector<string> holder;
    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos)
    {
        token = s.substr(0, pos);
        holder.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    holder.push_back(s);
    return holder;
}

/**
cleanLine
Parameters: s
Description: Takes the vector from the separate method and removes unwanted strings.
Return: first ; A vector with the correct information
**/
vector<string> Container::cleanLine(string s)
{
    vector<string> first = separate(s, "\"");
    string u = first.at(6);
    string v = first.at(10);

    first.erase(first.begin()+4, first.begin() +11);
    first.erase(first.begin()+2);
    first.erase(first.begin());


    vector<string> second = separate(u, ",");
    first.push_back(second.at(1));
    first.push_back(second.at(2));
    first.push_back(second.at(3));


    vector<string> third = separate(v, ",");
    first.push_back(third.at(1));
    first.push_back(third.at(2));
    first.push_back(third.at(3));

    return first;
}

/**
createDatabase
Parameters: none
Description: Populates the attribute database with Country objects. Uses cleanLine method and converToInt method
to place data into parameters of Country object. Also opens and closes data file.
Return: none
**/
void Container::createDatabase()
{
    string myText;
    ifstream MyReadFile(filename);
    getline(MyReadFile, myText);
    while (getline(MyReadFile, myText))
    {
        vector<string> holder = cleanLine(myText);
        string name = holder.at(0);
        string cc = holder.at(1);
        int nc = convertToInt(holder.at(2));
        int nd = convertToInt(holder.at(3));
        int nr = convertToInt(holder.at(4));
        int tc = convertToInt(holder.at(5));
        int td = convertToInt(holder.at(6));
        int tr = convertToInt(holder.at(7));

        Country record(name,cc,nc,nd,nr,tc,td,tr);
        database.push_back(record);
    }
    MyReadFile.close();
}

/**
print
Parameters: none
Description: Prints the database of Country COVID-19 data line by line to the console.
Return: none
**/
void Container::print()
{
    for (vector<Country>::size_type i = 0; i != database.size(); i++)
    {
        database[i].print();
    }
}

/**
convertToInt
Parameters: A holder string
Description: Converts a string type to an integer type.
Return: An integer x
**/
int Container::convertToInt(string holder)
{
    stringstream geek(holder);
    int x = 0;
    geek >> x;
    return x;
}

/**
graphNewConfirmedCases
Parameters: none
Description: Depending on the specified order, graphs the newconfirmedCases metric for the top 10 countries.
Return: none
**/
void Container::graphNewConfirmedCases()
{
    sort(database.begin(), database.end(),cmpNewConfirmedCases);
    string bar = "#";

    if(topBottom == "bottom")
    {
        reverse(database.begin(),database.end());
        reverse(database.begin(),database.begin()+10);
    }

    float factor = ceil((database.at(0).getNewConfirmedCases()+ 0.000000000000000001)/70);


    if (order == "descending")
    {
        for (vector<Country>::size_type i = 0; i < 10; i++)
        {
            float holder = ceil((database.at(i).getNewConfirmedCases())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
    }
    if (order == "ascending")
    {
        for (vector<Country>::size_type i = 9; i > 0; i--)
        {
            float holder = ceil((database.at(i).getNewConfirmedCases())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
        float holder2 = ceil((database.at(0).getNewConfirmedCases())/factor);
        cout << database.at(0).getTwoLetterCode() << " | " <<holder2*bar << endl;
    }

    string dash = "-";
    cout << 75*dash << endl;
    cout << "New Confirmed Cases; Each # is approx. " << factor << " cases";
}

/**
graphNewDeaths
Parameters: none
Description: Depending on the specified order, graphs the newDeaths metric for the top 10 countries.
Return: none
**/
void Container::graphNewDeaths()
{
    sort(database.begin(), database.end(),cmpNewDeaths);
    string bar = "#";

    if(topBottom == "bottom")
    {
       reverse(database.begin(),database.end());
       reverse(database.begin(),database.begin()+10);
    }

    float factor = ceil((database.at(0).getNewDeaths()+ 0.000000000000000001)/70);


    if (order == "descending")
    {
        for (vector<Country>::size_type i = 0; i < 10; i++)
        {
            float holder = ceil((database.at(i).getNewDeaths())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
    }
    if (order == "ascending")
    {
        for (vector<Country>::size_type i = 9; i > 0; i--)
        {
            float holder = ceil((database.at(i).getNewDeaths())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
        float holder2 = ceil((database.at(0).getNewDeaths())/factor);
        cout << database.at(0).getTwoLetterCode() << " | " <<holder2*bar << endl;
    }

    string dash = "-";
    cout << 75*dash << endl;
    cout << "New Deaths; Each # is approx. " << factor << " cases";
}

/**
graphNewRecoveredCases
Parameters: none
Description: Depending on the specified order, graphs the new recovered cases metric for the top 10 countries.
Return: none
**/
void Container::graphNewRecoveredCases()
{
    sort(database.begin(), database.end(),cmpNewRecoveredCases);
    string bar = "#";

    if(topBottom == "bottom")
    {
        reverse(database.begin(),database.end());
        reverse(database.begin(),database.begin()+10);
    }

    float factor = ceil((database.at(0).getNewRecoveredCases() + 0.000000000000000001)/70);

    if (order == "descending")
    {
        for (vector<Country>::size_type i = 0; i < 10; i++)
        {
            float holder = ceil((database.at(i).getNewRecoveredCases())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
    }
    if (order == "ascending")
    {
        for (vector<Country>::size_type i = 9; i > 0; i--)
        {
            float holder = ceil((database.at(i).getNewRecoveredCases())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
        float holder2 = ceil((database.at(0).getNewRecoveredCases())/factor);
        cout << database.at(0).getTwoLetterCode() << " | " <<holder2*bar << endl;
    }

    string dash = "-";
    cout << 75*dash << endl;
    cout << "New Recovered Cases; Each # is approx. " << factor << " cases";
}

/**
graphTotalConfirmedCases
Parameters: none
Description: Depending on the specified order, graphs the total confirmed cases metric for the top 10 countries.
Return: none
**/
void Container::graphTotalConfirmedCases()
{
    sort(database.begin(), database.end(),cmpTotalConfirmedCases);
    string bar = "#";

    if(topBottom == "bottom")
    {
        reverse(database.begin(),database.end());
        reverse(database.begin(),database.begin()+10);

    }

    float factor = ceil((database.at(0).getTotalConfirmedCases() + 0.000000000000000001)/70);

    if (order == "descending")
    {
        for (vector<Country>::size_type i = 0; i < 10; i++)
        {
            float holder = ceil((database.at(i).getTotalConfirmedCases())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
    }
    if (order == "ascending")
    {
        for (vector<Country>::size_type i = 9; i > 0; i--)
        {
            float holder = ceil((database.at(i).getTotalConfirmedCases())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
        float holder2 = ceil((database.at(0).getTotalConfirmedCases())/factor);
        cout << database.at(0).getTwoLetterCode() << " | " <<holder2*bar << endl;
    }

    string dash = "-";
    cout << 75*dash << endl;
    cout << "Total Confirmed Cases; Each # is approx. " << factor << " cases";
}

/**
graphTotalDeaths
Parameters: none
Description: Depending on the specified order, graphs the total deaths metric for the top 10 countries.
Return: none
**/
void Container::graphTotalDeaths()
{
    sort(database.begin(), database.end(),cmpGetTotalDeaths);
    string bar = "#";

    if(topBottom == "bottom")
    {
        reverse(database.begin(),database.end());
        reverse(database.begin(),database.begin()+10);
    }

    float factor = ceil((database.at(0).getTotalDeaths()+0.000000000000000001)/70);

    if (order == "descending")
    {
        for (vector<Country>::size_type i = 0; i < 10; i++)
        {
            float holder = ceil((database.at(i).getTotalDeaths())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
    }
    if (order == "ascending")
    {
        for (vector<Country>::size_type i = 9; i > 0; i--)
        {
            float holder = ceil((database.at(i).getTotalDeaths())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
        float holder2 = ceil((database.at(0).getTotalDeaths())/factor);
        cout << database.at(0).getTwoLetterCode() << " | " <<holder2*bar << endl;
    }

    string dash = "-";
    cout << 75*dash << endl;
    cout << "Total Deaths; Each # is approx. " << factor << " cases";
}

/**
graphTotalRecoveredCases
Parameters: none
Description: Depending on the specified order, graphs the total recovered cases metric for the top 10 countries.
Return: none
**/
void Container::graphTotalRecoveredCases()
{
    sort(database.begin(), database.end(),cmpGetTotalRecoveredCases);
    string bar = "#";

    if(topBottom == "bottom")
    {
        reverse(database.begin(),database.end());
        reverse(database.begin(),database.begin()+10);
    }

     float factor = ceil((database.at(0).getTotalRecoveredCases()+0.000000000000000001)/70);

    if (order == "descending")
    {
        for (vector<Country>::size_type i = 0; i < 10; i++)
        {
            float holder = ceil((database.at(i).getTotalRecoveredCases())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
    }
    if (order == "ascending")
    {
        for (vector<Country>::size_type i = 9; i > 0; i--)
        {
            float holder = ceil((database.at(i).getTotalRecoveredCases())/factor);
            cout << database.at(i).getTwoLetterCode() << " | " <<holder*bar << endl;
        }
        float holder2 = ceil((database.at(0).getTotalRecoveredCases())/factor);
        cout << database.at(0).getTwoLetterCode() << " | " <<holder2*bar << endl;
    }

    string dash = "-";
    cout << 75*dash << endl;
    cout << "Total Recovered Cases; Each # is approx. " << factor << " cases";
}





