#pragma once

#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include "Functii.h"
#include "Medic.h"
#include "Data.h"
#include "Consultatie.h"
#include "Persoana.h"

using namespace std;

#pragma region Clasa_Pacient 
class Pacient:Persoana{
    static int contor;
    const int id;
    string nume = "";
    char* prenume = nullptr;
    int varsta = 0;
    int nrConsultatii = 0;
    char adresa[60];
    Consultatie* viitoareConsultatii = nullptr;
    char* phoneNumber = nullptr;
    bool esteAsigurat = false;
    int nrPlati = 0;
    float* istoricPlati = nullptr;
public:

#pragma region Contructor_fara_parametrii
    Pacient() :id(contor++) {
        this->nume = "";
        this->prenume = nullptr;
        this->varsta = 0;
        this->nrConsultatii = 0;
        strcpy(this->adresa, "a");
        Consultatie* viitoareConsultatii = nullptr;
        this->phoneNumber = nullptr;
        this->esteAsigurat = false;
        this->nrPlati = 0;
        this->istoricPlati = nullptr;
    }
#pragma endregion

#pragma region Constructor_cu_cativa_parametrii
    Pacient(const char* prenume, const string nume, const char* phoneNumber, int varsta, const char adresa[30], bool eAsigurat)
        :id(contor++)
    {

        if (verifSiruriCaractere(prenume)) {
            this->prenume = new char [strlen(prenume) + 1];
            strcpy(this->prenume, prenume);
        }        

        if (verifSiruriCaractere(nume.c_str())) {
            this->nume = nume;
        }

        if (verifTelefon(phoneNumber)) {
            this->phoneNumber = new char[11];
            strcpy(this->phoneNumber, phoneNumber);
        }

        if (varsta >= 0) {
            this->varsta = varsta;
        }
        else {
            this->varsta = 0;
        }

        if (strlen(adresa) > 10) {
            strcpy(this->adresa, adresa);
        }
        else {
            strcpy(this->adresa, "");
        }

        this->esteAsigurat = esteAsigurat;
    }
#pragma endregion

#pragma region Constructor_cu_toti_parametrii
    Pacient(const char* prenume, const string nume, const char* phoneNumber, const int varsta, const char adresa[30], const bool eAsigurat, const int nrConsultatii, Consultatie* viitoareConsultatii,
        const float* istoricPlati, const int nrPlati)
        :id(contor++) {


        if (verifSiruriCaractere(prenume)) {
            this->prenume = new char[strlen(prenume) + 1];
            strcpy(this->prenume, prenume);
        }

        if (verifSiruriCaractere(nume.c_str())) {
            this->nume = nume;
        }

        if (verifTelefon(phoneNumber)) {
            this->phoneNumber = new char[11];
            strcpy(this->phoneNumber, phoneNumber);
        }


        if (nrPlati > 0) {
            this->nrPlati = nrPlati;
            this->istoricPlati = new float[this->nrPlati];
            for (int i = 0; i < this->nrPlati; i++) {
                if (istoricPlati[i] > 50) {
                    this->istoricPlati[i] = istoricPlati[i];
                }
                else {
                    this->istoricPlati[i] = 50;
                }
            }
        }
        else {
            this->nrPlati = 0;
            this->istoricPlati = nullptr;
        }

        if (varsta >= 0) {
            this->varsta = varsta;
        }
        else {
            this->varsta = 0;
        }

        if (strlen(adresa) > 10) {
            strcpy(this->adresa, adresa);
        }
        else {
            strcpy(this->adresa, "");
        }

        this->esteAsigurat = esteAsigurat;

        if (nrConsultatii > 0) {
            this->nrConsultatii = nrConsultatii;
        }
        if (viitoareConsultatii != nullptr) {
            this->viitoareConsultatii = new Consultatie[this->nrConsultatii];
            for (int i = 0; i < this->nrConsultatii; i++) {
                this->viitoareConsultatii[i] = viitoareConsultatii[i];
            }
        }
        else {
            this->nrConsultatii = 0;
            this->viitoareConsultatii = nullptr;
        }
    }
#pragma endregion

#pragma region Constructor_de_copiere
    Pacient(const Pacient& p):Pacient(){
        if (this != &p) {
            if (this->prenume != nullptr)
            {
                delete[] this->prenume;
            }
            if (this->phoneNumber != nullptr) {
                delete[] this->phoneNumber;
            }
            if (this->istoricPlati != nullptr) {
                delete[] this->istoricPlati;
            }
            if (this->viitoareConsultatii == nullptr) {
                delete[] this->viitoareConsultatii;
            }

            if (verifSiruriCaractere(p.prenume)) {
                this->prenume = new char[strlen(p.prenume) + 1];
                strcpy(this->prenume, p.prenume);
            }

            if (verifSiruriCaractere(p.nume.c_str())) {
                this->nume = p.nume;
            }

            if (verifTelefon(p.phoneNumber)) {
                this->phoneNumber = new char[11];
                strcpy(this->phoneNumber, p.phoneNumber);
            }

            if (p.nrPlati > 0) {
                this->nrPlati = p.nrPlati;
                this->istoricPlati = new float[p.nrPlati];
                for (int i = 0; i < this->nrPlati; i++) {
                    if (p.istoricPlati[i] > 50) {
                        this->istoricPlati[i] = p.istoricPlati[i];
                    }
                    else {
                        this->istoricPlati[i] = 50;
                    }
                }
            }
            else {
                this->nrPlati = 0;
                this->istoricPlati = nullptr;
            }

            if (p.varsta >= 0) {
                this->varsta = p.varsta;
            }
            else {
                this->varsta = 0;
            }

            if (strlen(p.adresa) > 10) {
                strcpy(this->adresa, p.adresa);
            }
            else {
                strcpy(this->adresa, "");
            }

            this->esteAsigurat = p.esteAsigurat;

            if (p.nrConsultatii > 0) {
                this->nrConsultatii = p.nrConsultatii;
            }
            if (p.viitoareConsultatii != nullptr) {
                this->viitoareConsultatii = new Consultatie[this->nrConsultatii];
                for (int i = 0; i < this->nrConsultatii; i++) {
                    this->viitoareConsultatii[i] = p.viitoareConsultatii[i];
                }
            }
            else {
                this->nrConsultatii = 0;
                this->viitoareConsultatii = nullptr;
            }
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

#pragma region MetodaRaport
    void creareRaport(ofstream& out) {
        out << "\n---------------------------------------------------------------------\n";
        out << "\nDate referitoare la pacientul cu id-ul: " << this->id;
        if (this->prenume != nullptr && this->nume != "") {
            out << endl << "Pacientul are numele: " << this->nume << endl;
            out << "Pacientul are prenumele: " << this->prenume << endl;
            if (this->phoneNumber != nullptr) {
                out << "Numarul de telefon al pacientului: " << this->phoneNumber << endl;
            }
            out << "Pacientul are varsta: " << this->varsta << endl;

            if (strlen(this->adresa) > 10) {
                out << "Pacientul are urmatoarea adresa: \n" << this->adresa << endl;
            }
            else {
                out << "Adresa pacientului nu este inregistrata";
            }
            (this->esteAsigurat) ? out << "Pacientul este asigurat." << endl : out << "Pacientul nu este asigurat." << endl;
            out << "Pacientul are programate " << this->nrConsultatii << " consultatii" << endl;
            if (this->nrConsultatii != 0) {
                out << "Consultatiile programate, contin urmatoarele date: \n";
                for (int i = 0; i < this->nrConsultatii; i++) {
                    out << this->viitoareConsultatii[i];
                }
            }


            if (this->nrPlati == 0 || this->istoricPlati == nullptr) {
                out << "Pacientul nu a efectuat plati in cadrul centrului medical." << endl;
            }
            else {
                out << "Pana acum pacientul facut " << this->nrPlati << " plati in cadrul spitalului" << endl;
                out << "\nIata valoarea platilor realizate de pacient: \n \n";
                for (int i = 0; i < this->nrPlati; i++) {
                    out << "Plata cu numarul " << i + 1 << " a fost in valoare de : " << this->istoricPlati[i] << endl;
                }
            }


        }
        else {
            out << "\nNu avem date referitoare la acest pacient\n";
        }
    }
#pragma endregion

#pragma region citireCSV

    void citireCSV(ifstream& f, char delim[]) {
        string line;
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
        this->setAdresa(token);

        token = strtok(NULL, delim);
        this->setPhoneNumber(token);

        token = strtok(NULL, delim);
        this->setEsteAsigurat(token);

        token = strtok(NULL, delim);
        this->setNrPlati(0);
        this->setNrConsultatii(0);
    }

#pragma endregion
  
#pragma region WriteBinary
    void writeBinary(fstream &f) {
        int len = this->nume.length() + 1;
        f.write((char*)&len, sizeof(int));
        f.write((char*)&this->nume, len * sizeof(string));
        int lenPrenume = strlen(this->prenume);
        f.write((char*)&lenPrenume, sizeof(lenPrenume));
        f.write(this->prenume, lenPrenume*sizeof(char));
        f.write((char*)&this->varsta, sizeof(int));
        f.write((char*)&this->nrConsultatii, sizeof(int));
        size_t length = strlen(this->adresa);
        f.write((char*)&this->adresa, sizeof(length));
        for (int i = 0; i < this->nrConsultatii; i++) {
            this->viitoareConsultatii[i].writeBinary(f);
        }
        size_t lengthTelefon = strlen(this->phoneNumber);
        f.write((char*)&this->phoneNumber, sizeof(lengthTelefon));
        f.write((char*)&this->esteAsigurat, sizeof(bool));
        f.write((char*)&this->nrPlati, sizeof(this->nrPlati));
        for (int i = 0; i < this->nrPlati; i++) {
            f.write((char*)&this->istoricPlati[i], sizeof(float));
        }
    }
#pragma endregion

#pragma region Metode_accesor
    void setNume(const string nume) {
        if (verifSiruriCaractere(nume.c_str())) {
            this->nume = nume;
        }
    }

    string getNume() const{
        return this->nume;
    }

    void setViitoareConsultatii(int nrConsultatii, Consultatie* viitoareConsultatii) {
        if (nrConsultatii > 0 && viitoareConsultatii != nullptr) {
            this->nrConsultatii = nrConsultatii;
            if (this->viitoareConsultatii != nullptr) {
                delete[] this->viitoareConsultatii;
            }
            this->viitoareConsultatii = new Consultatie[this->nrConsultatii];
            for (int i = 0; i < this->nrConsultatii; i++) {
                this->viitoareConsultatii[i] = viitoareConsultatii[i];
            }
        }
        else {
            this->nrConsultatii = 0;
            this->viitoareConsultatii = nullptr;
        }
    }
    Consultatie* getViitoareConsultatie() const {
        return this->viitoareConsultatii;
    }

    void setPrenume(const char* prenume) {
        if (this->prenume != nullptr)
        {
            delete[] this->prenume;
        }
        if (verifSiruriCaractere(prenume)) {
            this->prenume = new char[strlen(prenume) + 1];
            strcpy(this->prenume, prenume);
        }
    }
    char* getPrenume() const  {
        return this->prenume;
    }

    void setVarsta(const int varsta) {
        if (varsta >= 0) {
            this->varsta = varsta;
        }
    }
    int getVarsta() const{
        return this->varsta;
    }

    void setAdresa(const char adresa[]) {
        if (strlen(adresa) > 10) {
            strcpy(this->adresa, adresa);
        }
    }

    char* getAdresa() {
        return this->adresa;
    }

    void setEsteAsigurat(const bool rez) {
        this->esteAsigurat = rez;
    }

    bool getEsteAsigurat() const {
        return this->esteAsigurat;
    }

    void setNrPlati(const int nr) {
        if (nr > 0) {
            this->nrPlati = nr;
        }
        else {
            this->nrPlati = 0;
        }
    }
    int getNrPlati() const {
        return this->nrPlati;
    }

    void setIstoricPlati(const float* istoricPlati) {
        if (this->istoricPlati != nullptr) {
            delete[] this->istoricPlati;
        }
        if (this->nrPlati > 0) {
            this->istoricPlati = new float[this->nrPlati];
            for (int i = 0; i < this->nrPlati; i++) {
                if (istoricPlati[i] > 50) {
                    this->istoricPlati[i] = istoricPlati[i];
                }
                else {
                    this->istoricPlati[i] = 50;
                }
            }
        }
        else {
            this->nrPlati = 0;
            this->istoricPlati = nullptr;
        }
    }
    float* getIstoricPlati() const{
        return this->istoricPlati;
    }

    void setNrConsultatii(const int nrConsultatii) {
        if (nrConsultatii > 0) {
            this->nrConsultatii = nrConsultatii;
        }
        else if (nrConsultatii == 0) {
            this->nrConsultatii = 0;
            delete[] this->viitoareConsultatii;
        }
        else {
            cout << "Nr consultatiilor nu este potrivit";
        }
    }
    int getNrConsultatii() const {
        return this->nrConsultatii;
    }

    void setPhoneNumber(const char* phone) {
        if (verifTelefon(phone)) {
            this->phoneNumber = new char[11];
            strcpy(this->phoneNumber, phone);
        }
    }
    char* getPhoneNumber() const {
        return this->phoneNumber;
    }

#pragma endregion

#pragma region adaugaConsultatie
    int adaugaConsultatieStandard(int zi, int luna, int an, int ora) {
        Consultatie c;
        Data d;
        if (d.setData(zi, luna, an) && c.setDataConsultatie(d)) {
            Consultatie* aux;
            aux = new Consultatie[this->nrConsultatii + 1];
            for (int i = 0; i < this->nrConsultatii; i++) {
                aux[i] = this->viitoareConsultatii[i];
            }
            this->nrConsultatii++;
            aux[this->nrConsultatii - 1] = c;
            if (this->viitoareConsultatii != nullptr) {
                delete[] this->viitoareConsultatii;
            }
            this->viitoareConsultatii = new Consultatie[this->nrConsultatii];
            for (int i = 0; i < this->nrConsultatii; i++) {
                this->viitoareConsultatii[i] = aux[i];
            }
            return 1;
        }
        else {
            return 0;
        }
    }
#pragma endregion

#pragma region Operatorul_Plus

    Pacient& operator+(Pacient& p) {
        if (this != &p)
        {
            float* aux;
            int j;
            int ok = 0;
            aux = new float[this->nrPlati + p.nrPlati];
            if (this->istoricPlati != nullptr) {
                for (int i = 0; i < this->nrPlati; i++) {
                    aux[i] = this->istoricPlati[i];
                }
                j = this->nrPlati;
                ok = 1;
                delete[] this->istoricPlati;
            }
            else {
                j = 0;
            }

            if (p.istoricPlati != nullptr) {
                ok = 1;
                for (int i = j; i < (this->nrPlati + p.nrPlati); i++) {
                    aux[i] = p.istoricPlati[i - this->nrPlati];
                }
            }
            if (ok == 0) {
                this->nrPlati = 0;
                this->istoricPlati = nullptr;
            }
            else {
                this->nrPlati = this->nrPlati + p.nrPlati;
                this->istoricPlati = new float[this->nrPlati];
                for (int i = 0; i < this->nrPlati; i++) {
                    this->istoricPlati[i] = aux[i];
                }
            }
            if (p.istoricPlati != nullptr) {
                delete[] p.istoricPlati;
            }
            p.istoricPlati = nullptr;
            p.nrPlati = 0;
        }
        else {
            cout << "Faceti referire la acelasi pacient inregistrat";
        }
        return *this;
    }

#pragma endregion 

#pragma region Operator_incrementare
    Pacient& operator++ () {
        this->varsta++;
        return *this;
    }
#pragma endregion

#pragma region Operator_indexare
    float& operator[] (int index) {
        if (index >= 0 && index < this->nrPlati) {
            return this->istoricPlati[index];
        }
    }
#pragma endregion

#pragma region Operator_negatie
    bool operator!() {
        if (this->varsta > 18) {
            return true;
        }
        return false;
    }
#pragma endregion

#pragma region Operatorul_Cast
    operator float() {
        return this->istoricPlati[this->nrPlati - 1];
    }
#pragma endregion

#pragma region Operatorul_Comparatie
    bool operator < (Pacient& p) {
        float sumaP1 = 0, sumaP2 = 0;
        for (int i = 0; i < this->nrPlati; i++) {
            sumaP1 += this->istoricPlati[i];
        }
        for (int i = 0; i < this->nrPlati; i++) {
            sumaP2 += this->istoricPlati[i];
        }
        sumaP1 = sumaP1 / this->nrPlati;
        sumaP2 = sumaP2 / p.nrPlati;
        if (sumaP1 < sumaP2) {
            return true;
        }
        else {
            return false;
        }
    }

#pragma endregion

#pragma region Operatorul_Egal_Egal

    bool operator == (Pacient& p) {
        float sumaP1 = 0, sumaP2 = 0;
        for (int i = 0; i < this->nrPlati; i++) {
            sumaP1 += this->istoricPlati[i];
        }
        for (int i = 0; i < p.nrPlati; i++) {
            sumaP2 += this->istoricPlati[i];
        }
        sumaP1 = sumaP1 / this->nrPlati;
        sumaP2 = sumaP2 / p.nrPlati;
        if (sumaP1 == sumaP2) {
            return true;
        }
        else {
            return false;
        }
    }
#pragma endregion

#pragma region Afisare
    void afisare() {
        cout << "\n\n\nDate referitoare la pacientul cu id-ul: " << this->id;
        if (this->prenume != nullptr && this->nume != "") {
            cout << endl << "Pacientul are numele: " << this->nume << endl;
            cout << "Pacientul are prenumele: " << this->prenume << endl;
            if (this->phoneNumber != nullptr) {
                cout << "Numarul de telefon al pacientului: " << this->phoneNumber << endl;
            }
            cout << "Pacientul are varsta: " << this->varsta << endl;

            if (strlen(this->adresa) > 10) {
                cout << "Pacientul are urmatoarea adresa: \n" << this->adresa << endl;
            }
            else {
                cout << "Adresa pacientului nu este inregistrata";
            }
            (this->esteAsigurat) ? cout << "Pacientul este asigurat." << endl : cout << "Pacientul nu este asigurat." << endl;
            cout << "Pacientul are programate " << this->nrConsultatii << " consultatii(e)" << endl;

            cout << "Pacientul a fost la urmatorii medici:" << endl;

            if (this->nrPlati == 0) {
                cout << "Pacientul nu a efectuat plati in cadrul centrului medical." << endl;
            }
            else {
                cout << "Pana acum pacientul facut " << this->nrPlati << " plati in cadrul spitalului" << endl;
                cout << "Pana acum pacientul facut " << this->nrPlati << " plati in cadrul spitalului" << endl;
                cout << "\nIata valoarea platilor realizate de pacient: \n \n";
                for (int i = 0; i < this->nrPlati; i++) {
                    cout << "Plata cu numarul " << i + 1 << " a fost in valoare de : " << this->istoricPlati[i] << endl;
                }
            }

            if (this->nrConsultatii != 0) {
                cout << "Consultatiile programate, contin urmatoarele date: \n";
                for (int i = 0; i < this->nrConsultatii; i++) {
                    cout << this->viitoareConsultatii[i];
                }
            }

        }
        else {
            cout << "\nNu avem date referitoare la acest pacient\n";
        }
    }
#pragma endregion

#pragma region Destructor
    ~Pacient() {
        delete[] this->prenume;
        delete[] this->viitoareConsultatii;
        delete[] this->istoricPlati;
        delete[] this->phoneNumber;
    }
#pragma endregion

#pragma region Operator_Egal

    Pacient& operator =(const Pacient& p) {
        if (this != &p) {
            if (this->prenume != nullptr)
            {
                delete[] this->prenume;
            }
            if (this->phoneNumber != nullptr) {
                delete[] this->phoneNumber;
            }
            if (this->istoricPlati != nullptr) {
                delete[] this->istoricPlati;
            }       
            if (this->viitoareConsultatii != nullptr) {
                delete[] this->viitoareConsultatii;
            }

            if (verifSiruriCaractere(p.prenume)) {
                this->prenume = new char[strlen(p.prenume) + 1];
                strcpy(this->prenume, p.prenume);
            }

            if (verifSiruriCaractere(p.nume.c_str())) {
                this->nume = p.nume;
            }

            if (verifTelefon(p.phoneNumber)) {
                this->phoneNumber = new char[11];
                strcpy(this->phoneNumber, p.phoneNumber);
            }

            if (p.nrPlati > 0) {
                this->nrPlati = p.nrPlati;
                this->istoricPlati = new float[this->nrPlati];
                for (int i = 0; i < this->nrPlati; i++) {
                    if (p.istoricPlati[i] > 50) {
                        this->istoricPlati[i] = p.istoricPlati[i];
                    }
                    else {
                        this->istoricPlati[i] = 50;
                    }
                }
            }
            else {
                this->nrPlati = 0;
                this->istoricPlati = nullptr;
            }

            if (p.varsta >= 0) {
                this->varsta = p.varsta;
            }
            else {
                this->varsta = 0;
            }

            if (strlen(p.adresa) > 10) {
                strcpy(this->adresa, p.adresa);
            }
            else {
                strcpy(this->adresa, "");
            }

            this->esteAsigurat = p.esteAsigurat;

            if (p.nrConsultatii > 0) {
                this->nrConsultatii = p.nrConsultatii;
            }
            if (p.viitoareConsultatii != nullptr) {
                this->viitoareConsultatii = new Consultatie[this->nrConsultatii];
                for (int i = 0; i < this->nrConsultatii; i++) {
                    this->viitoareConsultatii[i] = p.viitoareConsultatii[i];
                }
            }
            else {
                this->nrConsultatii = 0;
                this->viitoareConsultatii = nullptr;
            }
        }
        return *this;
    }

#pragma endregion

#pragma region Operator_de_citire  
    friend istream& operator>>(istream& in, Pacient& p) {
        if (p.prenume != nullptr) {
            delete[] p.prenume;
        }
        if (p.istoricPlati != nullptr) {
            delete[] p.istoricPlati;
        }
        if (p.phoneNumber != nullptr) {
            delete[] p.phoneNumber;
        }
        if (p.viitoareConsultatii != nullptr) {
            delete[] p.viitoareConsultatii;
        }
        cout << "\nIntroduceri numele pacientului:\n";
        string nume;
        in >> nume;

        if (verifSiruriCaractere(nume.c_str())) {
            p.nume = nume;
        }
        else {
            p.nume = "";
        }
        char prenume[30];
        cout << "Introduceti prenumele pacientului:\n";
        in >> prenume;
        if (verifSiruriCaractere(prenume)) {
            p.prenume = new char[strlen(prenume) + 1];
            strcpy(p.prenume, prenume);
        }

        char* number;
        number = new char[11];
        cout << "Introduceti numarul de telefon al pacientului (10 cifre):\n";
        in >> number;

        if (verifTelefon(number)) {
            p.phoneNumber = new char[11];
            strcpy(p.phoneNumber, number);
        }
        else {
            p.phoneNumber = nullptr;
        }

        int varsta;
        cout << "Introduceti varsta pacientului:\n";
        in >> varsta;
        if (varsta >= 0) {
            p.varsta = varsta;
        }
        getchar();
        cout << "Introduceti adresa pacientului:\n";
        char adresa[60];
        cin.getline(adresa, strlen(adresa));
        if (strlen(adresa) > 10) {
            strcpy(p.adresa, adresa);
        }
        else {
            strcpy(p.adresa, "");
        }

        cout << "Este pacientul asigurat?(0-false / 1-true)";
        int ok;
        in >> ok;
        if (ok == 1) {
            p.esteAsigurat = true;
        }
        if (ok == 0) {
            p.esteAsigurat = false;
        }
        int nrConsultatii;
        cout << "Introduceti numarul de consulatii:";
        in >> nrConsultatii;

        if (nrConsultatii >= 0) {
            p.nrConsultatii = nrConsultatii;
            Consultatie* cons;
            cout << "Introduceti datele fiecarei consultatii in parte:\n";
            cons = new Consultatie[p.nrConsultatii];
            p.viitoareConsultatii = new Consultatie[p.nrConsultatii];
            for (int i = 0; i < p.nrConsultatii; i++) {
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
                        cout << "Nu ai introdus o data valida. Mai incearca. \n";
                    }
                }
                cout << "Introduceti ora la care va avea loc consultatia " << i + 1 << " :";
                int ora;
                in >> ora;
                c.setOra(ora);
                p.viitoareConsultatii[i] = c;
            }
        }
        else {
            p.nrConsultatii = 0;
            p.viitoareConsultatii = nullptr;
        }

        int nrPlati;
        float* istoricPlati;
        cout << "Introduceti numarul de plati efectuate de catre pacient in cadrul centrului medical:";
        in >> nrPlati;
        if (nrPlati > 0) {
            p.nrPlati = nrPlati;
            cout << "Intoruceti platile aferente fiecarui an: \n";
            istoricPlati = new float[nrPlati];
            for (int i = 0; i < nrPlati; i++) {
                cout << "Plata cu numarul " << i + 1 << " este in valoare de: ";
                in >> istoricPlati[i];
            }
            p.istoricPlati = new float[p.nrPlati];
            p.istoricPlati = verifIstoric<float>(istoricPlati, p.nrPlati, 50);
        }
        else {
            p.nrPlati = 0;
            p.istoricPlati = nullptr;
        }
        return in;
    }
#pragma endregion   

#pragma region Operator_de_afisare
    friend ostream& operator <<(ostream& out, const Pacient& p) {
        out << "\nDate referitoare la pacientul cu id-ul: " << p.id;
        if (p.prenume != nullptr && p.nume != "") {
            out << endl << "Pacientul are numele: " << p.nume << endl;
            out << "Pacientul are prenumele: " << p.prenume << endl;
            if (p.phoneNumber != nullptr) {
                out << "Numarul de telefon al pacientului: " << p.phoneNumber << endl;
            }
            out << "Pacientul are varsta: " << p.varsta << endl;

            if (strlen(p.adresa) > 10) {
                out << "Pacientul are urmatoarea adresa: \n" << p.adresa << endl;
            }
            else {
                out << "Adresa pacientului nu este inregistrata";
            }
            (p.esteAsigurat) ? out << "Pacientul este asigurat." << endl : out << "Pacientul nu este asigurat." << endl;
            out << "Pacientul are programate " << p.nrConsultatii << " consultatii" << endl;
            if (p.nrConsultatii != 0) {
                out << "Consultatiile programate, contin urmatoarele date: \n";
                for (int i = 0; i < p.nrConsultatii; i++) {
                    out << p.viitoareConsultatii[i];
                }
            }
            if (p.nrPlati == 0 || p.istoricPlati == nullptr) {
                out << "Pacientul nu a efectuat plati in cadrul centrului medical." << endl;
            }
            else {
                out << "Pana acum pacientul facut " << p.nrPlati << " plati in cadrul spitalului" << endl;
                out << "\nIata valoarea platilor realizate de pacient: \n \n";
                for (int i = 0; i < p.nrPlati; i++) {
                    out << "Plata cu numarul " << i + 1 << " a fost in valoare de : " << p.istoricPlati[i] << endl;
                }
            }


        }
        else {
            out << "\nNu avem date referitoare la acest pacient\n";
        }
        return out;
    }

#pragma endregion

#pragma region Citire_Fisier
    friend ifstream& operator >>(ifstream& in, Pacient& p) {
        if (p.prenume != nullptr) {
            delete[] p.prenume;
        }
        if (p.istoricPlati != nullptr) {
            delete[] p.istoricPlati;
        }
        if (p.phoneNumber != nullptr) {
            delete[] p.phoneNumber;
        }
        if (p.viitoareConsultatii != nullptr) {
            delete[] p.viitoareConsultatii;
        }
        string nume;
        in >> nume;
        if (verifSiruriCaractere(nume.c_str())) {
            p.nume=nume;
        }
        else {
            p.nume = "";
        }
        char prenume[30];
        in >> prenume;
        if (verifSiruriCaractere(prenume)) {
            p.prenume = new char[strlen(prenume)+1];
            strcpy(p.prenume, prenume);
        }
        else {
            p.prenume = nullptr;

        }
        char* number;
        number = new char[11];
        in >> number;

        if (verifTelefon(number)) {
            p.phoneNumber = new char[11];
            strcpy(p.phoneNumber, number);
        }
        else {
            p.phoneNumber = nullptr;
        }

        int varsta;
        in >> varsta;
        if (varsta >= 0) {
            p.varsta = varsta;
        }
        string line;
        getline(in,line);
        getline(in, line);
        if (strlen(line.c_str()) > 10) {
            strcpy(p.adresa, line.c_str());
        }
        else {
            strcpy(p.adresa, "");
        }
        char ok[30];
        in >> p.esteAsigurat;

        int nrConsultatii;
        in >> nrConsultatii;
        if (nrConsultatii > 0) {
            p.nrConsultatii = nrConsultatii;
        }
        p.viitoareConsultatii = new Consultatie[p.nrConsultatii];
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
            p.viitoareConsultatii[i].setDataConsultatie(d);
            p.viitoareConsultatii[i].setOra(ora);
        }

