#pragma once

#include <iostream>
using namespace std;
#include <string.h>
#include <fstream>
#include <string>
#include "Functii.h"
#include "Medic.h"
#include "Data.h"
#include "Consultatie.h"
#include "Pacient.h"
#include "Persoana.h"
#include <ctime>
#include <set>

class PacientExtins : public Pacient {

	bool areAlergii = false;
	string* alergii = nullptr;
	int nrAlergii = 0;
	set <string> boli;

public:

	#pragma region Constructori
	PacientExtins() :Pacient() {
		this->areAlergii = false;
		this->alergii = nullptr;
		this->nrAlergii = 0;
	}

	PacientExtins(const char* prenume, const string nume, const char* phoneNumber, const int varsta, const char adresa[], const bool eAsigurat, const bool areAlergii,const int nrAlergii, const string*alergii, int nrBoli, string* boli)
		:Pacient(prenume, nume, phoneNumber, varsta, adresa, eAsigurat) {
		this->areAlergii = areAlergii;
		this->nrAlergii = nrAlergii;
		if (this->nrAlergii != 0 && alergii != nullptr) {
			this->alergii = new string[this->nrAlergii];
			for (int i = 0; i < this->nrAlergii; i++) {
				this->alergii[i] = alergii[i];
			}
		}
		if (boli != nullptr) {
			for (int i = 0; i < nrBoli; i++) {
				this->boli.insert(boli[i]);
			}
		}
	}

	PacientExtins(const char* prenume, const string nume, const char* phoneNumber, const int varsta, const char adresa[], const bool eAsigurat, const bool areAlergii, set<string> boli)
		:Pacient(prenume, nume, phoneNumber, varsta, adresa, eAsigurat) {
		this->areAlergii = areAlergii;
		for (auto& str : boli) {
			this->boli.insert(str);
		}
	}

	PacientExtins(const Pacient p, const bool areAlergii, const string* alergii, const int nrAlergii, set<string> boli) :Pacient(p) {
		this->areAlergii = areAlergii;
		if (this->areAlergii) {
			if (nrAlergii > 0) {
				this->nrAlergii = nrAlergii;
				this->alergii = new string[this->nrAlergii];
				for (int i = 0; i < this->nrAlergii; i++) {
					this->alergii[i] = alergii[i];
				}
				for (auto& str : boli) {
					this->boli.insert(str);
				}
			}
		}
	}
#pragma endregion 

	#pragma region ConstructorCopiere
	PacientExtins(const PacientExtins& p) :Pacient(p) {
		this->areAlergii = p.areAlergii;
		if (this->alergii != nullptr) {
			delete[] this->alergii;
		}
		if (p.nrAlergii != 0 && p.alergii != nullptr && p.areAlergii) {
			this->alergii = new string[p.nrAlergii];
			for (int i = 0; i < p.nrAlergii; i++) {
				this->alergii[i] = p.alergii[i];
			}
		}
		for (auto& str : p.boli) {
			this->boli.insert(str);
		}
	}
#pragma endregion

	#pragma region MetodaMoare
	void Persoana::Moare() {
		this->setPrenume("Pacient");
		this->setNume("Decedat");
		time_t theTime = time(NULL);
		struct tm* aTime = localtime(&theTime);

		int ziuaCurenta = aTime->tm_mday;
		int lunaCurenta = aTime->tm_mon + 1;
		int anulCurent = aTime->tm_year + 1900;
		cout << "Pacientul a decedat la data de " << ziuaCurenta << "/" << lunaCurenta << "/" << anulCurent << endl;
	}
#pragma endregion

#pragma region SchimbaIdentitatea
	void Persoana::SchimbaIdentitatea() {
		cout << "Introduceti noul nume al pacientului:\n";
		string nume, prenume;
		cin >> nume;
		cout << "Introduceti noul prenume al pacientului:\n";
		cin >> prenume;
		this->setNume(nume);
		this->setPrenume(prenume.c_str());
		cout << "Introduceti noua varsta a pacientului:\n";
		int varsta;
		cin >> varsta;
		this->setVarsta(varsta);
		cout << "\nSchimbarea de identitate a avut loc cu succes\n";
	}
#pragma region


	#pragma region MetodeAccesore
	void changeEAlergic(const bool eAlergic) {
		if (!eAlergic) {
			this->areAlergii = false;
			this->alergii = nullptr;
			this->nrAlergii = 0;
		}
		else {
			this->areAlergii = eAlergic;
		}
	}

	void setEAlergic(const bool eAlergic, const string* alergii, const int nrAlergii) {
		if (!eAlergic) {
			this->areAlergii = eAlergic;
			this->alergii = nullptr;
			this->nrAlergii = 0;
		}
		else {
			this->areAlergii = eAlergic;
			if (this->nrAlergii > 0) {
				this->nrAlergii = nrAlergii;
				if (this->alergii != nullptr) {
					delete[] this->alergii;
				}
				this->alergii = new string[this->nrAlergii];
				for (int i = 0; i < this->nrAlergii; i++) {
					this->alergii[i] = alergii[i];
				}
			}
		}
	}

