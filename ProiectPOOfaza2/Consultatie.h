#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <string.h>
#include <fstream>
#include <time.h>
#include "Functii.h"
#include "Medic.h"
#include "Data.h"

#pragma region Clasa_Consultatie
class Consultatie {
    const int id;
    static int contor;
    int ora = 0;
    float pret = 50;
    Data data;
    Medic medic;
public:

#pragma region Constructor_fara_parametrii
    Consultatie() :id(contor++) {
        this->ora = 0;
        this->pret = 50;
    }
#pragma endregion

#pragma region Constructor_cu_cativa_parametrii
    Consultatie( const int ora, const int zi, const int luna, const int an) :id(contor++) {
        this->data.setData(zi, luna, an);
        if (ora >= 1 && ora <= 24) {
            this->ora = ora;
        }
    }
#pragma endregion

#pragma region Constructor_cu_toti_parametrii
    Consultatie( const int ora, const float pret, const int zi, const int luna, const int an, const Medic medic) :id(contor++) {
        this->data.setData(zi, luna, an);
        if (ora >= 1 && ora <= 24) {
            this->ora = ora;
        }
        if (pret > 50) {
            this->pret = pret;
        }
        this->medic = medic;
    }
#pragma endregion

#pragma region Constructor_copiere
    Consultatie(const Consultatie& c) :Consultatie() {
        this->data.setData(c.data.getZi(), c.data.getLuna(), c.data.getAn());
        if (ora >= 1 && ora <= 24) {
            this->ora = c.ora;
        }
        if (c.pret > 50) {
            this->pret = c.pret;
        }
    }

#pragma endregion

#pragma region MetodaRaport
    void creareRaport(ofstream& out) {
        out << "\n---------------------------------------------------------------------\n";
        out << "\n\nDate referitoare la consultatia cu id-ul: " << this->id<<endl;
        out << "Consultatia va avea loc in data de: " << this->data.getZi() << "/" << this->data.getLuna() << "/" << this->data.getAn() << endl;
        out << "Consultatia va avea loc la ora: " << this->ora << endl;
        out << "Consultatia va avea pretul de: " << this->pret << endl;
        if (this->medic.getNume() != nullptr && this->medic.getPrenume() != "") {
            out << "Numele medicului ce sustine consultatia: " << this->medic.getNume() << " " << this->medic.getPrenume() << endl;
        }
        else {
            out << "Nu exista un medic asignat consultatiei in momentul de fata" << endl;
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
        int zi = atoi(token);
        token = strtok(NULL, delim);
        int luna = atoi(token);
        token = strtok(NULL, delim);
        int an = atoi(token);
        token = strtok(NULL, delim);
        int ora = atoi(token);
        token = strtok(NULL, delim);
        float pret = atof(token);
        token = strtok(NULL, delim);
        Data d(zi, luna, an);
        this->setDataConsultatie(d);
        this->setOra(ora);
        this->setPret(pret);
    }

#pragma endregion

#pragma region ScriereInBinar

    void writeBinary(fstream &f) {     
        this->data.writeBinary(f);
        f.write((char*)&this->ora, sizeof(int));
        f.write((char*)&this->pret, sizeof(int));
    }

#pragma endregion

#pragma region acceseazaDateMedic
    void acceseazaDateMedic() {
        cout << this->medic;
    }
#pragma endregion

#pragma region schimbaMedicul
    void schimbaMedicul(Medic m) {
        this->medic = m;
    }
#pragma endregion

#pragma region Metode_Accesor

    bool setDataConsultatie(const Data data) {

        int zi = data.getZi();
        int luna = data.getLuna();
        int an = data.getAn();

        time_t theTime = time(NULL);
        struct tm* aTime = localtime(&theTime);

        int ziuaCurenta = aTime->tm_mday;
        int lunaCurenta = aTime->tm_mon + 1;
        int anulCurent = aTime->tm_year + 1900;
        if (anulCurent < an) {
            this->data.setZi(zi);
            this->data.setLuna(luna);
            this->data.setAn(an);
            return true;
        }
        else {
            if (anulCurent == an) {
                if (luna > lunaCurenta) {
                    this->data.setZi(zi);
                    this->data.setLuna(luna);
                    this->data.setAn(an);
                    return true;
                }
                else {
                    if (luna == lunaCurenta) {
                        if (zi > ziuaCurenta) {
                            this->data.setZi(zi);
                            this->data.setLuna(luna);
                            this->data.setAn(an);
                            return true;
                        }
                        else {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                }
            }
            else {
                return false;
            }
        }
    }

    Data getData() const {
        return this->data;
    }

    int getZi() const {
        return this->data.getZi();
    }

    int getLuna()const {
        return this->data.getLuna();
    }

    int getAn()const {
        return this->data.getAn();
    }

    bool setOra(const int ora) {
        if (ora >= 1 && ora <= 24) {
            this->ora = ora;
            return true;
        }
        else {
            return false;
        }
    }

    int getOra() const {
        return this->ora;
    }

    void setPret(const float pret) {
        if (pret > 50) {
            this->pret = pret;
        }
        else {
            this->pret = 50;
        }
    }

    float getPret() const {
        return this->pret;
    }

    void setMedic(const Medic m) {
        this->medic = m;
    }

    Medic getMedic() const {
        return this->medic;
    }

#pragma endregion

#pragma region Operator_negatie
    //vreau sa vad daca consultatia va avea loc pe tura de noapte sau nu
    bool operator!() {
        if (this->ora > 20) {
            return true;
        }
        return false;
    }
#pragma endregion

#pragma region Operatorul_de_incrementare
    Consultatie& operator++ () {
        if (this->ora < 24) {
            this->ora++;
        }
        return *this;
    }
#pragma endregion

#pragma region Operatorul_Cast
    operator float() {
        return this->pret;
    }
#pragma endregion

#pragma region Operatorul_Comparatie
    bool operator < (Consultatie& c) {
        if (this->pret < c.pret) {
            return true;
        }
        else {
            return false;
        }
    }
#pragma endregion

#pragma region Operatorul_Plus
    Consultatie& operator+(const Consultatie& c) {
        if (this != &c)
        {
            this->pret = this->pret + c.pret;
        }
        return *this;
    }
#pragma endregion

#pragma region Operatorul_Egal_Egal
    bool operator == (Consultatie& c) {
        if (this->pret == c.pret) {
            return true;
        }
        else {
            return false;
        }
    }
#pragma endregion

#pragma region Operatorul_Egal
    Consultatie& operator =(Consultatie& c) {
        if (this != &c) {
            int zi = c.data.getZi();
            int luna = c.data.getLuna();
            int an = c.data.getAn();
            this->data.setData(zi, luna, an);
            if (c.ora >= 1 && c.ora <= 24) {
                this->ora = c.ora;
            }
            if (pret > 50) {
                this->pret = c.pret;
            }
            if (c.medic.getPrenume() != "" && c.medic.getNume() != nullptr) {
                this->medic.setPrenume(c.medic.getPrenume());
                this->medic.setNume(c.medic.getNume());
            }
        }
        return *this;
    }
#pragma endregion

#pragma region Operator_Scriere
    friend ostream& operator <<(ostream& out, const Consultatie& c) {
        out << "\n\n\nDate referitoare la consultatia cu id-ul: " << c.id<<endl;
        
            out << "Consultatia va avea loc in data de: " << c.data.getZi() << "/" << c.data.getLuna() << "/" << c.data.getAn() << endl;
            out << "Consultatia va avea loc la ora: " << c.ora << endl;
            out << "Consultatia va avea pretul de: " << c.pret << endl;

            if (c.medic.getNume() != nullptr && c.medic.getPrenume() != "") {
                out << "Numele medicului ce sustine consultatia: " << c.medic.getNume() << " " << c.medic.getPrenume() << endl;
            }
            else {
                out << "Nu exista un medic asignat consultatiei in momentul de fata" << endl;
            }
        return out;
    }

#pragma endregion

#pragma region Operator_citire
    friend istream& operator>>(istream& in, Consultatie& c) {
        int zi;
        int luna;
        int an;
        int ok = 0;
        while (ok == 0) {
            cout << "Introduceti anul in care va avea loc consultatia: \n";
            in >> an;
            cout << "Introduceti luna in care va avea loc consultatia: \n";
            in >> luna;
            cout << "Introduceti ziua in care va avea loc consultatia: \n";
            in >> zi;
            Data aux;
            aux.setData(zi, luna, an);
            if (c.setDataConsultatie(aux) == true) {
                ok = 1;
                c.data = aux;
            }
            else {
                cout << "Nu se poate programa o consultatie in data transmisa. Incercati din nou:\n";
            }
        }

        cout << "Introduceti ora la care va avea loc consultatia (Consultatia poate avea loc doar la ore fixe. ex: 9):\n";
        int ora;
        in >> ora;
        ok = 0;
        while (ok == 0) {
            if (ora >= 1 && ora <= 24) {
                c.ora = ora;
                ok = 1;
            }
            else {
                cout << "Ora nu e corespunzatoare, mai incercati odata: \n";
                in >> ora;
            }
        }
        ok = 0;
        float pret;
        cout << "Introduceti pretul consultatiei:\n";
        in >> pret;
        while (ok == 0) {
            if (pret > 50) {
                c.pret = pret;
                ok = 1;
            }
            else {
                cout << "Nu se trezeste doctorul din pat pentru atata lucru, introduceti alt pret: \n";
                in >> pret;
            }
        }
        in >> c.medic;
        return in;
    }

#pragma endregion

#pragma region CitireFisier
    friend ifstream& operator>>(ifstream& in, Consultatie& c) {
        int zi;
        int luna;
        int an;
        int ok = 0;
        in >> zi;
        in >> luna;
        in >> an;

        Data aux;
        aux.setData(zi, luna, an);
        if (c.setDataConsultatie(aux) == true) {
            c.data = aux;
        }
        int ora;
        in >> ora;
        if (ora >= 1 && ora <= 24) {
            c.ora = ora;
        }
        else {
            c.ora = 24;
        }
        ok = 0;
        float pret;
        in >> pret;
        if (pret > 50) {
            c.pret = (float)pret;
        }
        return in;
    }
#pragma endregion

#pragma region ScriereFisier
    friend ofstream& operator<<(ofstream& out, const Consultatie& c) {
            out << c.data.getZi() << " " << c.data.getLuna() << " " << c.data.getAn() << endl;
            out << c.ora << endl;
            out << c.pret << endl;
       return out;
    }
#pragma endregion

#pragma region Destructor
    ~Consultatie() {}
#pragma endregion

};

int Consultatie::contor = 0;

#pragma endregion