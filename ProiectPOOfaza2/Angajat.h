#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <string.h>
#include <fstream>
#include "Functii.h"
#include "Persoana.h"
#include <ctime>

class Angajat:public Persoana {
protected:
    const int id;
    static int contor;
    static char luni[13][30];
    static int MINIM_SALARIU;
    static int MEDIU_SALARIU;
    char* nume = nullptr;
    string prenume = "";
    int vechimeCentru = 0;
    int istoricNrConsultatiiLunare[30] = { 0 };
    float istoricVenituriLunare[12] = { 0 };
    int istoricOreLucrate[12] = { 0 };
    float salariu = 0;
    int varsta = 0;
public:

#pragma region Constructor_fara_parametrii
    Angajat() :id(contor++) {
        this->nume = nullptr;
        this->prenume = "";
        this->vechimeCentru = 0;
    }
#pragma endregion

#pragma region Constructor_cu_cativa_paramterii
    Angajat(const char* nume, const string prenume, const float salariu, const int varsta) :id(contor++) {
        if (verifSiruriCaractere(nume)) {
            this->nume = new char[strlen(nume) + 1];
            strcpy(this->nume, nume);
        }

        if (verifSiruriCaractere(prenume.c_str())) {
            this->prenume = prenume;
        }
        if (salariu > Angajat::MINIM_SALARIU) {
            this->salariu = salariu;
        }
        else {
            this->salariu = Angajat::MINIM_SALARIU;
        }

        if (varsta >= 0) {
            this->varsta = varsta;
        }
        else {
            this->varsta = 0;
        }
    }
#pragma endregion

#pragma region Constructor_cu_toti_paramterii
    Angajat(const char* nume, const string prenume, float salariu, int varsta, const int vechime, const int istoricNrConsultatiiLunare[], const float istoricVenituriLunare[], const int istoricOreLucrate[]) :Angajat(nume, prenume, salariu, varsta) {
        if (vechime >= 0) {
            this->vechimeCentru = vechime;
            int* aux = new int[12];
            aux = verifIstoric<int>(istoricNrConsultatiiLunare, this->vechimeCentru, 0);
            for (int i = 0; i < 12; i++) {
                this->istoricNrConsultatiiLunare[i] = aux[i];
            }
            delete[]aux;


            float* aux2 = new float[12];
            aux2 = verifIstoric<float>(istoricVenituriLunare, this->vechimeCentru, Angajat::MINIM_SALARIU);
            for (int i = 0; i < 12; i++) {
                this->istoricVenituriLunare[i] = aux2[i];
            }
            delete[] aux2;

            int* aux3 = new int[12];
            aux3 = verifIstoric<int>(istoricOreLucrate, this->vechimeCentru, 6);
            for (int i = 0; i < 12; i++) {
                this->istoricOreLucrate[i] = aux3[i];
            }
            delete[]aux3;
        }
        else {
            this->vechimeCentru = 0;
        }

    }
#pragma endregion

#pragma region Constructor_de_copiere
    Angajat(const Angajat& m) :Angajat() {
        if (this->nume != nullptr) {
            delete[] this->nume;
        }
        if (m.nume != nullptr) {
            if (verifSiruriCaractere(m.nume)) {
                this->nume = new char[strlen(m.nume) + 1];
                strcpy(this->nume, m.nume);
            }
            else {
                this->nume = nullptr;
            }
        }
        else {
            this->nume = nullptr;
        }
        if (m.prenume != "") {
            if (verifSiruriCaractere(m.prenume.c_str())) {
                this->prenume = m.prenume;
            }
            else {
                this->prenume = "";
            }
        }
        else {
            this->prenume = "";
        }
       
        if (m.salariu > Angajat::MINIM_SALARIU) {
            this->salariu = m.salariu;
        }
        else {
            this->salariu = Angajat::MINIM_SALARIU;
        }


        if (m.varsta >= 0) {
            this->varsta = m.varsta;
        }
        else {
            this->varsta = 0;
        }
        if (m.vechimeCentru >= 0) {
            this->vechimeCentru = m.vechimeCentru;
            int* aux = new int[12];
            aux = verifIstoric<int>(m.istoricNrConsultatiiLunare, this->vechimeCentru, 0);
            for (int i = 0; i < 12; i++) {
                this->istoricNrConsultatiiLunare[i] = aux[i];
            }
            delete[]aux;


            float* aux2 = new float[12];
            aux2 = verifIstoric<float>(m.istoricVenituriLunare, this->vechimeCentru, Angajat::MINIM_SALARIU);
            for (int i = 0; i < 12; i++) {
                this->istoricVenituriLunare[i] = aux2[i];
            }
            delete[] aux2;

            int* aux3 = new int[12];
            aux3 = verifIstoric<int>(m.istoricOreLucrate, this->vechimeCentru, 6);
            for (int i = 0; i < 12; i++) {
                this->istoricOreLucrate[i] = aux3[i];
            }
            delete[]aux3;
        }
        else {
            this->vechimeCentru = 0;
        }

    }
#pragma endregion

#pragma region MetodaRaport
    virtual void creareRaport(ofstream& out) {
        out << "\n---------------------------------------------------------\n";
        out << "\n\n\nDate referitoare la Angajatul cu id-ul: " << this->id;
        if (this->prenume != "" && this->nume != nullptr) {
            out << endl << "Numele Angajatului: " << this->nume << endl;
            out << "Prenumele Angajatului: " << this->prenume << endl;
            if (this->vechimeCentru == 0) {
                out << "Angajatul abia s-a transferat in cadrul acestui centru medical";
            }
            else {
                out << "Angajatul are o experienta de " << this->vechimeCentru << "luni in cadrul acestui centru medical." << endl;
            }
            out << "Angajatul are un salariu in valoare de " << this->salariu << " RON" << endl;
            out << "Varsta angajatului este de : " << this->varsta << " ani" << endl;

            if (this->vechimeCentru > 0) {
                for (int i = 0; i < 12; i++) {
                    out << this->luni[i] << ": " << this->istoricNrConsultatiiLunare[i] << "\n";
                }
                out << "Veniturile incasate in cadrul acestui an: " << endl;
                for (int i = 0; i < 12; i++) {
                    out << this->luni[i] << ": " << this->istoricVenituriLunare[i] << "\n";
                }
                out << "Numarul de ore lucrate lunar in cadrul acestui an: " << endl;
                for (int i = 0; i < 12; i++) {
                    out << this->luni[i] << ": " << this->istoricOreLucrate[i] << "\n";
                }
            }

        }
        else {
            out << "\nNu avem date referitoare la acest Angajat\n";
        }
    }
#pragma endregion

#pragma region WriteBinary
    virtual void writeBinary(fstream& f) {

        int lenNume = (strlen(this->nume) + 1)*sizeof(char);
        f.write((char*)&lenNume, sizeof(int));
        f.write((char*)&this->nume, lenNume);
       
        int len = (this->prenume.length())*sizeof(char);
        f.write((char*)&len, sizeof(int));
        f.write((char*)&this->prenume, len);
        f.write((char*)&this->varsta, sizeof(int));
        f.write((char*)&this->salariu, sizeof(float));
        f.write((char*)&this->vechimeCentru, sizeof(int));
        for (int i = 0; i < this->vechimeCentru; i++) {
            f.write((char*)&this->istoricNrConsultatiiLunare[i], sizeof(int));
        }
        for (int i = 0; i < this->vechimeCentru; i++) {
            f.write((char*)&this->istoricVenituriLunare[i], sizeof(float));
        }
        for (int i = 0; i < this->vechimeCentru; i++) {
            f.write((char*)&this->istoricOreLucrate[i], sizeof(int));
        }
    }
#pragma endregion

#pragma region citireCSV

