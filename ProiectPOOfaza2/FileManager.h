#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <string.h>
#include <fstream>
#include <vector>
#include "Functii.h"
#include "Medic.h"
#include "Consultatie.h"
#include "Angajat.h"
#include "Asistent.h"
#include "Medic.h"
#include "Pacient.h"
#include "Colectie.h";

class FileManager {

	string numeColectie="";

	ofstream fileOutTxt;
	string fileOutTxtName="";

	ifstream fileInTxt;
	string fileInTxtName="";

	ofstream raport;
	string raportName="";

	ifstream fileInCSV;
	string fileInCSVName="";

	fstream fileOutBinary;
	string fileOutBinaryName="";

	Colectie <Pacient> colectiePacienti;
	Colectie <Consultatie> colectieConsultatii;
	Colectie <Medic> colectieMedici;
	Colectie <Angajat> colectieAngajati;
	Colectie <Asistent> colectieAsistenti;

public:
	
	#pragma region Constructori

	FileManager() {};

	FileManager(const string fileInTxt, const string fileOutTxt, const string raportName, string numeColectie) {
		this->numeColectie = numeColectie;

		this->fileOutTxtName = fileOutTxt;
		this->fileOutTxt.open(this->fileOutTxtName, ios::out);

		this->fileInTxtName = fileInTxt;
		this->fileInTxt.open(this->fileInTxtName, ios::in);

		this->raportName = raportName;
		this->raport.open(this->raportName, ios::out);
	}

	FileManager(const string fileInTxt, const string file, string numeColectie) {
		
		this->numeColectie = numeColectie;

		this->fileInTxtName = fileInTxt;
		this->fileInTxt.open(this->fileInTxtName, ios::in);

		string type = file.substr(file.size() - 3);
		if (type == "csv") {
			this->fileInCSVName = file;
			this->fileInCSV.open(fileInCSVName, ios::in);
		}
		else if (type == "bin" || type == "txt") {
			this->fileOutBinaryName = file;
			this->fileOutBinary.open(this->fileOutBinaryName, ios::out|ios::binary);
		}
	}

	#pragma endregion
	
	#pragma region MetodeAccesor

	void setFileInTxt(const string fileInTxt) {
		this->fileInTxt.close();
		this->fileInTxtName = fileInTxt;
		this->fileInTxt.open(fileInTxt, ios::in);
	}

	void setFileOutTxt(const string fileOutTxt) {
		this->fileOutTxt.close();
		this->fileOutTxtName = fileOutTxt;
		this->fileOutTxt.open(fileOutTxt, ios::out);
	}

	void setRaport(const string raportName) {
		this->raport.close();
		this->raportName = raportName;
		this->raport.open(raportName, ios::out);
	}

	void setFileCSV(const string csvName) {
		this->fileInCSV.close();
		this->fileInCSVName = csvName;
		this->fileInCSV.open(csvName, ios::out);
	}

	void setFileOutBinary(const string binaryName) {
		this->fileOutBinaryName = binaryName;
		if (this->fileOutBinary) {
			this->fileOutBinary.close();
		}
		this->fileOutBinary.open(this->fileOutBinaryName, ios::out| ios::binary);
	}

	string getFileInTxtName() const {
		return this->fileInTxtName;
	}

	string getFileOutTxtName() const {
		return this->fileOutTxtName;
	}

	string getRaportName() const {
		return this->raportName;
	}

	string getFileOutBinary() const {
		return this->fileOutBinaryName;
	}

	Colectie <Medic> getMedici() {
		return this->colectieMedici;
	}

	void setColectieMedici(Medic *m, int nrObiecte) {
		this->colectieMedici.setColectie(nrObiecte, m);
	}

	Colectie<Angajat> getAngajati() {
		return this->colectieAngajati;
	}

	void setColectieAngajati(Angajat* a, int nrObiecte) {
		this->colectieAngajati.setColectie(nrObiecte, a);
	}

	Colectie <Asistent> getAsistenti() {
		return this->colectieAsistenti;
	}

	void setColectieAsistenti(Asistent *a,int nrObiecte) {
		this->colectieAsistenti.setColectie(nrObiecte, a);
	}

	Colectie <Pacient> getPacienti() {
		return this->colectiePacienti;
	}

