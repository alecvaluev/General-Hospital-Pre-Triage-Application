/*
Final Project Milestone 3
Module: Patient
Filename: Patient.h
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
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include "IOAble.h"
#include "Ticket.h"
namespace sdds {
	class Patient: public IOAble {
		char* m_name;
		int m_ohipNo;
		Ticket* m_ticket;
		bool m_flag;
	public:
		Patient(int = 0, bool = false);
		~Patient();
		Patient (const Patient&) = delete;
		Patient& operator=(Patient&) = delete;
		virtual char type() const = 0;
		bool fileIO() const;
		void fileIO(bool);
		bool operator==(const char&) const;
		bool operator==(const Patient&)const;
		void setArrivalTime();
		operator Time()const;
		int number() const;
		void resetTime();
		std::ostream& csvWrite(std::ostream&)const;
		std::istream& csvRead(std::istream&);
		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
	};
}
#endif