    virtual void citireCSV(ifstream& f, char delim[]) {
        string line;
        strcat(delim, " ");
        getline(f, line);
        char l[100];
        strcpy(l, line.c_str());

        char* token = strtok(l, delim);
        this->setNume(token);

        token = strtok(NULL, delim);
        this->setPrenume(token);

        token = strtok(NULL, delim);
        this->setVarsta(atoi(token));

        token = strtok(NULL, delim);
        this->setSalariu(atof(token));

        token = strtok(NULL, delim);
        this->setVechime(0);
    }

#pragma endregion

#pragma region MetodaOneYearPassed

    void OneYearPassed(int salariu) {
        for (int i = 0; i < 12; i++) {
            this->istoricVenituriLunare[i] = 0;
            this->istoricOreLucrate[i] = 0;
            this->istoricNrConsultatiiLunare[i] = 0;
        }
        this->salariu = salariu;
    }
#pragma endregion

#pragma region Metoda_AdaugaBonus
    void adaugaBonus() {
        float sum = 0;
        for (int i = 0; i < 12; i++) {
            sum += this->istoricOreLucrate[i];
        }
        sum = sum * 30;
        this->salariu = this->salariu + sum;
    }

#pragma endregion

#pragma region MetodaMoare
    virtual void Persoana::Moare() {
        if (this->nume != nullptr) {
            delete[]this->nume;
        }
        this->nume = new char[8];
        strcpy(this->nume,"Angajat");
        this->prenume = "Decedat";
        time_t theTime = time(NULL);
        struct tm* aTime = localtime(&theTime);

        int ziuaCurenta = aTime->tm_mday;
        int lunaCurenta = aTime->tm_mon + 1;
        int anulCurent = aTime->tm_year + 1900;
        cout << "Angajatul a decedat la data de "<<ziuaCurenta<<"/"<<lunaCurenta<<"/"<<anulCurent<<endl;
    }
#pragma endregion

#pragma region SchimbaIdentitatea
    void Persoana::SchimbaIdentitatea(){
        cout<< "Introduceti noul nume al angajatului:\n";
        string nume, prenume;
        cin >> nume;
        cout << "Introduceti noul prenume al angajatului:\n";
        cin >> prenume;
        this->setNume(nume.c_str());
        this->setPrenume(prenume);
        cout << "Introduceti noua varsta a angajatului:\n";
        int varsta;
        cin >> varsta;
        this->setVarsta(varsta);
        cout << "\nSchimbarea de identitate a avut loc cu succes\n";
    }
#pragma region

#pragma region Metode_Accesor
    void setNume(const char* nume) {
        if (this->nume != nullptr) {
            delete[] this->nume;
        }
        if (verifSiruriCaractere(nume)) {
            this->nume = new char[strlen(nume) + 1];
            strcpy(this->nume, nume);
        }
        else {
            this->nume = nullptr;
        }
    }

