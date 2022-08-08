/*
Final Project Milestone 3
Module: Patient
Filename: Patient.cpp
Version 1.0
Author	Aleksandr Valuev
Revision History
-----------------------------------------------------------
Date      Reason
2020/03/27  Preliminary release
2020/03/27  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Patient.h"
#include "Ticket.h"
#include "utils.h"
#include <cstring>
using namespace std;
namespace sdds {
	Patient::Patient(int ticketNo, bool flag) {
		m_ticket = new Ticket(ticketNo);
		m_flag = flag;
		m_name = nullptr;
		m_ohipNo = 0;
	};
	Patient::~Patient() {
		delete[] m_name;
		m_name = nullptr;
		delete m_ticket;
		m_ticket = nullptr;
	};
	bool Patient::fileIO() const {
		return m_flag;
	}
	void Patient::fileIO(bool flag) {
		m_flag = flag;
	}
	bool Patient::operator==(const char& ch) const {
		return (type() == ch);
	};
	bool Patient::operator==(const Patient& patient2)const {
		return (type() == patient2.type());

	};
	void Patient::setArrivalTime() {
		m_ticket->resetTime();
	}
	Patient::operator Time() const {
		return Time(*m_ticket);
	}
	int Patient::number() const {
		return m_ticket->number();
	}
	void Patient::resetTime() {
		m_ticket->resetTime();
	}

	std::ostream& Patient::csvWrite(std::ostream& ostr) const {
		ostr << type() << ',' << m_name << ',' << m_ohipNo << ',';
		return m_ticket->csvWrite(ostr);
	}

	std::istream& Patient::csvRead(std::istream& istr){
		delete[] m_name;
		m_name = getcstr(nullptr, istr, ',');
		istr >> m_ohipNo;
		istr.ignore(1000, ',');
		return m_ticket->csvRead(istr);
	}

	std::ostream& Patient::write(std::ostream& ostr) const {
		m_ticket->write(ostr);
		ostr << endl;
		int i = -1;
		int len = strlen(m_name);
		while (++i < 25 && i < len) {
			ostr << m_name[i];
		}
		return ostr << ", OHIP: " << m_ohipNo;
	}

	std::istream& Patient::read(std::istream& istr)
	{
		delete[] m_name;
		m_name = getcstr("Name: ", istr, '\n');
		m_ohipNo = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ");
		return istr;
	}
	
}