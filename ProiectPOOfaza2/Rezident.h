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
    
    #pragma region Constructori

	Rezident() {
		this->facultate = "";
	}

    Rezident(string facultate):Asistent(), Medic() {
		this->facultate = facultate;
	}

    Rezident(string facultate, int* note, int nrNote):Medic(), Asistent() {
		this->facultate = facultate;
		if (note != nullptr) {
			for (int i = 0; i < nrNote; i++) {
				this->note.push_back(note[i]);
			}
		}
	}

	Rezident(const char* nume, const string prenume, const float salariu, const int varsta,string facultate, int* note, int nrNote) :Angajat(nume, prenume, salariu,varsta), Medic(), Asistent() {
		this->facultate = facultate;
		if (note != nullptr) {
			for (int i = 0; i < nrNote; i++) {
				this->note.push_back(note[i]);
			}
		}
	}

    #pragma endregion

    #pragma region ConstructorCopiere
    Rezident(const Rezident& r) :Angajat(r) {
        this->facultate = r.facultate;
        this->note.clear();
        for (const int& i : r.note) {
            this->note.push_back(i);
        }
    }
#pragma endregion

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

    #pragma region MetodeAccesor

    void setFacultate(string facultate) {
        this->facultate = facultate;
    }

    string getFacultate() {
        return this->facultate;
    }

    void setNote(int *note, int nrNote) {
        if (note != nullptr&&nrNote!=0) {
            this->note.clear();
            for (int i = 0; i < nrNote; i++) {
                this->note.push_back(note[i]);
            }
        }
    }

    vector<int> getNote() {
        return this->note;
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
    #pragma endregion

    #pragma region MetodaRaport
    void creareRaport(ofstream& out) {
        out << "\n---------------------------------------------------------\n";
        out << "\n\n\nDate referitoare la stagiarul cu id-ul: " << this->id;
        if (this->prenume != "" && this->nume != nullptr) {
            out << endl << "Numele stagiarului: " << this->getNume() << endl;
            out << "Prenumele stagiarului: " << this->getPrenume()<< endl;
            if (this->vechimeCentru == 0) {
                out << "Stagiarul abia s-a transferat in cadrul acestui centru medical";
            }
            else {
                out << "Stagiarul are o experienta de " << this->getVechime() << "luni in cadrul acestui centru medical." << endl;
            }
            out << "Stagiarul are un salariu in valoare de " << this->getSalariu() << " RON" << endl;
            out << "Varsta stagiarului este de : " << this->getVarsta() << " ani" << endl;
            out << "Specializarea aferenta stagiarului este: "<<this->getSpecializare()<<endl;
            if (this->getMedicAsociat() != nullptr&&this->getNrMedici()!=0) {
                out << "Stagiarul are urmatorii medici asociati: \n";
                for (int i = 0; i < this->getNrMedici(); i++) {
                    out << this->getMedicAsociat()[i];
                }
            }
        }
        else {
            out << "\nNu avem date referitoare la acest Angajat\n";
        }
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

    #pragma region OperatorulEgal
    Rezident& operator =(const Rezident& r) {
        if (this != &r) {
            Medic::operator=(r);
            Asistent::operator =(r);
            this->facultate = r.facultate;
            this->note.clear();
            for (const int& i : r.note) {
                this->note.push_back(i);
            }
        }
        return *this;
    }

#pragma endregion

    #pragma region OperatorScriere
    friend ostream& operator <<(ostream& out, const Rezident& m) {
        out << "\n\n\nDate referitoare la stagiarul cu id-ul: " << m.id << endl;
        if (m.prenume != "" && m.nume != nullptr) {
            out << endl << "Numele stagiarului: " << m.nume << endl;
            out << "Prenumele stagiarului: " << m.prenume << endl;
            if (m.vechimeCentru == 0) {
                out << "Stagiarul abia s-a transferat in cadrul acestui centru medical" << endl;
            }
            else {
                out << "Stagiarul are o experienta de " << m.vechimeCentru << "luni in cadrul acestui centru medical." << endl;
            }
            out << "Stagiarul are un salariu in valoare de " << m.salariu << " RON" << endl;
            out << "Varsta stagiarului este de : " << m.varsta << " ani" << endl;
            out << "Specializarea pe care studentul face stagiul este: " << m.getSpecializare() << endl;
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
#pragma endregion

    #pragma region OperatorCitire
    
    friend istream &operator >>(istream& in, Rezident &m) {
        cout << "\nIntroduceti prenumele stagiarului:\n";
        string prenume;
        in >> prenume;

        if (verifSiruriCaractere(prenume.c_str())) {
            m.prenume = prenume;
        }
        else {
            m.prenume = "";
        }
        if (m.nume != nullptr)
        {
            delete[] m.nume;
        }
        cout << "Intorduceti numele stagiarului:\n";
        char nume[30];
        in >> nume;
        if (verifSiruriCaractere(nume)) {
            m.nume = new char[strlen(nume) + 1];
            strcpy(m.nume, nume);
        }
        else {
            m.nume = nullptr;
        }
        int vechime;
        cout << "Introduceti vechimea stagiarului in cadrul acestui centru medical:\n";
        in >> vechime;
        if (vechime > 0) {
            m.vechimeCentru = vechime;
        }

        int varsta;
        cout << "Introduceti varsta stagiarului:\n";
        in >> varsta;
        if (varsta > 0) {
            m.varsta = varsta;
        }
        else {
            m.varsta = 0;
        }

        cout << "Introduceti numarul consultatiilor sustinute de acest rezident pe parcursul acestui an:\n";
        int istoricNrConsultatiiLunare[12];
        if (m.vechimeCentru >= 12) {
            for (int i = 0; i < 12; i++) {
                cout << "Numarul de consultatii din luna " << m.luni[i] << " este: ";
                in >> istoricNrConsultatiiLunare[i];
            }

        }
        else {
            for (int i = 0; i < m.vechimeCentru; i++) {
                cout << "Numarul de consultatii din luna " << m.luni[i] << " este: ";
                in >> istoricNrConsultatiiLunare[i];
            }

        }

        if (m.vechimeCentru >= 0) {
            int* aux = new int[12];
            aux = verifIstoric<int>(istoricNrConsultatiiLunare, m.vechimeCentru, 0);
            for (int i = 0; i < 12; i++) {
                m.istoricNrConsultatiiLunare[i] = aux[i];
            }
            delete[]aux;
        }


        cout << "Introduceti veniturile aferente lunilor acestui an ale angajatului:\n";
        float istoricVenituriLunare[12];
        if (m.vechimeCentru >= 12) {
            for (int i = 0; i < 12; i++) {
                cout << "Venitul din luna " << m.luni[i] << " este: ";
                in >> istoricVenituriLunare[i];
            }

        }
        else {
            for (int i = 0; i < m.vechimeCentru; i++) {
                cout << "Venitul din luna " << m.luni[i] << " este: ";
                in >> istoricVenituriLunare[i];
            }

        }

        if (m.vechimeCentru > 0) {
            float* aux2 = new float[12];
            aux2 = verifIstoric<float>(istoricVenituriLunare, m.vechimeCentru, Rezident::MINIM_SALARIU);
            for (int i = 0; i < 12; i++) {
                m.istoricVenituriLunare[i] = aux2[i];
            }
            delete[] aux2;
        }

        float salariu;
        cout << "Introduceti salariul curent: \n";
        in >> salariu;

        if (salariu > Rezident::MINIM_SALARIU) {
            m.salariu = salariu;
        }
        else {
            m.salariu = Rezident::MINIM_SALARIU;
        }

        int istoricOreLucrate[12];
        cout << "Introduceti orele lucrate in lunile anului acesta de catre stagiar: \n";
        if (m.vechimeCentru > 12) {
            for (int i = 0; i < 12; i++) {
                cout << "Ore lucrate in luna " << m.luni[i] << " este: ";
                in >> istoricOreLucrate[i];
            }
        }
        else {
            for (int i = 0; i < m.vechimeCentru; i++) {
                cout << "Ore lucrate in luna " << m.luni[i] << " este: ";
                in >> istoricOreLucrate[i];
            }
        }

        if (m.vechimeCentru > 0) {

            int* aux3 = new int[12];
            aux3 = verifIstoric<int>(istoricOreLucrate, m.vechimeCentru, 6);
            for (int i = 0; i < 12; i++) {
                m.istoricOreLucrate[i] = aux3[i];
            }
            delete[]aux3;
        }
        char specializare[70];
        cout << "Introduceti specializarea stagiarului:\n";
        in.get();
        in.getline(specializare, 70);

        cout << "Introduceti facultatea de provenienta a stagiarului: \n";
        char faculta[70];
        in.get();
        in.getline(faculta, 70);
        m.setFacultate(faculta);

        int nrNote;
        cout << "Introduceti numarul de note:\n";
        in >> nrNote;
        int* note = new int[nrNote];
        cout << "Introduceti notele: \n";
        for (int i = 0; i < nrNote; i++) {
            cout << "Nota cu indicele " << i+1<<" este: ";
            in >> note[i];
        }

        if (note != nullptr && nrNote != 0) {
            m.setNote(note, nrNote);
        }
        return in;
    }
    
#pragma endregion

    #pragma region Destructor
    ~Rezident() {

    }
#pragma endregion

};