    char* getNume() const {
        return this->nume;
    }

    void setPrenume(const string prenume) {
        if (verifSiruriCaractere(prenume.c_str())) {
            this->prenume = prenume;
        }
    }

    string getPrenume() const {
        return this->prenume;

    }

    void setSalariu(const float salariu) {
        if (salariu > Angajat::MINIM_SALARIU) {
            this->salariu = salariu;
        }
        else {
            this->salariu = Angajat::MINIM_SALARIU;
        }
    }

    float getSalariu() const {
        return this->salariu;
    }

    void setVarsta(const int varsta) {
        if (varsta >= 0) {
            this->varsta = varsta;
        }
        else {
            this->varsta = 0;
        }
    }

    int getVarsta() {
        return this->varsta;
    }

  
    void setVechime(int vechime) {
        if (vechime >= 0) {
            this->vechimeCentru = vechime;
        }
        else {
            this->vechimeCentru = 0;
        }
    }

    int getVechime() const {
        return this->vechimeCentru;
    }

    void setIstoricConsultatiiLunare(int istoricNrConsultatiiLunare[]) {
        if (this->vechimeCentru > 0) {
            int* aux = new int[12];
            aux = verifIstoric<int>(istoricNrConsultatiiLunare, this->vechimeCentru, 0);
            for (int i = 0; i < 12; i++) {
                this->istoricNrConsultatiiLunare[i] = aux[i];
            }
            delete[]aux;
        }
    }

