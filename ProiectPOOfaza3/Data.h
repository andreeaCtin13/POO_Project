#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <string.h>
#include <time.h>
#include "Functii.h"


#pragma region Clasa_Data
class Data {
    int zi;
    int luna;
    int an;
public:
    Data() {
        this->luna = 1;
        this->zi = 1;
        this->an = 1991;
    }
    Data(int zi, int luna, int an) {

        if (esteDataOk(zi, luna, an)) {
            this->zi = zi;
            this->luna = luna;
            this->an = an;
        }
        else
        {
            this->luna = 1;
            this->zi = 1;
            this->an = 1991;
        }
    }

    bool setData(int zi, int luna, int an) {
        if (esteDataOk(zi, luna, an)) {
            this->zi = zi;
            this->luna = luna;
            this->an = an;
            return true;
        }
        else {
            return false;
        }
    }

    void setZi(int zi) {
        if (esteDataOk(zi, this->luna, this->an) == true) {
            this->zi = zi;
        }
    }

    int getZi() const {
        return this->zi;
    }

    void setLuna(int luna) {
        if (esteDataOk(this->zi, luna, this->an) == true) {
            this->luna = luna;
        }
    }

    int getLuna() const {
        return this->luna;
    }

    void setAn(int an) {
        if (esteDataOk(this->zi, this->luna, an) == true) {
            this->an = an;
        }
    }

    int getAn() const {
        return this->an;
    }

    Data& operator = (const Data& d) {
        if (esteDataOk(d.zi, d.luna, d.an)) {
            this->zi = d.zi;
            this->luna = d.luna;
            this->an = d.an;
        }
        return *this;
    }

    void writeBinary(fstream& f) {

        f.write((char*)&this->zi, sizeof(int));
        f.write((char*)&this->luna, sizeof(int));
        f.write((char*)&this->an, sizeof(int));

    }

};
#pragma endregion
