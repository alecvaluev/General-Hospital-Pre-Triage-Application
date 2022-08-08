/* 
Final Project Milestone 2
Module: IOAble
Filename: IOAble.h
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
#ifndef SDDS_IOABLE_H__
#define SDDS_IOABLE_H__
#include <iostream>
namespace sdds {
	class IOAble {
	public: 
		virtual std::ostream& csvWrite(std::ostream&)const = 0;
		virtual std::istream& csvRead(std::istream&) = 0;
		virtual std::ostream& write(std::ostream&)const = 0;
		virtual std::istream& read(std::istream&) = 0;
		virtual ~IOAble(); //pure virtual or just virtual???
	};
	std::ostream& operator<<(std::ostream&, const IOAble& obj);
	std::istream& operator>>(std::istream&, IOAble& obj);
}
#endif 