	void setColectiePacienti(Pacient* p, int nrObiecte) {
		this->colectiePacienti.setColectie(nrObiecte, p);
	}

	Colectie <Consultatie> getConsultatie() {
		return this->colectieConsultatii;
	}

	void setColectieConsultatii(Consultatie* c, int nrObiecte) {
		this->colectieConsultatii.setColectie(nrObiecte, c);
	}

	void setNumeColectie(string numeColectie) {
		this->numeColectie = numeColectie;
	}

	string getNumeColectie() {
		return this->numeColectie;
	}

#pragma endregion

	#pragma region closeFiles
	void closeFileInTxt() {
		this->fileInTxt.close();
		this->fileInTxt.open(this->fileInTxtName, ios::in);
	}
#pragma endregion

	#pragma region updateCollection
	template<typename TIP>
	void updateColllection(Colectie<TIP> collection) {
		this->fileInTxt.close();
		ofstream auxiliar;
		auxiliar.open(this->fileInTxtName, ios::out);
		auxiliar << collection.getNrObiecte()<<endl;
		for (int i = 0; i < collection.getNrObiecte(); i++) {
			auxiliar << collection.getColectie()[i];
		}
		auxiliar.close();
		this->fileInTxt.open(this->fileInTxtName, ios::in);
	}
	#pragma endregion

	#pragma region setColectie
	
	void setColectieFile() {
		if (this->numeColectie == "Medici") {
			this->setMedici();
		}
		else if (this->numeColectie == "Pacienti") {
			this->setPacienti();
		}
		else if (this->numeColectie == "Consultatii") {
			this->setConsultatii();
		}
		else if (this->numeColectie == "Asistenti") {
			this->setAsistenti();
		}
		else if (this->numeColectie == "Angajati") {
			this->setAngajati();
		}
		else {
			return;
		}
	}

	#pragma endregion


	#pragma region MedicIsIncluded
	int MedicIsIncluded(Medic m) {
		for (int i = 0; i < this->colectieMedici.getNrObiecte(); i++) {
			if (this->colectieMedici.getColectie()[i] == m) {
				return 1;
			}
		}
		return 0;
	}
#pragma endregion	

	#pragma region Pacient

	void setPacienti() {
		Pacient* p;
		int nrObiecte;
		this->fileInTxt >> nrObiecte;
		p = new Pacient[nrObiecte];
		for (int i = 0; i < nrObiecte; i++) {
			this->fileInTxt >> p[i];
		}

		colectiePacienti.setColectie(nrObiecte, p);
	}

	void printPacienti() {
		if (this->fileInTxt.is_open()) {
			this->fileOutTxt << this->colectiePacienti.getNrObiecte() << endl;
			for (int i = 0; i < this->colectiePacienti.getNrObiecte(); i++) {
				this->fileOutTxt << this->colectiePacienti[i] << endl;
			}
		}
		else {
			cout << "Nu ati setat/ nu ati setat corect fisierul";
		}
	}

	void generareRaportPacienti() {
		for (int i = 0; i < colectiePacienti.getNrObiecte(); i++) {
			colectiePacienti[i].creareRaport(this->raport);
		}
	}

	void printBinaryPacienti() {
		for (int i = 0; i < colectiePacienti.getNrObiecte(); i++) {
			colectiePacienti[i].writeBinary(this->fileOutBinary);
		}
	}

	void readPacientiFromCSV(char delim[]) {
		int numar;
		this->fileInCSV >> numar;
		if (numar > 0) {
			Pacient* p;
			int nrActual = this->colectiePacienti.getNrObiecte();
			int numarPacienti = numar + nrActual;
			p = new Pacient[numarPacienti];
			for (int i = 0; i < numarPacienti; i++) {
				if (i < nrActual) {
					p[i] = this->colectiePacienti.getColectie()[i];
				}
				else {
					p[i].citireCSV(this->fileInCSV, delim);
				}
				cout << p[i];
			}
			this->colectiePacienti.setColectie(numarPacienti, p);

		}
	}
	
	#pragma endregion	

	#pragma region Consultatie
	
	void setConsultatii() {
		Consultatie* c;
		int nrObiecte;
		this->fileInTxt >> nrObiecte;
		c = new Consultatie[nrObiecte];
		for (int i = 0; i < nrObiecte; i++) {
			this->fileInTxt >> c[i];
		}
		this->colectieConsultatii.setColectie(nrObiecte, c);
	}