    int* getIstoricNrConsultatiiLunare() {
        return this->istoricNrConsultatiiLunare;
    }

    void setIstoricVenituriLunare(const float istoricVenituriLunare[]) {
        if (this->vechimeCentru > 0) {
            float* aux2 = new float[12];
            aux2 = verifIstoric<float>(istoricVenituriLunare, this->vechimeCentru, Angajat::MINIM_SALARIU);
            for (int i = 0; i < 12; i++) {
                this->istoricVenituriLunare[i] = aux2[i];
            }
            delete[] aux2;
        }
    }

    float* getIstoricVenituriLunare() {
        return this->istoricVenituriLunare;
    }

    void setIstoricOreLucrate(int istoricOreLucrate[]) {
        if (this->vechimeCentru > 0) {
            int* aux3 = new int[12];
            aux3 = verifIstoric<int>(istoricOreLucrate, this->vechimeCentru, 6);
            for (int i = 0; i < 12; i++) {
                this->istoricOreLucrate[i] = aux3[i];
            }
            delete[]aux3;
        }
    }

    int* getIstoricOreLucarte() {
        return this->istoricOreLucrate;
    }

#pragma endregion

#pragma region Operatorul_De_Negatie
    bool operator!() {
        if (this->salariu > Angajat::MEDIU_SALARIU) {
            return true;
        }
        return false;
    }
#pragma endregion

#pragma region Operatorul_Minus
    Angajat& operator-(float val) {
        this->salariu -= val;
        return *this;
    }
#pragma endregion

#pragma region Operatorul_egal
    Angajat& operator = (const Angajat& m) {
        if (this != &m) {
            if (this->nume != nullptr) {
                delete[] this->nume;
            }
            if (verifSiruriCaractere(m.nume)) {
                this->nume = new char[strlen(m.nume) + 1];
                strcpy(this->nume, m.nume);
            }
            else {
                this->nume = nullptr;
            }

            if (verifSiruriCaractere(m.prenume.c_str())) {
                this->prenume = m.prenume;
            }
            else {
                this->prenume = "";
            }
            if (m.salariu > Angajat::MINIM_SALARIU) {
                this->salariu = m.salariu;
            }
            else {
                this->salariu = Angajat::MINIM_SALARIU;
            }
           

            if (m.varsta >= 0) {
                this->varsta = m.varsta;
            }
            else {
                this->varsta = 0;
            }
            if (m.vechimeCentru >= 0) {
                this->vechimeCentru = m.vechimeCentru;
                int* aux = new int[12];
                aux = verifIstoric<int>(m.istoricNrConsultatiiLunare, this->vechimeCentru, 0);
                for (int i = 0; i < 12; i++) {
                    this->istoricNrConsultatiiLunare[i] = aux[i];
                }
                delete[]aux;


                float* aux2 = new float[12];
                aux2 = verifIstoric<float>(m.istoricVenituriLunare, this->vechimeCentru, Angajat::MINIM_SALARIU);
                for (int i = 0; i < 12; i++) {
                    this->istoricVenituriLunare[i] = aux2[i];
                }
                delete[] aux2;

                int* aux3 = new int[12];
                aux3 = verifIstoric<int>(m.istoricOreLucrate, this->vechimeCentru, 6);
                for (int i = 0; i < 12; i++) {
                    this->istoricOreLucrate[i] = aux3[i];
                }
                delete[]aux3;
            }
            else {
                this->vechimeCentru = 0;
            }
        }
        return *this;
    }
#pragma endregion

#pragma region Operatorul_Cast
    operator int() {
        return this->vechimeCentru;
    }
#pragma endregion

#pragma region Operator_Indexare
    int& operator[] (int index) {
        if (index >= 0 && index < this->vechimeCentru) {
            return this->istoricNrConsultatiiLunare[index];
        }

    }
#pragma endregion 

#pragma region Operatorul_Comparatie
    bool operator >= (Angajat& m) {
        if (this->salariu >= m.salariu) {
            return true;
        }
        else {
            return false;
        }
    }
#pragma endregion

#pragma region Operatorul_incrementare
    Angajat& operator++ () {
        this->vechimeCentru++;
        return *this;
    }
#pragma endregion

#pragma region Operatorul_Egal_Egal
    bool operator == (Angajat m) {
        if (this->vechimeCentru == m.vechimeCentru) {
            return true;
        }
        else {
            return false;
        }
    }
#pragma endregion

#pragma region Operatorul_de_citire
    friend istream& operator >> (istream& in, Angajat& m) {
        cout << "\nIntroduceti prenumele Angajatului:\n";
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
        cout << "Intorduceti numele Angajatului:\n";
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
        cout << "Introduceti vechimea angajatului in cadrul acestui centru Angajatal:\n";
        in >> vechime;
        if (vechime > 0) {
            m.vechimeCentru = vechime;
        }

        int varsta;
        cout << "Introduceti varsta angajatului:\n";
        in >> varsta;
        if (varsta > 0) {
            m.varsta = varsta;
        }
        else {
            m.varsta = 0;
        }

        cout << "Introduceti numarul consultatiilor sustinute de acest Angajat pe parcursul acestui an:\n";
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
            aux2 = verifIstoric<float>(istoricVenituriLunare, m.vechimeCentru, Angajat::MINIM_SALARIU);
            for (int i = 0; i < 12; i++) {
                m.istoricVenituriLunare[i] = aux2[i];
            }
            delete[] aux2;
        }

