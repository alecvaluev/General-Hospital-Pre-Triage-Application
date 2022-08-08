/*
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	Aleksandr Valuev
Revision History
-----------------------------------------------------------
Date      Reason
2020/03/22  Preliminary release
2020/03/22  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
#include "utils.h"
#include <cstring>
using namespace std;

namespace sdds {
    Menu::Menu(const char* MenuContent, int NoOfSelections) {
        m_text = new char[strlen(MenuContent) + 1];
        strcpy(m_text, MenuContent);
        m_noOfSel = NoOfSelections;
    };
    Menu::~Menu() {
        delete[] m_text;
    };
    Menu::Menu(const Menu& menuCopy) {
        m_noOfSel = menuCopy.m_noOfSel;
        m_text = new char[strlen(menuCopy.m_text) + 1];
        strcpy(m_text, menuCopy.m_text);
    };
    void Menu::display()const {
        cout << m_text << endl;
        cout << "0- Exit" << endl;
    }
    int& Menu::operator>>(int& Selection) {
        display();
        Selection = getInt(0, m_noOfSel, "> ", "Invalid option ");
        return Selection;
    };
}