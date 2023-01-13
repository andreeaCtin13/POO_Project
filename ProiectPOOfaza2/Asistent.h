#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <string.h>
#include <fstream>
#include "Functii.h"
#include "Angajat.h"
#include "Medic.h"
#include "Persoana.h"
#include <ctime>

//TO DO : SA PUI LA STAGIAR, NU LA REZIDENT ASTA CU MOSTENIREA IN ROMB


class Asistent : virtual public Angajat {
    int nrMedici=0;
    Medic* mediciAsociati = nullptr;
    int orePregatireLunara = 0;

public:

#pragma region Constructor_fara_parametrii
    Asistent() :Angajat() {
        this->orePregatireLunara = 0;
        this->nrMedici = 0;
    }
#pragma endregion

#pragma region Constructor_cu_cativa_paramterii
    Asistent(const char* nume, const string prenume, const float salariu, const int varsta, int orePregatireLunara) :Angajat(nume, prenume, salariu, varsta) {
        if (orePregatireLunara > 0) {
            this->orePregatireLunara = orePregatireLunara;
        }
    }
#pragma endregion

#pragma region Constructor_cu_toti_paramterii
    Asistent(const char* nume, const string prenume, float salariu, int varsta, int orePregatireLunara, const int vechime, const int istoricNrConsultatiiLunare[], const float istoricVenituriLunare[], const int istoricOreLucrate[], int nrMedici, Medic *mediciAsociati) :Angajat(nume, prenume, salariu, varsta, vechime, istoricNrConsultatiiLunare, istoricVenituriLunare, istoricOreLucrate) {
        if (nrMedici > 0) {
            this->nrMedici = nrMedici;
            this->mediciAsociati = new Medic[this->nrMedici];
            for (int i = 0; i < this->nrMedici; i++) {
                this->mediciAsociati[i] = mediciAsociati[i];
            }
        }
        if (orePregatireLunara > 0) {
            this->orePregatireLunara = orePregatireLunara;
        }

    }
#pragma endregion

#pragma region Constructor_de_copiere
    Asistent(const Asistent& m) :Angajat(m) {
        if (m.nrMedici > 0) {
            this->nrMedici = m.nrMedici;
            this->mediciAsociati = new Medic[this->nrMedici];
            for (int i = 0; i < this->nrMedici; i++) {
                this->mediciAsociati[i] = m.mediciAsociati[i];
            }
        }
        if (orePregatireLunara > 0) {
            this->orePregatireLunara = orePregatireLunara;
        }
    }
#pragma endregion

#pragma region MetodaMoare
    void Persoana::Moare() {
        this->setPrenume("Asistent");
        this->setNume("Decedat");
        time_t theTime = time(NULL);
        struct tm* aTime = localtime(&theTime);

        int ziuaCurenta = aTime->tm_mday;
        int lunaCurenta = aTime->tm_mon + 1;
        int anulCurent = aTime->tm_year + 1900;
        cout << "Asistetul a decedat la data de " << ziuaCurenta << "/" << lunaCurenta << "/" << anulCurent << endl;
    }
#pragma endregion

#pragma region SchimbaIdentitatea
    void Persoana::SchimbaIdentitatea() {
        cout << "Introduceti noul nume al asistentului:\n";
        string nume, prenume;
        cin >> nume;
        cout << "Introduceti noul prenume al asistentului:\n";
        cin >> prenume;
        this->setNume(nume.c_str());
        this->setPrenume(prenume);
        cout << "Introduceti noua varsta a asistentului:\n";
        int varsta;
        cin >> varsta;
        this->setVarsta(varsta);
        cout << "\nSchimbarea de identitate a avut loc cu succes\n";
    }
#pragma region

#pragma region MetodaRaport
    virtual void creareRaport(ofstream& out) {
        out << "\n----------------------------------------------------------\n";
        out << "\n\n\nDate referitoare la Asistentul cu id-ul: " << this->id;
        if (this->prenume != "" && this->nume != nullptr) {
            out << endl << "Numele Asistentului: " << this->nume << endl;
            out << "Prenumele Asistentului: " << this->prenume << endl;
            if (this->vechimeCentru == 0) {
                out << "Asistentul abia s-a transferat in cadrul acestui centru Asistental";
            }
            else {
                out << "Asistentul are o experienta de " << this->vechimeCentru << "luni in cadrul acestui centru Asistental." << endl;
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
            out << "Numarul de ore de pregatire lunara ale asistentului sunt: " << this->orePregatireLunara << endl;
            if (this->nrMedici) {
                out << "Medicii asociati asistentului sunt:" << endl;
                for (int i = 0; i < this->nrMedici; i++) {
                     out << "Numele medicului este: "<<this->mediciAsociati->getNume()<<" "<<this->mediciAsociati->getPrenume()<<" specializat ca "<<this->mediciAsociati->getSpecializare() << "\n";
                }
            }
        }
        else {
            out << "\nNu avem date referitoare la acest Asistent\n";
        }
    }
#pragma endregion

#pragma region WriteBinary
    void writeBinary(fstream &f) {
        Angajat::writeBinary(f);
        f.write((char*)&this->orePregatireLunara, sizeof(int));
        f.write((char*)&this->nrMedici, sizeof(int));
        for (int i = 0; i < this->nrMedici; i++) {
            this->mediciAsociati[i].writeBinary(f);
        }
    }
#pragma endregion

#pragma region citireCSV

    void citireCSV(ifstream& f, char delim[]) {
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
        this->setOrePregatireLunara(atoi(token));

        token = strtok(NULL, delim);
        this->setVechime(0);
        this->setNrMedici(0);
    }

#pragma endregion

#pragma region AddMedic
    void addMedic(Medic m) {
        Medic* copie = new Medic[this->nrMedici+1];
        for (int i = 0; i < this->nrMedici; i++) {
            copie[i] = this->mediciAsociati[i];
        }
        copie[this->nrMedici] = m;
        this->nrMedici++;
        if (this->mediciAsociati != nullptr) {
            delete[] this->mediciAsociati;
        }
        this->mediciAsociati = new Medic[this->nrMedici];
        for (int i = 0; i < this->nrMedici; i++) {
            this->mediciAsociati[i] = copie[i];
        }
    }
#pragma endregion

#pragma region Metode_Accesor
    void setOrePregatireLunara(int orePregatireLunara) {
        //numarul minim de ore de pregatire lunara este de 10 ore
        if (orePregatireLunara > 10) {
            this->orePregatireLunara = orePregatireLunara;
        }
        else {
            this->orePregatireLunara = 10;
        }
    }
    
    int getOrePregatireLunara() const {
        return this->orePregatireLunara;
    } 
    
    void setMedicAsociat(const Medic* mediciAsociati, const int nrMedici) {

        if (mediciAsociati != nullptr) {
            if (this->mediciAsociati != nullptr) {
                delete[] this->mediciAsociati;
            }
            if (nrMedici > 0) {
                this->nrMedici = nrMedici;
            }
            for (int i = 0; i < this->nrMedici; i++) {
                this->mediciAsociati[i] = mediciAsociati[i];
            }
        }
    }
    
    Medic* getMedicAsociat() {
        return this->mediciAsociati;
    }
    
    void setNrMedici(int nrMedici) {
        if (nrMedici > 0) {
            this->nrMedici = nrMedici;
        }
    }

    int getNrMedici() const {
        return this->nrMedici;
    }

#pragma endregion

#pragma region Operator_negatie
    bool operator!() {
        if (this->orePregatireLunara < 30) {
            return true;
        }
        return false;
    }
#pragma endregion

#pragma region Operatorul_egal
    Asistent& operator = (const Asistent& m) {
        if (this != &m) {
            Angajat::operator=(m);
            if (m.orePregatireLunara > 10) {
                this->orePregatireLunara = m.orePregatireLunara;
            }
            else {
                this->orePregatireLunara = 10;
            }

            if (m.nrMedici > 0) {
                this->nrMedici = m.nrMedici;
                if (m.mediciAsociati != nullptr) {
                    this->mediciAsociati = new Medic[this->nrMedici];
                    for (int i = 0; i < this->nrMedici; i++) {
                        this->mediciAsociati[i] = m.mediciAsociati[i];
                    }
                }
            }
        }
        return *this;
    }
#pragma endregion

#pragma region Operator_Indexare
    Medic& operator[] (int index) {
        if (index >= 0 && index < this->vechimeCentru) {
            return this->mediciAsociati[index];
        }
    }

#pragma endregion 

#pragma region Operatorul_de_citire
    friend istream& operator >> (istream& in, Asistent& m) {
        cout << "\nIntroduceti prenumele Asistentului:\n";
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
        cout << "Intorduceti numele Asistentului:\n";
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
        cout << "Introduceti vechimea Asistentului in cadrul acestui centru Asistental:\n";
        in >> vechime;
        if (vechime > 0) {
            m.vechimeCentru = vechime;
        }

        int varsta;
        cout << "Introduceti varsta Asistentului:\n";
        in >> varsta;
        if (varsta > 0) {
            m.varsta = varsta;
        }
        else {
            m.varsta = 0;
        }

        cout << "Introduceti numarul consultatiilor sustinute de acest Asistent pe parcursul acestui an:\n";
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
            aux2 = verifIstoric<float>(istoricVenituriLunare, m.vechimeCentru, Asistent::MINIM_SALARIU);
            for (int i = 0; i < 12; i++) {
                m.istoricVenituriLunare[i] = aux2[i];
            }
            delete[] aux2;
        }

        float salariu;
        cout << "Introduceti salariul curent: \n";
        in >> salariu;

        if (salariu > Asistent::MINIM_SALARIU) {
            m.salariu = salariu;
        }
        else {
            m.salariu = Asistent::MINIM_SALARIU;
        }

        int istoricOreLucrate[12];
        cout << "Introduceti orele lucrate in lunile anului acesta de catre Asistent: \n";
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


        int nrMedici;
        cout << "Introduceti numarul de medici asociati asistentului: ";
        in >> nrMedici;
        if (nrMedici > 0) {
            m.nrMedici = nrMedici;
            if (m.mediciAsociati != nullptr) {
                delete[] m.mediciAsociati;
            }
            m.mediciAsociati = new Medic[m.nrMedici];
            for (int i = 0; i < m.nrMedici; i++) {
                cout << "Introduceti datele referitoare la medicul " << i + 1 << endl << endl;
                Medic aux;
                cin >> aux;
                m.mediciAsociati[i] = aux;

            }
        }

        cout << "Introduceti numarul de ore de pregatire lunara: ";
        int orePregatireLunara;
        in >> orePregatireLunara;
        if (orePregatireLunara > 10) {
            m.orePregatireLunara = orePregatireLunara;
        }
        else {
            m.orePregatireLunara = 10;
        }
        return in;
    }

#pragma endregion

#pragma region Operator_Scriere
    friend ostream& operator <<(ostream& out, const Asistent& m) {
        out << "\n\n\nDate referitoare la Asistentul cu id-ul: " << m.id << endl;
        if (m.prenume != "" && m.nume != nullptr) {
            if (m.prenume != "" && m.nume != nullptr) {
                out << endl << "Numele Asistentului: " << m.nume << endl;
                out << "Prenumele Asistentului: " << m.prenume << endl;
                if (m.vechimeCentru == 0) {
                    out << "Asistentul abia s-a transferat in cadrul acestui centru medical";
                }
                else {
                    out << "Asistentul are o experienta de " << m.vechimeCentru << "luni in cadrul acestui centru medical." << endl;
                }
                out << "Asistentul are un salariu in valoare de " << m.salariu << " RON" << endl;
                out << "Varsta angajatului este de : " << m.varsta << " ani" << endl;
                if (m.vechimeCentru > 0) {
                    out << "Numarul de consultatii de anul acesta sustinute de catre Asistent este urmatorul:\n";

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
                out << "Numarul de ore de pregatire lunara ale asistentului : " << m.orePregatireLunara << endl;
                out << "Numarul de medici asociati acestui asistent este de: " << m.nrMedici << endl;
                if (m.nrMedici != 0 && m.mediciAsociati != nullptr) {
                    out << "Medicii asociati: \n" << endl;
                    for (int i = 0; i < m.nrMedici; i++) {
                        out << m.mediciAsociati[i].getPrenume() << " " << m.mediciAsociati[i].getNume() << " cu specializarea de " << m.mediciAsociati[i].getSpecializare()<<endl;
                    }
                }
            }
            else {
                out << "\nNu avem date referitoare la acest Asistent\n";
            }
        }
        else {
            out << "\nNu avem date referitoare la acest Asistent\n";
        }
        return out;

    }
#pragma endregion

#pragma region Citire_Fisier
    friend ifstream& operator>>(ifstream& in, Asistent& m) {
        string prenume;
        in >> prenume;
        int ok = 1;
        if (verifSiruriCaractere(prenume.c_str())) {
            m.prenume = prenume;
        }
        else {
            ok = 0;
            m.prenume = "";
        }

        if (m.nume != nullptr)
        {
            delete[] m.nume;
        }
        char nume[30];
        in >> nume;

        if (verifSiruriCaractere(nume)) {
            m.nume = new char[strlen(nume) + 1];
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
          

            int nrMedici;
            in >> nrMedici;
            if (nrMedici > 0) {
                m.nrMedici = nrMedici;
                if (m.mediciAsociati != nullptr) {
                    delete[] m.mediciAsociati;
                }
                m.mediciAsociati = new Medic[m.nrMedici];
                for (int i = 0; i < m.nrMedici; i++) {
                    Medic aux;
                    in >> aux;
                    m.mediciAsociati[i] = aux;

                }
            }

            int orePregatireLunara;
            in >> orePregatireLunara;
            if (orePregatireLunara > 10) {
                m.orePregatireLunara = orePregatireLunara;
            }
            else {
                m.orePregatireLunara = 10;
            }

        }
        return in;
    }
#pragma endregion

#pragma region Scriere_Fisier
    friend ofstream& operator <<(ofstream& out, const Asistent& m) {
        if (m.prenume != "" && m.nume != nullptr) {
            out << m.prenume << endl;
            out << m.nume << endl;
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
            out <<  m.nrMedici << endl;
            if (m.nrMedici != 0 && m.mediciAsociati != nullptr) {
                for (int i = 0; i < m.nrMedici; i++) {
                    out << m.mediciAsociati[i];
                }
            }
            out << m.orePregatireLunara << endl;

            out << endl;
        }
        return out;
    }

#pragma endregion

#pragma region Destructor
    ~Asistent() {
    }
#pragma endregion

};

