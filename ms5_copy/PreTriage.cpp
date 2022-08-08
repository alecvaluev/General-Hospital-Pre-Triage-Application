/*
Final Project Milestone 5
Module: PreTriage
Filename: PreTriage.cpp
Version 1.0
Author	Aleksandr Valuev
Revision History
-----------------------------------------------------------
Date      Reason
2020/03/22  Preliminary
release
2020/03/22  Debugged DMA
+-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Patient.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "PreTriage.h"
#include "utils.h"
using namespace std;
namespace sdds {
    PreTriage::PreTriage(const char* dataFilename) : m_averCovidWait(15), m_averTriageWait(5), m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
        m_dataFilename = new char[strlen(dataFilename) + 1];
        strcpy(m_dataFilename, dataFilename);
        load();
    };

    PreTriage::~PreTriage() {
        ofstream fout(m_dataFilename);

        if (fout.is_open()) {
            cout << "Saving Average Wait Times," << endl;
            cout << "   COVID Test: " << m_averCovidWait << endl;
            cout << "   Triage: " << m_averTriageWait << endl;
            fout << m_averCovidWait << "," << m_averTriageWait << endl;
            cout << "Saving m_lineup..." << endl;

            for (int i = 0; i < m_lineupSize; i++) {
                m_lineup[i]->csvWrite(fout);
                fout << endl;
                cout << (i + 1) << "- ";
                m_lineup[i]->csvWrite(cout) << endl;
            }

            for (int i = 0; i < maxNoOfPatients; i++) {
                delete m_lineup[i];
            }
            delete[] m_dataFilename;
            cout << "done!" << endl;
            fout.close();
        }
    };
    const Time PreTriage::getWaitTime(const Patient& p)const {
        int count = 0;
        for (int i = 0; i < m_lineupSize; i++) {
            if (p == *m_lineup[i])count++;
        }
        return Time(p) * (unsigned int)count;
    };
    void PreTriage::setAverageWaitTime(const Patient& p) {
        Time CP;
        CP.setToNow();
        if (p == 'C') {
            m_averCovidWait = ((int)(CP - Time(p)) + ((int)m_averCovidWait * (p.number() - 1))) / p.number();
        }
        else {
            m_averTriageWait = ((int)(CP - Time(p)) + ((int)m_averTriageWait * (p.number() - 1))) / p.number();
        }
    };

    void PreTriage::removePatientFromLineup(int index) {
        removeDynamicElement(m_lineup, index, m_lineupSize);
    };
    int PreTriage::indexOfFirstInLine(char type) const {
        int index = -1;
        for (int i = 0; i < m_lineupSize; i++) {
            if (*(m_lineup[i]) == type) {
                index = i;
                break;
            }
        }
        return index;
    };
    void PreTriage::load() {
        Patient* p = nullptr;
        char type;
        ifstream fin(m_dataFilename);

        cout << "Loading data...\n";
        if (fin.is_open()) {
            fin >> m_averCovidWait;
            fin.ignore(1000, ',');
            fin >> m_averTriageWait;
            fin.ignore(1000, '\n');

            while (m_lineupSize < maxNoOfPatients) {
                type = '\0';
                fin.get(type);
                fin.ignore();

                if (type == 'C') {
                    p = new CovidPatient();
                }
                else if (type == 'T') {
                    p = new TriagePatient();
                }
                else {
                    break;
                }

                if (p) {
                    p->fileIO(true);
                    p->csvRead(fin);
                    p->fileIO(false);
                    m_lineup[m_lineupSize] = p;

                    m_lineupSize++;
                }
            }
            fin.close();
        }
        if (m_lineupSize >= maxNoOfPatients) cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
        if (m_lineupSize == 0) cout << "No data or bad data file!" << endl << endl;
        else cout << m_lineupSize << " Records imported..." << endl << endl;
    }; 
    void PreTriage::reg() {
        if (m_lineupSize == maxNoOfPatients) cout << "Line up full!" << endl;
        else {
            int selection;
            m_pMenu >> selection;
            switch (selection) {
            case 1: m_lineup[m_lineupSize] = new CovidPatient();
                break;
            case 2: m_lineup[m_lineupSize] = new TriagePatient();
                break;
            case 0:
                break;
            }
            m_lineup[m_lineupSize]->setArrivalTime();
            cout << "Please enter patient information: \n";
            cin >> *(m_lineup[m_lineupSize]);
            cout << endl;
            cout << "******************************************" << endl;
            cout << *m_lineup[m_lineupSize];
            cout << "Estimated Wait Time: " << getWaitTime(*(m_lineup[m_lineupSize])) << endl;
            cout << "******************************************" << endl << endl;

            m_lineupSize++;
        }
    };
    void PreTriage::admit() {
        int selection;
        char type = '\0';
        m_pMenu >> selection;
        switch (selection) {
        case 1: type = 'C';
            break;
        case 2: type = 'T';
            break;
        case 0:
            break;
        }
        int indexOfPatient = -1;
        if (type) indexOfPatient = indexOfFirstInLine(type);
        if (indexOfPatient > -1) {
            cout << "\n******************************************" << endl;
            m_lineup[indexOfPatient]->fileIO(false);
            cout << "Calling for " << *m_lineup[indexOfPatient];
            cout << "******************************************" << endl << endl;
            setAverageWaitTime(*m_lineup[indexOfPatient]);
            removePatientFromLineup(indexOfPatient);
        }
    };
    void PreTriage::run(void) {
        int selection;
        do {
            m_appMenu >> selection;
            switch (selection) {
            case 1: reg();
                break;
            case 2: admit();
                break;
            case 0:
                break;
            }
        } while (selection != 0);
    };
}