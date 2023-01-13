#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <fstream>
#include <ctime>

#include "Functii.h"
#include "Angajat.h"
using namespace std;

class Medic: virtual public Angajat {
    static string* Listaspecializari;
    string specializare = "";

public:

#pragma region Constructor_fara_parametrii
    Medic() :Angajat() {
        this->specializare = "";
        Medic::setSpecializari();
    }
#pragma endregion

#pragma region Constructor_cu_cativa_paramterii
    Medic(const char* nume, const string prenume, const float salariu, const int varsta, const string specializare) :Angajat(nume, prenume, salariu, varsta){
        Medic::setSpecializari();
      
        if (verifSpecializare(specializare, Medic::Listaspecializari)) {
            this->specializare = specializare;
        }
        else {
            this->specializare = Medic::Listaspecializari[7];
        }
    }
#pragma endregion

#pragma region Constructor_cu_toti_paramterii
    Medic(const char* nume, const string prenume, float salariu, int varsta, const string specializare, const int vechime, const int istoricNrConsultatiiLunare[], const float istoricVenituriLunare[], const int istoricOreLucrate[]) :Angajat(nume, prenume, salariu, varsta, vechime, istoricNrConsultatiiLunare, istoricVenituriLunare, istoricOreLucrate) {
        Medic::setSpecializari();

        if (verifSpecializare(specializare, Medic::Listaspecializari)) {
            this->specializare = specializare;
        }
        else {
            this->specializare = Medic::Listaspecializari[7];
        }
    }
#pragma endregion

#pragma region Constructor_de_copiere
    Medic(const Medic& m):Angajat(m) {
        if (verifSpecializare(m.specializare, Medic::Listaspecializari)) {
            this->specializare = m.specializare;
        }
        else {
            this->specializare = Medic::Listaspecializari[7];
        }
    }
#pragma endregion

#pragma region MetodaRaport
    void creareRaport(ofstream& out) {
        out << "\n-----------------------------------------------------------\n";
        out << "\n\n\nDate referitoare la medicul cu id-ul: " << this->id;
        if (this->prenume != "" && this->nume != nullptr) {
            out << endl << "Numele medicului: " << this->nume << endl;
            out << "Prenumele medicului: " << this->prenume << endl;
            out << "Specializarea medicului este: " << this->specializare << endl;
            if (this->vechimeCentru == 0) {
                out << "Medicul abia s-a transferat in cadrul acestui centru medical";
            }
            else {
                out << "Medicul are o experienta de " << this->vechimeCentru << "luni in cadrul acestui centru medical." << endl;
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
            out << "\nNu avem date referitoare la acest medic\n";
        }
    }
#pragma endregion

#pragma region WriteBinary
    void writeBinary(fstream &f) {
        Angajat::writeBinary(f);
        f.write((char*)&this->specializare, sizeof(string));
    }
#pragma endregion

#pragma region CitireCSV

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
        this->setSpecializare(token);

        token = strtok(NULL, delim);
        this->setVechime(0);
    }

#pragma endregion

#pragma region MetodaMoare
    void Persoana::Moare() {
        this->setPrenume("Medic");
        this->setNume("Decedat");
        time_t theTime = time(NULL);
        struct tm* aTime = localtime(&theTime);

        int ziuaCurenta = aTime->tm_mday;
        int lunaCurenta = aTime->tm_mon + 1;
        int anulCurent = aTime->tm_year + 1900;
        cout << "Medicul a decedat la data de " << ziuaCurenta << "/" << lunaCurenta << "/" << anulCurent << endl;
    }
#pragma endregion

#pragma region SchimbaIdentitatea
    void Persoana::SchimbaIdentitatea() {
        cout << "Introduceti noul nume al medicului:\n";
        string nume, prenume;
        cin >> nume;
        cout << "Introduceti noul prenume al medicului:\n";
        cin >> prenume;
        this->setNume(nume.c_str());
        this->setPrenume(prenume);
        cout << "Introduceti noua varsta a medicului:\n";
        int varsta;
        cin >> varsta;
        this->setVarsta(varsta);
        cout << "\nSchimbarea de identitate a avut loc cu succes\n";
    }
#pragma region

#pragma region functie_specializari
    static void setSpecializari() {
        Medic::Listaspecializari = new string[8];
        Medic::Listaspecializari[0] = "pediatru";
        Medic::Listaspecializari[1] = "cardiolog";
        Medic::Listaspecializari[2] = "oftalmolog";
        Medic::Listaspecializari[3] = "chirurg";
        Medic::Listaspecializari[4] = "nefrolog";
        Medic::Listaspecializari[5] = "urolog";
        Medic::Listaspecializari[6] = "psihiatru";
        Medic::Listaspecializari[7] = "medic generalist";
    }
#pragma endregion

#pragma region Metode_Accesor
  
    int setSpecializare(const string specializare) {
        if (verifSpecializare(specializare, Medic::Listaspecializari)) {
            this->specializare = specializare;
            return 1;
        }
        else {
            return 0;
        }
    }