	void addBoli(string boala) {
		this->boli.insert(boala);
	}

	void setBoala(set<string> boala) {
		set<string>::iterator itr;
		for (itr = boala.begin();
			itr != boala.end(); itr++)
		{
			this->boli.insert(*itr);
		}
	}

	set<string> getBoala() {
		return this->boli;
	}

	void setNrAlergii(int nrAlergii) {
		if (nrAlergii > 0) {
			this->nrAlergii = nrAlergii;
		}
	}

#pragma endregion

	#pragma region OperatorEgal
	PacientExtins& operator=(const PacientExtins& p)
	{
		if (this != &p) {

			Pacient::operator=(p);
			this->areAlergii = p.areAlergii;
			if (this->areAlergii) {
				this->nrAlergii = p.nrAlergii;
				for (int i = 0; i < this->nrAlergii; i++) {
					this->alergii[i] = p.alergii[i];
				}
			}
			for (auto& str : p.boli) {
				this->boli.insert(str);
			}
		}
		return *this;
	}
#pragma endregion

	#pragma region OperatorAfisare
	friend ostream& operator<<(ostream& out, const PacientExtins& p)
	{
		out << (Pacient)p;
		out << "Pacientul ";
		(p.areAlergii) ? cout << "are alergii.\n" : cout << "nu are alergii.\n";
		if (p.areAlergii) {
			cout << "Pacientul are " << p.nrAlergii << " alergii, respectiv:\n";
			for (int i = 0; i < p.nrAlergii; i++) {
				cout << p.alergii[i] << endl;
			}
		}
		if (!p.boli.empty()) {
			out << "Bolile pacientului au fost urmatoarele: \n";
			for (auto& str : p.boli) {
				out << str << endl;
			}
		}
		return out;
	
	}
#pragma endregion

	#pragma region OperatorCitire
	friend istream& operator>>(istream& in, PacientExtins& p) {
        
        cout << "\nIntroduceri numele pacientului:\n";
        string nume;
        in >> nume;
        p.setNume(nume);
        char prenume[30];
        cout << "Introduceti prenumele pacientului:\n";
        in >> prenume;
        p.setPrenume(prenume);

        char* number;
        number = new char[11];
        cout << "Introduceti numarul de telefon al pacientului (10 cifre):\n";
        in >> number;
        p.setPhoneNumber(number);
		delete[] number;

        int varsta;
        cout << "Introduceti varsta pacientului:\n";
        in >> varsta;
        p.setVarsta(varsta);
        getchar();
        cout << "Introduceti adresa pacientului:\n";
        char adresa[60];
        cin.getline(adresa, strlen(adresa));
		p.setAdresa(adresa);

        cout << "Este pacientul asigurat?(0-false / 1-true)";
        int ok;
        in >> ok;
        if (ok == 1) {
			p.setEsteAsigurat(true);
        }
        if (ok == 0) {
			p.setEsteAsigurat(false);
        }
        int nrConsultatii;
        cout << "Introduceti numarul de consulatii:";
        in >> nrConsultatii;

	    p.setNrConsultatii(nrConsultatii);
            
        Consultatie* cons;
            cout << "Introduceti datele fiecarei consultatii in parte:\n";
            cons = new Consultatie[nrConsultatii];
            for (int i = 0; i < p.getNrConsultatii(); i++) {
                Consultatie c;
                Data d;
                bool ok = false;
                while (ok == false) {
                    cout << "Introduceti ziua in care va avea loc consultatia " << i + 1 << " :";
                    int zi;
                    in >> zi;
                    cout << "Introduceti luna in care va avea loc consultatia " << i + 1 << " :";
                    int luna;
                    in >> luna;
                    cout << "Introduceti anul in care va avea loc consultatia " << i + 1 << " :";
                    int an;
                    in >> an;
                    if (d.setData(zi, luna, an) && c.setDataConsultatie(d)) {
                        ok = true;
                    }
                    else {
                        cout << "Nu ai introdus o data valida";
                    }
                }
                cout << "Introduceti ora la care va avea loc consultatia " << i + 1 << " :";
                int ora;
                in >> ora;
                c.setOra(ora);
                cons[i] = c;
            }
		p.setViitoareConsultatii(nrConsultatii, cons);
        int nrPlati;
        float* istoricPlati;
        cout << "Introduceti numarul de plati efectuate de catre pacient in cadrul centrului medical:";
        in >> nrPlati;
		p.setNrPlati(nrPlati);
        if (nrPlati > 0) {
            cout << "Intoruceti platile aferente fiecarui an: \n";
            istoricPlati = new float[nrPlati];
            for (int i = 0; i < nrPlati; i++) {
                cout << "Plata cu numarul " << i + 1 << " este in valoare de: ";
                in >> istoricPlati[i];
            }
			p.setIstoricPlati(istoricPlati);
			delete[] istoricPlati;
        }
		cout << "Pacientul are alergii(1 - da/ 0 - nu)\n";
		int da;
		cin >> da;
		if (da==1) {
			cout << "Introduceti numarul de alergi pe care le are pacientul: \n";
			int nr;
			cin >> nr;
			if (nr > 0) {
				p.nrAlergii = nr;
				string* alergie = new string[p.nrAlergii];
				for (int i = 0; i < nr; i++) {
					cout << "Introduceti alergia cu numarul " << i + 1 << endl;
					cin >> alergie[i];
				}
				p.setEAlergic(true, alergie, nr);
				delete[] alergie;
			}
		}
		cout << "Introduceti numarul de boli ale pacientului:\n";
		int nr;
		cin >> nr;
		string boala;
		for (int i = 0; i < nr; i++) {
			cout << "Boala " << i << endl;
			in >> boala;
			p.addBoli(boala);
		}
		delete[] cons;
		return in;
	}
#pragma endregion

