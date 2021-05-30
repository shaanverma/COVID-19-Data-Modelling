/**
Author: Shaan Verma
Date: 2020-10-18
Description: main.cpp file that provides a system of prompts asking a user for what kind of data they want to graph.
**/

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Container.h"

using namespace std;

int main()
{
    string userFile,statCount,order,checker, topBottom;
    cout << "#####################################################################################\n" << endl;
    cout << "CS 3307 ASSIGNMENT #1: COVID-19 DATA ANALYZER\n" << endl;
    cout << "#####################################################################################" << endl;
    cout << "\nPLEASE INPUT A CSV FILE" << endl;
    cout << "FILENAME: ";
    getline(cin, userFile);

    //Checks if the file is valid
    while(!fstream{userFile})
    {
        cout << "\nFILE DOES NOT EXIST TRY AGAIN" << endl;
        cout << "\nFILENAME: ";
        getline(cin, userFile);
    }

    //Loop to acces more than 1 stat count
    while (true)
    {
        cout << "\n#####################################################################################" << endl;

        //Loop to ensure input is correct
        while(true)
        {
            cout << "\nPLEASE SELECT A STATISTICAL COUNT:" << endl;
            cout << "\n\"new confirmed cases\"  \"new deaths\"  \"new recovered cases" << endl;
            cout << "\n\"total confirmed cases\"  \"total deaths\"  \"total recovered cases\"" << endl;
            cout << "\nSTAT COUNT: ";
            getline(cin, statCount);

            //Converts to lowercase
            transform(statCount.begin(), statCount.end(), statCount.begin(), ::tolower);

            if ((statCount == "new confirmed cases") | (statCount == "new deaths") | (statCount == "new recovered cases") |
                (statCount == "total confirmed cases") | (statCount == "total deaths") | (statCount == "total recovered cases"))
            {
                break;
            }
            cout << "INVALID STAT COUNT!" << endl;
        }

        cout << "\n#####################################################################################" << endl;

        //Loop to ensure input is correct
        while(true)
        {
            cout << "\nASCENDING OR DESCENDING?: ";
            getline(cin, order);

            //Converts to lowercase
            transform(order.begin(), order.end(), order.begin(), ::tolower);

            if ((order == "ascending") | (order == "descending"))
            {
                break;
            }
            cout << "\nINVALID ORDER SELECTION!" << endl;
        }

        cout << "\n#####################################################################################" << endl;

         //Loop to ensure input is correct
        while(true)
        {
            cout << "\nTop 10 data or bottom 10 data?(\"top\" , \"bottom\"): ";
            getline(cin, topBottom);

            //Converts to lowercase
            transform(topBottom.begin(), topBottom.end(), topBottom.begin(), ::tolower);

            if ((topBottom == "top") | (topBottom == "bottom"))
            {
                break;
            }
            cout << "\nINVALID TOP/BOTTOM DATA SELECTION!" << endl;
        }

        cout << "\n-----------------------------------------------------------------------------\n" << endl;

        //Creates graph based on user choices
        Container userData(userFile,statCount,order,topBottom);

        cout << "\n\nTYPE \"STOP\" TO EXIT OR PRESS ENTER TO CONTINUE: ";

        getline(cin, checker);
        transform(checker.begin(), checker.end(), checker.begin(), ::tolower);

        //Exit clause to leave program
        if(checker == "stop")
        {break;}

    }
    return 0;
}