        float salariu;
        cout << "Introduceti salariul curent: \n";
        in >> salariu;

        if (salariu > Angajat::MINIM_SALARIU) {
            m.salariu = salariu;
        }
        else {
            m.salariu = Angajat::MINIM_SALARIU;
        }

        int istoricOreLucrate[12];
        cout << "Introduceti orele lucrate in lunile anului acesta de catre Angajat: \n";
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

        return in;
    }

#pragma endregion

#pragma region Operator_Scriere
    friend ostream& operator <<(ostream& out, const Angajat& m) {
        out << "\n\n\nDate referitoare la Angajatul cu id-ul: " << m.id;
        if (m.prenume != "" && m.nume != nullptr) {
            out << endl << "Numele Angajatului: " << m.nume << endl;
            out << "Prenumele Angajatului: " << m.prenume << endl;
            if (m.vechimeCentru == 0) {
                out << "Angajatul abia s-a transferat in cadrul acestui centru medical";
            }
            else {
                out << "Angajatul are o experienta de " << m.vechimeCentru << "luni in cadrul acestui centru medical." << endl;
            }
            out << "Angajatul are un salariu in valoare de " << m.salariu << " RON" << endl;
            out << "Varsta angajatului este de : " << m.varsta << " ani" << endl;
            if (m.vechimeCentru > 0) {
                out << "Numarul de consultatii de anul acesta sustinute de catre Angajat este urmatorul:\n";

                for (int i = 0; i < 12; i++) {
                    out << m.luni[i] << ": " << m.istoricNrConsultatiiLunare[i] << "\n";
                }
                out << "Veniturile incasate in cadrul acestui an: " << endl;
                for (int i = 0; i < 12; i++) {
                    out << m.luni[i] << ": " << m.istoricVenituriLunare[i] << "\n";
                }
                out << "Numarul de ore lucrate lunar in cadrul acestui an: " << endl;
                for (int i = 0; i < 12; i++) {
                    out << m.luni[i] << ": " << m.istoricOreLucrate[i] << "\n";
                }
            }

        }
        else {
            out << "\nNu avem date referitoare la acest Angajat\n";
        }
        return out;
    }
#pragma endregion

