#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <ctime>
#include "Angajat.h"
#include "Medic.h"
#include "Asistent.h"
#include "Consultatie.h"
#include "Pacient.h"
#include "Colectie.h"
#include "FileManager.h"
#include "Menu.h"
#include "Colectie.h"
#include "Persoana.h"
using namespace std;

class Rezident: public Medic, public Asistent {
	string facultate="";
	vector<int> note;
public:
	Rezident() {
		this->facultate = "";
	}

    Rezident(string facultate) {
		this->facultate = facultate;
	}

    Rezident(string facultate, int* note, int nrNote) {
		this->facultate = facultate;
		if (note != nullptr) {
			for (int i = 0; i < nrNote; i++) {
				this->note.push_back(note[i]);
			}
		}
	}

    friend ostream& operator <<(ostream&	 out, const Rezident& m) {
        out << "\n\n\nDate referitoare la stagiarul cu id-ul: " << m.id << endl;
        if (m.prenume != "" && m.nume != nullptr) {
                out << endl << "Numele stagiarului: " << m.nume << endl;
                out << "Prenumele stagiarului: " << m.prenume << endl;
                if (m.vechimeCentru == 0) {
                    out << "Stagiarul abia s-a transferat in cadrul acestui centru medical"<<endl;
                }
                else {
                    out << "Stagiarul are o experienta de " << m.vechimeCentru << "luni in cadrul acestui centru medical." << endl;
                }
                out << "Stagiarul are un salariu in valoare de " << m.salariu << " RON" << endl;
                out << "Varsta stagiarului este de : " << m.varsta << " ani" << endl;
                out << "Specializarea pe care studentul face stagiul este: " << m.getSpecializare() <<endl;
                out << "Facultatea la care studiaza studentul este: " << m.facultate << endl;
                out << "Notele studentului sunt: \n";
                for (const int& i : m.note) {
                    out << i << "  ";
                }
        }
        else {
            out << "\nNu avem date referitoare la acest stagiar\n";
        }
        return out;
                
    }

#pragma region MetodaMoare
	void Persoana::Moare() {
		this->setPrenume("Rezident");
		this->setNume("Decedat");
		time_t theTime = time(NULL);
		struct tm* aTime = localtime(&theTime);
		int ziuaCurenta = aTime->tm_mday;
		int lunaCurenta = aTime->tm_mon + 1;
		int anulCurent = aTime->tm_year + 1900;
		cout << "Rezidentul a decedat la data de " << ziuaCurenta << "/" << lunaCurenta << "/" << anulCurent << endl;
	}
#pragma endregion

#pragma region SchimbaIdentitatea
	void Persoana::SchimbaIdentitatea() {
		cout << "Introduceti noul nume al rezidentului:\n";
		string nume, prenume;
		cin >> nume;
		cout << "Introduceti noul prenume al rezidentului:\n";
		cin >> prenume;
		this->setNume(nume.c_str());
		this->setPrenume(prenume);
		cout << "Introduceti noua varsta a rezidentului:\n";
		int varsta;
		cin >> varsta;
		this->setVarsta(varsta);
		cout << "\nSchimbarea de identitate a avut loc cu succes\n";
	}
#pragma region


#pragma region MetodaRaport
    void creareRaport(ofstream& out) {
        Angajat::creareRaport(out);
    }
#pragma endregion

#pragma region WriteBinary
    void writeBinary(fstream& f) {
        Angajat::writeBinary(f);
    }
#pragma endregion

#pragma region CitireCSV

    virtual void citireCSV(ifstream& f, char delim[]) {
		Angajat::citireCSV(f, delim);
    }

#pragma endregion


};
