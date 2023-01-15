#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>
#include <vector>
#include "Functii.h"
#include "Pacient.h"
#include "Data.h"

using namespace std;

template<class TIP>
class Colectie {

	TIP* listaObiecte = nullptr;
	int nrObiecte = 0;

public:

	Colectie() {}

	Colectie(int nrObiecte, TIP* listaObiecte) {
		if (nrObiecte > 0 && listaObiecte != nullptr) {
			this->nrObiecte = nrObiecte;
			this->listaObiecte = new TIP[this->nrObiecte];
			for (int i = 0; i < this->nrObiecte; i++) {
				this->listaObiecte[i] = listaObiecte[i];
			}
		}
	}

	Colectie(const Colectie& c) {
		if (c.nrObiecte > 0 && c.listaObiecte != NULL) {
			this->nrObiecte = c.nrObiecte;
			this->listaObiecte = new TIP[this->nrObiecte];
			for (int i = 0; i < this->nrObiecte; i++) {
				this->listaObiecte[i] = c.listaObiecte[i];
			}
		}
	}

#pragma region MetodeAccesore
	TIP operator[](int i) {
		return this->listaObiecte[i];
	}

	void setColectie(int nrObiecte, TIP* listaObiecte) {
		if (nrObiecte > 0 && listaObiecte != nullptr) {
			this->nrObiecte = nrObiecte;
			if (this->listaObiecte != nullptr) {
				delete[] this->listaObiecte;
			}
			this->listaObiecte = new TIP[this->nrObiecte];
			for (int i = 0; i < this->nrObiecte; i++) {
				this->listaObiecte[i] = listaObiecte[i];
			}
		}
	}

	int getNrObiecte() {
		return this->nrObiecte;
	}

	TIP* getColectie() {
		return this->listaObiecte;
	}

#pragma endregion

	Colectie& operator =(const Colectie& c) {
		if (this != &c) {
			if (c.nrObiecte > 0 && c.listaObiecte != NULL) {
				if (this->listaObiecte != nullptr) {
					delete[] this->listaObiecte;
				}
				this->nrObiecte = c.nrObiecte;
				this->listaObiecte = new TIP[this->nrObiecte];
				for (int i = 0; i < this->nrObiecte; i++) {
					this->listaObiecte[i] = c.listaObiecte[i];
				}
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Colectie& c) {
		out << "\nNr obiecte: " << c.nrObiecte << endl;
		for (int i = 0; i < c.nrObiecte; i++) {
			out << c.listaObiecte[i];
		}
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Colectie& c) {
		for (int i = 0; i < c.nrObiecte; i++) {
			out << c.listaObiecte[i];
		}
		return out;
	}

	~Colectie() {
		delete[] this->listaObiecte;
	}

};