/*
Final Project Milestone 1
Module: utils
Filename: utils.cpp
Version 1.0
Author	Aleksandr Valuev
Revision History
-----------------------------------------------------------
Date      Reason
2020/03/16  Preliminary release
2020/03/16  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
#include <cstring>
using namespace std;
namespace sdds {
   bool debug = false;  // made global in utils.h
   int getTime() {  
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   // needs extraction operator overloaded for Time
            if (!cin) {
               cout << "Invlid time, try agian (HH:MM): ";
               cin.clear();
            }
            else {
               mins = int(t);
            }
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }
   int getInt(const char* prompt) {
       int value = 0;
       bool failedEntry;
       char ch;
       if (prompt) cout << prompt;
       do {
           failedEntry = false;
           cin >> value;
           cin.get(ch);
           if (cin.fail()) {
               cout << "Bad integer value, try again: ";
               cin.clear();
               cin.ignore(1000, '\n');
               failedEntry = true;
           }
           else {
               if (ch != '\n') {
                   cout << "Enter only an integer, try again: ";
                   cin.clear();
                   cin.ignore(1000, '\n');
                   failedEntry = true;
               }
           }
       } while (failedEntry);
       return value;
   }
   int getInt(int min, int max, const char* prompt, const char* errorMessage , bool showRangeAtError) {
       int value = 0;
           value = getInt(prompt);
           while (value < min || value > max) {
               if (errorMessage) cerr << errorMessage;
               if (showRangeAtError) cout << "[" << min << " <= value <= " << max << "]: ";
               value = getInt();
           }
       return value;
   }

   char* getcstr(const char* prompt, std::istream& istr, char delimiter) {
       char* entryStr;
       if (prompt) cout << prompt;

       string str; 
       getline(istr, str, delimiter);
       entryStr = new char[str.length() + 1];
       strcpy(entryStr, str.c_str());
       return entryStr;
   }
}