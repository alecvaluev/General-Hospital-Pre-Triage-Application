/*
Final Project Milestone 2
Module: IOAble
Filename: IOAble.cpp
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
#include <iostream>
#include "IOAble.h"

namespace sdds {
	std::ostream& operator<<(std::ostream& ostr, const IOAble& obj) {
		obj.write(ostr);
		return ostr;
	};
	std::istream& operator>>(std::istream& istr, IOAble& obj) {
		obj.read(istr);
		return istr;
	};
	IOAble::~IOAble() {};
}