#pragma region Citire_Fisier
    friend ifstream& operator>>(ifstream& in, Angajat& m) {
        string prenume;
        in >> prenume;
        int ok = 1;
        if (verifSiruriCaractere(prenume.c_str())) {
            m.prenume = prenume;
        }
        else {
            ok = 0;
        }
        char nume[30];
        in >> nume;
        if (m.nume != nullptr) {
            delete[] m.nume;
        }
        if (verifSiruriCaractere(nume)) {
            m.nume = new char[strlen(nume)+1];
            strcpy(m.nume, nume);
        }
        else {
            m.nume = nullptr;
            ok = 0;
        }
        if (ok != 0) {
            
            float salariu;
            in >> salariu;
            if (salariu > Angajat::MINIM_SALARIU) {
                m.salariu = salariu;
            }
            else {
                m.salariu = Angajat::MINIM_SALARIU;
            }
            int varsta;
            in >> varsta;
            if (varsta > 0) {
                m.varsta = varsta;
            }
            else {
                m.varsta = 0;
            }

            int vechime;
            in >> vechime;
            if (vechime > 0) {
                m.vechimeCentru = vechime;
            }
            else {
                m.vechimeCentru = 0;
            }

            int istoricNrConsultatiiLunare[12];
            for (int i = 0; i < 12; i++) {
                in >> istoricNrConsultatiiLunare[i];
            }


            if (m.vechimeCentru > 0) {
                int* aux = new int[12];
                aux = verifIstoric<int>(istoricNrConsultatiiLunare, m.vechimeCentru, 0);
                for (int i = 0; i < 12; i++) {
                    m.istoricNrConsultatiiLunare[i] = aux[i];
                }
                delete[]aux;
            }

            float istoricVenituriLunare[12];
            for (int i = 0; i < 12; i++) {
                in >> istoricVenituriLunare[i];
            }

            if (m.vechimeCentru > 0) {
                float* aux2 = new float[12];
                aux2 = verifIstoric<float>(istoricVenituriLunare, m.vechimeCentru, Angajat::MINIM_SALARIU);
                for (int i = 0; i < 12; i++) {
                    m.istoricVenituriLunare[i] = aux2[i];
                }
                delete[] aux2;
            }

            int istoricOreLucrate[12];

            for (int i = 0; i < 12; i++) {
                in >> istoricOreLucrate[i];
            }

            int* aux3 = new int[12];
            aux3 = verifIstoric<int>(istoricOreLucrate, m.vechimeCentru, 6);
            for (int i = 0; i < 12; i++) {
                m.istoricOreLucrate[i] = aux3[i];
            }
            delete[]aux3;
        }
        return in;
    }
#pragma endregion

#pragma region Scriere_Fisier
    friend ofstream& operator <<(ofstream& out, const Angajat& m) {
        if (m.prenume != "" && m.nume != nullptr) {
            out << m.nume << endl;
            out << m.prenume << endl;
            out << m.salariu << endl;
            out << m.varsta << endl;
            out << m.vechimeCentru << endl;
            if (m.vechimeCentru > 0) {
                for (int i = 0; i < 12; i++) {
                    out << m.istoricNrConsultatiiLunare[i] << " ";
                }
                out << endl;

                for (int i = 0; i < 12; i++) {
                    out << m.istoricVenituriLunare[i] << " ";
                }
                out << endl;
                for (int i = 0; i < 12; i++) {
                    out << m.istoricOreLucrate[i] << " ";
                }
            }
            out << endl;
        }
        return out;
    }

#pragma endregion

#pragma region Destructor
    ~Angajat() {
        delete[] this->nume;
    }
#pragma endregion

};

int Angajat::contor = 0;
char Angajat::luni[13][30] = { "Ianuarie", "Februarie", "Martie", "Aprilie","Mai", "Iunie", "Iulie", "August", "Septembrie", "Octombrie","Noiembrie", "Decembrie" };
int Angajat::MINIM_SALARIU = 1542;
int Angajat::MEDIU_SALARIU = 3629;