	#pragma region Citire_Fisier
    friend ifstream& operator >>(ifstream& in, PacientExtins& p) {
        if (p.getPrenume() != nullptr) {
			p.setPrenume(nullptr);
        }
        if (p.getIstoricPlati() != nullptr) {
            p.setIstoricPlati(nullptr);
        }
        if (p.getPhoneNumber() != nullptr) {
			p.setPhoneNumber(nullptr);
        }
        if (p.getViitoareConsultatie() != nullptr) {
            p.setViitoareConsultatii(0, nullptr);
        }
        string nume;
        in >> nume;
		p.setNume(nume);
        char prenume[30];
        in >> prenume;
		p.setPrenume(prenume);
        char* number;
        number = new char[11];
        in >> number;

		p.setPhoneNumber(number);

        int varsta;
        in >> varsta;
		p.setVarsta(varsta);

        int ok;
        in >> ok;
		p.setEsteAsigurat(ok);
        int nrConsultatii;
        in >> nrConsultatii;
		p.setNrConsultatii(nrConsultatii);
        Consultatie *viitoareConsultatii = new Consultatie[p.getNrConsultatii()];
		if (p.getNrConsultatii() != 0) {
			for (int i = 0; i < nrConsultatii; i++) {
				int zi;
				int luna;
				int an;
				int ora;
				in >> zi;
				in >> luna;
				in >> an;
				in >> ora;
				Data d(zi, luna, an);
				viitoareConsultatii[i].setDataConsultatie(d);
				viitoareConsultatii[i].setOra(ora);
			}
			p.setViitoareConsultatii(p.getNrConsultatii(), viitoareConsultatii);
		}

        int nrPlati;
        float* istoricPlati;
        in >> nrPlati;
		p.setNrPlati(nrPlati);
		if (p.getNrPlati() != 0) {
			istoricPlati = new float[p.getNrPlati()];
			for (int i = 0; i < p.getNrPlati(); i++) {
				in >> istoricPlati[i];
			}
		}

		int nr;
		in >> nr;

		p.setNrAlergii(nr);
		string* alergie = new string[p.nrAlergii];
		for (int i = 0; i < nr; i++) {
			in >> alergie[i];
		}
		p.setEAlergic(true, alergie, nr);
		int nr2;
		in >> nr2;
		string boala;
		p.boli.clear();
		for (int i = 0; i < nr2; i++) {
			in >> boala;
			p.addBoli(boala);
		}

        return in;
    }
#pragma endregion

	#pragma region Scriere_in_fisier
    friend ofstream& operator <<(ofstream& out, const PacientExtins& p) {
        if (p.getPrenume() != nullptr && p.getNume() != "") {
            out << p.getNume() << endl;
            out << p.getPrenume() << endl;
            if (p.getPhoneNumber() != nullptr) {
                out << p.getPhoneNumber() << endl;
            }
            out << p.getVarsta() << endl;

            out << p.getEsteAsigurat() << endl;
            out << p.getNrConsultatii() << endl;
            if (p.getNrConsultatii() != 0) {
                for (int i = 0; i < p.getNrConsultatii(); i++) {
                    out << p.getViitoareConsultatie()[i].getZi() << " ";
                    out << p.getViitoareConsultatie()[i].getLuna() << " ";
                    out << p.getViitoareConsultatie()[i].getAn() << " ";
                    out << p.getViitoareConsultatie()[i].getOra() << endl;
                }
            }

            if (!(p.getNrPlati() == 0 || p.getIstoricPlati() == nullptr)) {
				out << p.getNrPlati()<<endl;
                for (int i = 0; i < p.getNrPlati(); i++) {
                    out << p.getIstoricPlati()[i] << endl;
                }
            }

			out << p.nrAlergii << endl;
			if (p.alergii != nullptr) {
				for (int i = 0; i < p.nrAlergii; i++) {
					out << p.alergii[i] << " ";
				}
			}

			int k = 0;
			for (auto& str : p.boli) {
				k++;
			}
			out << k << endl;
			for (auto& str : p.boli) {
				out << str;
			}
			out << endl;
        }
        return out;
    }
#pragma endregion


	~PacientExtins(){
		delete[] this->alergii;
	}
};