	void printConsultatii() {
		this->fileOutTxt << this->colectieConsultatii.getNrObiecte()<<endl;
		for (int i = 0; i < this->colectieConsultatii.getNrObiecte(); i++) {
			this->fileOutTxt << this->colectieConsultatii[i]<<endl;
		}
		
	}
	
	void generareRaportConsultatii() {
		for (int i = 0; i < colectieConsultatii.getNrObiecte(); i++) {
			colectieConsultatii[i].creareRaport(this->raport);
		}
	}

	void printBinaryConsultatii() {
		for (int i = 0; i < colectieConsultatii.getNrObiecte(); i++) {
			colectieConsultatii[i].writeBinary(this->fileOutBinary);
		}
	}

	#pragma endregion

	#pragma region Angajati
	
	void setAngajati() {
		Angajat* a;
		int nrObiecte;
		this->fileInTxt >> nrObiecte;
		a = new Angajat[nrObiecte];
		for (int i = 0; i < nrObiecte; i++) {
			this->fileInTxt >> a[i];
		}
		colectieAngajati.setColectie(nrObiecte, a);
	}

	void printAngajati() {
		this->fileOutTxt << this->colectieAngajati.getNrObiecte()<<endl;
		for (int i = 0; i < colectieAngajati.getNrObiecte(); i++) {
			this->fileOutTxt << colectieAngajati[i]<<endl;
		}
	}

	void generareRaportAngajati() {
		for (int i = 0; i < colectieAngajati.getNrObiecte(); i++) {
			colectieAngajati[i].creareRaport(this->raport);
		}
	}

	void printBinaryAngajati() {
		for (int i = 0; i < colectieAngajati.getNrObiecte(); i++) {
			colectieAngajati[i].writeBinary(this->fileOutBinary);
		}
	}

	#pragma endregion

	#pragma region Asistenti

	void setAsistenti() {
		Asistent* a;
		int nrObiecte;
		this->fileInTxt >> nrObiecte;
		a = new Asistent[nrObiecte];
		for (int i = 0; i < nrObiecte; i++) {
			this->fileInTxt >> a[i];
		}
		colectieAsistenti.setColectie(nrObiecte, a);
		delete[] a;
	}

	void printAsistenti() {
		this->fileOutTxt << this->colectieAsistenti.getNrObiecte()<<endl;
		for (int i = 0; i < this->colectieAsistenti.getNrObiecte(); i++) {
			this->fileOutTxt << this->colectieAsistenti[i] << endl;
		}
	}

	void generareRaportAsistenti() {
		for (int i = 0; i < colectieAsistenti.getNrObiecte(); i++) {
			colectieAsistenti[i].creareRaport(this->raport);
		}
	}

	void printBinaryAsistenti() {
		for (int i = 0; i < colectieAsistenti.getNrObiecte(); i++) {
			colectieAsistenti[i].writeBinary(this->fileOutBinary);
		}
	}

	#pragma endregion

	#pragma region Medici

	void setMedici() {
		Medic* m;
		int nrObiecte;
		this->fileInTxt >> nrObiecte;
		m = new Medic[nrObiecte];
		for (int i = 0; i < nrObiecte; i++) {
			this->fileInTxt >> m[i];
		}
		colectieMedici.setColectie(nrObiecte, m);
		delete[] m;
	}

	void printMedici() {
		this->fileOutTxt << this->colectieMedici.getNrObiecte() << endl;
		for (int i = 0; i < this->colectieMedici.getNrObiecte(); i++) {
			this->fileOutTxt << this->colectieMedici[i] << endl;
		}
	}

	void generareRaportMedici() {
		for (int i = 0; i < colectiePacienti.getNrObiecte(); i++) {
			colectieMedici[i].creareRaport(this->raport);
		}
	}

	void printBinaryMedici() {
		for (int i = 0; i < colectieMedici.getNrObiecte(); i++) {
			colectieMedici[i].writeBinary(this->fileOutBinary);
		}
	}

	#pragma endregion

	#pragma region Destructor
		~FileManager() {
		this->fileInTxt.close();
		this->fileOutTxt.close();
		this->raport.close();
		this->fileOutBinary.close();
	}
	#pragma endregion

};