    string getSpecializare() const {
        return this->specializare;
    }

#pragma endregion

#pragma region Operator_negatie
    bool operator!() {
        if (this->specializare != "medic generalist") {
            return true;
        }
        return false;
    }
#pragma endregion

#pragma region Operatorul_egal
    Medic& operator = (const Medic& m) {
        if (this != &m) {
            Angajat::operator=(m);
            if (verifSpecializare(m.specializare, Medic::Listaspecializari)) {
                this->specializare = m.specializare;
            }
            else {
                this->specializare = Medic::Listaspecializari[7];
            }
        }
        return *this;
    }
#pragma endregion

#pragma region Operator_Indexare
    int operator[] (const char *index) {
        if (index!=nullptr) {
            for (int i = 0; i < 8; i++) {
                if (strcmp(Medic::Listaspecializari[i].c_str(), index) == 0) {
                    return i;
                }
            }
        }
        return -1;
    }

#pragma endregion 

#pragma region Operatorul_de_citire
    friend istream& operator >> (istream& in, Medic& m) {
        cout << "\nIntroduceti prenumele medicului:\n";
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
        cout << "Intorduceti numele medicului:\n";
        char nume[30];
        in >> nume;
        if (verifSiruriCaractere(nume)) {
            m.nume = new char[strlen(nume) + 1];
            strcpy(m.nume, nume);
        }
        else {
            m.nume = nullptr;
        }

        int ok = 0;
        char specializare[70];
        cout << "Introduceti specializarea medicului:\n";
        in.get();
        in.getline(specializare, 70);

        if (verifSpecializare(specializare, Medic::Listaspecializari)) {
            m.specializare = specializare;
        }
        else {
            m.specializare = Medic::Listaspecializari[7];
        }

        int vechime;
        cout << "Introduceti vechimea medicului in cadrul acestui centru medical:\n";
        in >> vechime;
        if (vechime > 0) {
            m.vechimeCentru = vechime;
        }

        int varsta;
        cout << "Introduceti varsta medicului:\n";
        in >> varsta;
        if (varsta > 0) {
            m.varsta = varsta;
        }
        else {
            m.varsta = 0;
        }

        cout << "Introduceti numarul consultatiilor sustinute de acest medic pe parcursul acestui an:\n";
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
            aux2 = verifIstoric<float>(istoricVenituriLunare, m.vechimeCentru, Medic::MINIM_SALARIU);
            for (int i = 0; i < 12; i++) {
                m.istoricVenituriLunare[i] = aux2[i];
            }
            delete[] aux2;
        }

        float salariu;
        cout << "Introduceti salariul curent: \n";
        in >> salariu;

        if (salariu > Medic::MINIM_SALARIU) {
            m.salariu = salariu;
        }
        else {
            m.salariu = Medic::MINIM_SALARIU;
        }

        int istoricOreLucrate[12];
        cout << "Introduceti orele lucrate in lunile anului acesta de catre medic: \n";
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
    friend ostream& operator <<(ostream& out, const Medic& m) {
        if (m.prenume != "" && m.nume != nullptr) {
            out << "\n\n\nDate referitoare la medicul cu id-ul: " << m.id<<endl;
            if (m.prenume != "" && m.nume != nullptr) {
                out << endl << "Numele medicului: " << m.nume << endl;
                out << "Prenumele medicului: " << m.prenume << endl;
                if (m.vechimeCentru == 0) {
                    out << "Medicul abia s-a transferat in cadrul acestui centru medical";
                }
                else {
                    out << "Medicul are o experienta de " << m.vechimeCentru << "luni in cadrul acestui centru medical." << endl;
                }
                out << "Medicul are un salariu in valoare de " << m.salariu << " RON" << endl;
                out << "Varsta angajatului este de : " << m.varsta << " ani" << endl;
                if (m.vechimeCentru > 0) {
                    out << "Numarul de consultatii de anul acesta sustinute de catre medic este urmatorul:\n";

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
                out << "Specializarea medicului este " << m.specializare << endl;
            }
            else {
                out << "\nNu avem date referitoare la acest medic\n";
            }
        }
        return out;

    }
#pragma endregion

#pragma region Citire_Fisier
    friend ifstream& operator>>(ifstream& in, Medic& m) {
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
            char specializare[30];
            int ok = 0;
            in.get();
            in.getline(specializare, 100);
            for (int i = 0; i < 8; i++) {
                if (strcmp(specializare, Medic::Listaspecializari[i].c_str()) == 0) {
                    ok = 1;
                }
            }
            if (ok == 1) {
                m.specializare = specializare;
            }
            else {
                m.specializare = Medic::Listaspecializari[7];
            }
            float salariu;
            in >> salariu;
            if (salariu > Medic::MINIM_SALARIU) {
                m.salariu = salariu;
            }
            else {
                m.salariu = Medic::MINIM_SALARIU;
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

            if (m.vechimeCentru > 0) {
                int* aux3 = new int[12];
                aux3 = verifIstoric<int>(istoricOreLucrate, m.vechimeCentru, 6);
                for (int i = 0; i < 12; i++) {
                    m.istoricOreLucrate[i] = aux3[i];
                }
                delete[]aux3;
            }
            
        }
        return in;
    }
#pragma endregion

#pragma region Scriere_Fisier
    friend ofstream& operator <<(ofstream& out, const Medic& m) {
        if (m.prenume != "" && m.nume != nullptr) {
            out << m.prenume << endl;
            out << m.nume << endl;
            out << m.specializare << endl;
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
    ~Medic() {
    }
#pragma endregion

};

string* Medic::Listaspecializari = nullptr;
