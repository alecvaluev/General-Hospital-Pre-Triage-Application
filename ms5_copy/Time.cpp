/*
Final Project Milestone 1
Module: Time
Filename: Time.cpp
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
#include "Time.h"
#include "utils.h"
#include <iostream>
using namespace std;
namespace sdds {
    Time& Time::setToNow() {
        m_min = getTime();
        return *this;
    };
    Time::Time(unsigned int min) {
        m_min = min;
    };
    std::ostream& Time::write(std::ostream& ostr) const {
        
        unsigned int hours = m_min / 60;
        unsigned int minutes = m_min % 60;
        
        if (hours < 10) ostr << "0";
        ostr << hours << ":";
        if (minutes < 10) ostr << "0";
        ostr << minutes;

        return ostr;
    };
    std::istream& Time::read(std::istream& istr) {
        int hours = -1;
        int minutes = -1;
        char ch = '\0';
        istr >> hours;
        if (hours < 0) istr.setstate(ios::failbit);
        istr >> ch;
        if (ch != ':') istr.setstate(ios::failbit);
        istr >> minutes;
        if (minutes < 0) istr.setstate(ios::failbit);

        if (istr.good())m_min = (hours * 60) + minutes;
        return istr;
    };
    Time& Time::operator-=(const Time& D) {
        while (D.m_min > m_min) m_min += 24 * 60;
        m_min -= D.m_min;
        return *this;
    };
    Time Time::operator-(const Time& D)const {
        Time time(m_min);
        while (D.m_min > time.m_min) time.m_min += 24 * 60;
        time.m_min -= D.m_min;
        return time;
    };
    Time& Time::operator+=(const Time& D) {
        m_min += D.m_min;
        return *this;
    };
    Time Time::operator+(const Time& D)const {
        Time time(m_min + D.m_min);
        return time;
    };
    Time& Time::operator=(unsigned int val) {
        m_min = val;
        return *this;
    };
    Time& Time::operator *= (unsigned int val) {
        m_min *= val;
        return *this;
    };
    Time& Time::operator /= (unsigned int val) {
        m_min /= val;
        return *this;
    };
    Time Time::operator *(unsigned int val)const {
        Time time(m_min * val);
        return time;
    };
    Time Time::operator /(unsigned int val)const {
        Time time(m_min / val);
        return time;
    };
    Time::operator unsigned int()const {
        return m_min;
    };
    Time::operator int()const {
        return (int)m_min;
    };
    std::ostream& operator<<(std::ostream& ostr, const Time& D) {
        D.write(ostr);
        return ostr;
    };
    std::istream& operator>>(std::istream& istr, Time& D) {
        D.read(istr);
        return istr;
    };
}