        int nrPlati;
        float* istoricPlati;
        in >> nrPlati;
        if (nrPlati > 0) {
            p.nrPlati = nrPlati;
            istoricPlati = new float[p.nrPlati];
            for (int i = 0; i < nrPlati; i++) {
                in >> istoricPlati[i];
            }
            p.istoricPlati = new float[p.nrPlati]; 
            p.istoricPlati = verifIstoric<float>(istoricPlati, p.nrPlati, 50);
        }
        else {
            p.nrPlati = 0;
            p.istoricPlati = nullptr;
        }
        return in;
    }
#pragma endregion

#pragma region Scriere_in_fisier
    friend ofstream& operator <<(ofstream& out, const Pacient& p) {
        if (p.prenume != nullptr && p.nume != "") {
            out << p.nume << endl;
            out << p.prenume << endl;
            if (p.phoneNumber != nullptr) {
                out << p.phoneNumber << endl;
            }
            out << p.varsta << endl;

            if (strlen(p.adresa) > 10) {
                out << p.adresa << endl;
            }
            out << p.esteAsigurat << endl;
            out << p.nrConsultatii << endl;
            if (p.nrConsultatii != 0) {
                for (int i = 0; i < p.nrConsultatii; i++) {
                    out << p.viitoareConsultatii[i].getZi()<<" ";
                    out << p.viitoareConsultatii[i].getLuna()<<" ";
                    out << p.viitoareConsultatii[i].getAn()<<" ";
                    out << p.viitoareConsultatii[i].getOra()<<endl;
                }
            }
  
            if (!(p.nrPlati == 0 || p.istoricPlati == nullptr)) {
                out << p.nrPlati << endl;
                for (int i = 0; i < p.nrPlati; i++) {
                    out << p.istoricPlati[i] << endl;
                }
            }


        }
        return out;
    }
#pragma endregion

};


int Pacient::contor = 1;
#pragma endregion
